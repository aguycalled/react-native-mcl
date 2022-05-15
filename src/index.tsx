import crypto from 'crypto';
import { NativeModules, Platform } from 'react-native';
import * as Utils from './Utils';

const LINKING_ERROR =
  `The package 'react-native-mcl' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo managed workflow\n';

const Mcl = NativeModules.Mcl
  ? NativeModules.Mcl
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

console.log('Loaded React Native MCL');

const MCLBN_FP_UNIT_SIZE = 6
const MCLBN_FR_UNIT_SIZE = 4
const MCLBN_FP_SIZE = MCLBN_FP_UNIT_SIZE * 8
const MCLBN_FR_SIZE = MCLBN_FR_UNIT_SIZE * 8
const MCLBN_G1_SIZE = MCLBN_FP_SIZE * 3
const MCLBN_G2_SIZE = MCLBN_FP_SIZE * 6
const MCLBN_GT_SIZE = MCLBN_FP_SIZE * 12

export enum CurveType {
  BN254 = 0,
  BN_SNARK1 = 4,
  BLS12_381 = 5,

  SECP224K1 = 101,
  SECP256K1 = 102,
  NIST_P192 = 105,
  NIST_P224 = 106,
  NIST_P256 = 107,
}

export const BN254 = CurveType.BN254;
export const BN_SNARK1 = CurveType.BN_SNARK1;
export const BLS12_381 = CurveType.BLS12_381;
export const SECP224K1 = CurveType.SECP224K1;
export const SECP256K1 = CurveType.SECP256K1;
export const NIST_P192 = CurveType.NIST_P192;
export const NIST_P224 = CurveType.NIST_P224;
export const NIST_P256 = CurveType.NIST_P256;
//export const IRTF = 5;
//export const EC_PROJ = 1024;

export class Common {
  a_: Uint32Array;

  constructor(size: number) {
    this.a_ = new Uint32Array(size/4);
  }
  // @ts-ignore
  deserialize(b: Uint8Array) {
  }
  serialize() {}
  deserializeHexStr(s: string) {
    this.deserialize(Utils.fromHexStr(s));
  }
  serializeToHexStr() {
    return Utils.toHexStr(this.serialize());
  }
  dump(msg = '') {
    console.log(msg + this.serializeToHexStr());
  }
  clear() {
    this.a_.fill(0);
  }
  // divide Uint32Array a into n and chose the idx-th
  _getSubArray(idx: number, n: number) {
    const d = this.a_.length / n;
    return new Uint32Array(this.a_.buffer, d * idx*4, d);
  }
  // set array lhs to idx
  _setSubArray(lhs: Common, idx: number, n: number) {
    const d = this.a_.length / n;
    this.a_.set(lhs.a_, d * idx);
  }
  _setA(a: Uint8Array | Uint32Array) {
    if (a instanceof Uint32Array) {
      this.a_.set(a);
    } else {
      this.a_.set(Utils.Uint8ToUint32(a));
    }
  }
}

export class Fr extends Common {
  constructor() {
    super(MCLBN_FR_SIZE);
  }
  setInt(x: number) {
    this._setA(Mcl.frSetInt32(x));
  }
  deserialize(s: Uint8Array) {
    try {
      this._setA(Mcl.frDeserialize(new Uint8Array(s)));
    } catch(e) {
      console.log(e)
    }
  }
  serialize() {
    try {
      return new Uint8Array(Mcl.frSerialize(Utils.Uint32ToUint8(this.a_)));
    } catch(e) {
      console.log(e)
      return new Uint8Array(32);
    }
  }
  setStr(s: string, base = 0) {
    this._setA(Mcl.frSetStr(s, base));
  }
  getStr(base = 0) {
    return Mcl.frGetStr(Utils.Uint32ToUint8(this.a_), base);
  }
  isZero() {
    return Mcl.frIsZero(Utils.Uint32ToUint8(this.a_)) === 1;
  }
  isOne() {
    return Mcl.frIsOne(Utils.Uint32ToUint8(this.a_)) === 1;
  }
  isEqual(rhs: this) {
    return Mcl.frIsEqual(Utils.Uint32ToUint8(this.a_), Utils.Uint32ToUint8(rhs.a_)) === 1;
  }
  setLittleEndian(s: Uint8Array) {
    this._setA(Mcl.frSetLittleEndian(s));
  }
  setLittleEndianMod(s: Uint8Array) {
    this._setA(Mcl.frSetLittleEndianMod(s));
  }
  setBigEndianMod(s: Uint8Array) {
    this._setA(Mcl.frSetBigEndianMod(s));
  }
  setByCSPRNG() {
    const a = new Uint8Array(MCLBN_FR_SIZE);
    crypto.randomFillSync(a);
    this.setLittleEndian(a);
  }
  setHashOf(a: string | Uint8Array) {
    if (typeof a === 'string') {
      this.setHashOf(new Uint8Array(Buffer.from(a, 'utf-8').buffer));
    } else {
      this._setA(Mcl.frSetHashOf(a));
    }
  }
}

export const deserializeHexStrToFr = (s: string) => {
  const r = new Fr();
  r.deserializeHexStr(s);
  return r;
};

export class Fp extends Common {
  constructor() {
    super(MCLBN_FP_SIZE);
  }
  setInt(x: number) {
    this._setA(Mcl.fpSetInt32(x));
  }
  deserialize(s: Uint8Array) {
    this._setA(Mcl.fpDeserialize(new Uint8Array(s)));
  }
  serialize() {
    return new Uint8Array(Mcl.fpSerialize(Utils.Uint32ToUint8(this.a_)));
  }
  setStr(s: string, base = 0) {
    this._setA(Mcl.fpSetStr(s, base));
  }
  getStr(base = 0) {
    return Mcl.fpGetStr(this.a_, base);
  }
  isEqual(rhs: this) {
    return Mcl.fpIsEqual(Utils.Uint32ToUint8(this.a_), Utils.Uint32ToUint8(rhs.a_)) === 1;
  }
  setLittleEndian(s: Uint8Array) {
    this._setA(Mcl.fpSetLittleEndian(s));
  }
  setLittleEndianMod(s: Uint8Array) {
    this._setA(Mcl.fpSetLittleEndianMod(s));
  }
  setBigEndianMod(s: Uint8Array) {
    this._setA(Mcl.fpSetBigEndianMod(s));
  }
  setByCSPRNG() {
    const a = new Uint8Array(MCLBN_FP_SIZE);
    crypto.randomFillSync(a);
    this.setLittleEndian(a);
  }
  setHashOf(a: string | Uint8Array) {
    if (typeof a === 'string') {
      this.setHashOf(new Uint8Array(Buffer.from(a, 'utf-8')));
    } else {
      this._setA(Mcl.fpSetHashOf(a));
    }
  }
  mapToG1() {
    const y = new G1();
    y._setA(Mcl.fpMapToG1(Utils.Uint32ToUint8(this.a_)));
    return y;
  }
}

export const deserializeHexStrToFp = (s: string) => {
  const r = new Fp();
  r.deserializeHexStr(s);
  return r;
};

export class Fp2 extends Common {
  constructor() {
    super(MCLBN_FP_SIZE * 2);
  }
  setInt(x: number, y: number) {
    const v = new Fp();
    v.setInt(x);
    this.set_a(v);
    v.setInt(y);
    this.set_b(v);
  }
  deserialize(s: Uint8Array) {
    this._setA(Mcl.fp2Deserialize(new Uint8Array(s)));
  }
  serialize() {
    return new Uint8Array(Mcl.fp2Serialize(Utils.Uint32ToUint8(this.a_)));
  }
  isEqual(rhs: this) {
    return Mcl.fp2IsEqual(Utils.Uint32ToUint8(this.a_), Utils.Uint32ToUint8(rhs.a_)) === 1;
  }
  /*
    x = a + bi where a, b in Fp and i^2 = -1
  */
  get_a() {
    const r = new Fp();
    r.a_ = this._getSubArray(0, 2);
    return r;
  }
  get_b() {
    const r = new Fp();
    r.a_ = this._getSubArray(1, 2);
    return r;
  }
  set_a(v: Fp) {
    this._setSubArray(v, 0, 2);
  }
  set_b(v: Fp) {
    this._setSubArray(v, 1, 2);
  }
  mapToG2() {
    const y = new G2();
    y._setA(Mcl.fpMapToG2(Utils.Uint32ToUint8(this.a_)));
    return y;
  }
}
export const deserializeHexStrToFp2 = (s: string) => {
  const r = new Fp2();
  r.deserializeHexStr(s);
  return r;
};

export class G1 extends Common {
  constructor() {
    super(MCLBN_G1_SIZE);
  }
  deserialize(s: Uint8Array) {
    this._setA(Mcl.g1Deserialize(new Uint8Array(s)))
  }
  serialize() {
    return new Uint8Array(Mcl.g1Serialize(Utils.Uint32ToUint8(this.a_)));
  }
  setStr(s: string, base = 0) {
    this._setA(Mcl.g1SetStr(s, base));
  }
  getStr(base = 0) {
    return Mcl.g1GetStr(Utils.Uint32ToUint8(this.a_), base);
  }
  normalize() {
    this.a_ = normalize(this).a_;
  }
  getX() {
    const r = new Fp();
    r.a_ = this._getSubArray(0, 3);
    return r;
  }
  getY() {
    const r = new Fp();
    r.a_ = this._getSubArray(1, 3);
    return r;
  }
  getZ() {
    const r = new Fp();
    r.a_ = this._getSubArray(2, 3);
    return r;
  }
  setX(v: Fp) {
    this._setSubArray(v, 0, 3);
  }
  setY(v: Fp) {
    this._setSubArray(v, 1, 3);
  }
  setZ(v: Fp) {
    this._setSubArray(v, 2, 3);
  }
  isZero() {
    return Mcl.g1IsZero(Utils.Uint32ToUint8(this.a_)) === 1;
  }
  isValid() {
    return Mcl.g1IsValid(Utils.Uint32ToUint8(this.a_)) === 1;
  }
  isValidOrder() {
    return Mcl.g1IsValidOrder(Utils.Uint32ToUint8(this.a_)) === 1;
  }
  isEqual(rhs: this) {
    return Mcl.g1IsEqual(Utils.Uint32ToUint8(this.a_), Utils.Uint32ToUint8(rhs.a_)) === 1;
  }
  setHashOf(s: Uint8Array) {
    if (typeof s === 'string') {
      this.setHashOf(new Uint8Array(Buffer.from(s, 'utf-8')));
    } else {
      this._setA(Mcl.g1SetHashAndMapTo(s));
    }
  }
}
export const deserializeHexStrToG1 = (s: string) => {
  const r = new G1();
  r.deserializeHexStr(s);
  return r;
};

export const setETHserialization = (ETHserialization: boolean) => {
  Mcl.setETHserialization(ETHserialization ? 1 : 0);
};

// mode = mcl.IRTF for Ethereum 2.0 spec
export const setMapToMode = (mode: number) => {
  Mcl.setMapToMode(mode);
};
export const verifyOrderG1 = (doVerify: boolean) => {
  Mcl.verifyOrderG1(doVerify ? 1 : 0);
};
export const verifyOrderG2 = (doVerify: boolean) => {
  Mcl.verifyOrderG2(doVerify ? 1 : 0);
};
export const getBasePointG1 = () => {
  const x = new G1();
  x.a_ = Mcl.g1GetBasePoint();
  if (x.isZero()) {
    throw new Error('not supported for pairing curves');
  }
  return x;
};

export class G2 extends Common {
  constructor() {
    super(MCLBN_G2_SIZE);
  }
  deserialize(s: Uint8Array) {
    this._setA(Mcl.g2Deserialize(new Uint8Array(s)));
  }
  serialize() {
    return new Uint8Array(Mcl.g2Serialize(Utils.Uint32ToUint8(this.a_)));
  }
  setStr(s: string, base = 0) {
    this._setA(Mcl.g2SetStr(s, base));
  }
  getStr(base = 0) {
    return Mcl.g2GetStr(Utils.Uint32ToUint8(this.a_), base);
  }
  normalize() {
    this.a_ = normalize(this).a_;
  }
  getX() {
    const r = new Fp2();
    r.a_ = this._getSubArray(0, 3);
    return r;
  }
  getY() {
    const r = new Fp2();
    r.a_ = this._getSubArray(1, 3);
    return r;
  }
  getZ() {
    const r = new Fp2();
    r.a_ = this._getSubArray(2, 3);
    return r;
  }
  setX(v: Fp2) {
    this._setSubArray(v, 0, 3);
  }
  setY(v: Fp2) {
    this._setSubArray(v, 1, 3);
  }
  setZ(v: Fp2) {
    this._setSubArray(v, 2, 3);
  }
  isZero() {
    return Mcl.g2IsZero(Utils.Uint32ToUint8(this.a_)) === 1;
  }
  isValid() {
    return Mcl.g2IsValid(Utils.Uint32ToUint8(this.a_)) === 1;
  }
  isValidOrder() {
    return Mcl.g2IsValidOrder(Utils.Uint32ToUint8(this.a_)) === 1;
  }
  isEqual(rhs: this) {
    return Mcl.g2IsEqual(Utils.Uint32ToUint8(this.a_), Utils.Uint32ToUint8(rhs.a_)) === 1;
  }
  setHashOf(a: Uint8Array) {
    if (typeof a === 'string') {
      this.setHashOf(new Uint8Array(Buffer.from(a, 'utf-8')));
    } else {
      this._setA(Mcl.g2SetHashAndMapTo(a));
    }
  }
}

export const deserializeHexStrToG2 = (s: string) => {
  const r = new G2();
  r.deserializeHexStr(s);
  return r;
};

export class GT extends Common {
  constructor() {
    super(MCLBN_GT_SIZE);
  }
  setInt(x: number) {
    this._setA(Mcl.gtSetInt32(x));
  }
  deserialize(s: Uint8Array) {
    this._setA(Mcl.gtDeserialize(new Uint8Array(s)));
  }
  serialize() {
    return new Uint8Array(Mcl.gtSerialize(Utils.Uint32ToUint8(this.a_)));
  }
  setStr(s: string, base = 0) {
    this._setA(Mcl.gtSetStr(s, base));
  }
  getStr(base = 0) {
    return Mcl.gtGetStr(Utils.Uint32ToUint8(this.a_), base);
  }
  isEqual(rhs: this) {
    return Mcl.g1IsEqual(Utils.Uint32ToUint8(this.a_), Utils.Uint32ToUint8(rhs.a_)) === 1;
  }
  isZero() {
    return Mcl.g1IsZero(Utils.Uint32ToUint8(this.a_)) === 1;
  }
  isOne() {
    return Mcl.g1IsOne(Utils.Uint32ToUint8(this.a_)) === 1;
  }
}

export const deserializeHexStrToGT = (s: string) => {
  const r = new GT();
  r.deserializeHexStr(s);
  return r;
};

export class PrecomputedG2 {
  p: Uint32Array | null;

  constructor(Q: G2) {
    if (!(Q instanceof G2)) throw new Error('PrecomputedG2:bad type');
    //const byteSize = Mcl.getUint64NumToPrecompute() * 8;
    //this.p = new Uint32Array(byteSize);
    this.p = Utils.Uint8ToUint32(Mcl.precomputeG2(Utils.Uint32ToUint8(Q.a_)));
  }
  /*
    call destroy if PrecomputedG2 is not necessary
    to avoid memory leak
  */
  destroy() {
    this.p = null;
  }
}

export const neg = (x: any) => {
  if (x instanceof Fr) {
    let ret = new Fr();
    ret._setA(Mcl.frNeg(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof Fp) {
    let ret = new Fp();
    ret._setA(Mcl.fpNeg(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof G1) {
    let ret = new G1();
    ret._setA(Mcl.g1Neg(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof G2) {
    let ret = new G2();
    ret._setA(Mcl.g2Neg(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof GT) {
    let ret = new GT();
    ret._setA(Mcl.gtNeg(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof Fp2) {
    let ret = new Fp2();
    ret._setA(Mcl.fp2Neg(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  throw new Error('neg:bad type')
}

export const sqr = (x: any) => {
  if (x instanceof Fr) {
    let ret = new Fr();
    ret._setA(Mcl.frSqr(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof Fp) {
    let ret = new Fp();
    ret._setA(Mcl.fpSqr(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof GT) {
    let ret = new GT();
    ret._setA(Mcl.gtSqr(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof Fp2) {
    let ret = new Fp2();
    ret._setA(Mcl.fp2Sqr(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  throw new Error('sqr:bad type')
}

export const inv = (x: any) => {
  if (x instanceof Fr) {
    let ret = new Fr();
    ret._setA(Mcl.frInv(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof Fp) {
    let ret = new Fp();
    ret._setA(Mcl.fpInv(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof GT) {
    let ret = new GT();
    ret._setA(Mcl.gtInv(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof Fp2) {
    let ret = new Fp2();
    ret._setA(Mcl.fp2Inv(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  throw new Error('inv:bad type')
}

export const normalize = (x: any) => {
  if (x instanceof G1) {
    let ret = new G1();
    ret._setA(Mcl.g1Normalize(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof G2) {
    let ret = new G2();
    ret._setA(Mcl.g2Normalize(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  throw new Error('normalize:bad type')
}

export const add = (x: any, y: any) => {
  if (x.constructor !== y.constructor) throw new Error('add:mismatch type')
  if (x instanceof Fp) {
    let ret = new Fp();
    ret._setA(Mcl.fpAdd(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof Fr) {
    let ret = new Fr();
    ret._setA(Mcl.frAdd(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof G1) {
    let ret = new G1();
    ret._setA(Mcl.g1Add(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof G2) {
    let ret = new G2();
    ret._setA(Mcl.g2Add(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof GT) {
    let ret = new GT();
    ret._setA(Mcl.gtAdd(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  throw new Error('add:bad type')
}

export const sub = (x: any, y: any) => {
  if (x.constructor !== y.constructor) throw new Error('sub:mismatch type')
  if (x instanceof Fp) {
    let ret = new Fp();
    ret._setA(Mcl.fpSub(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof Fr) {
    let ret = new Fr();
    ret._setA(Mcl.frSub(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof G1) {
    let ret = new G1();
    ret._setA(Mcl.g1Sub(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof G2) {
    let ret = new G2();
    ret._setA(Mcl.g2Sub(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof GT) {
    let ret = new GT();
    ret._setA(Mcl.gtSub(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof G2) {
    let ret = new G2();
    ret._setA(Mcl.g2Sub(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  throw new Error('sub:bad type')
}

export const mul = (x: any, y:any) => {
  if (x instanceof Fp && y instanceof Fp) {
    let ret = new Fp();
    ret._setA(Mcl.fpMul(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof Fr && y instanceof Fr) {
    let ret = new Fr();
    ret._setA(Mcl.frMul(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof G1 && y instanceof Fr) {
    let ret = new G1();
    ret._setA(Mcl.g1Mul(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof G2 && y instanceof Fr) {
    let ret = new G2();
    ret._setA(Mcl.g2Mul(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof GT && y instanceof GT) {
    let ret = new GT();
    ret._setA(Mcl.gtMul(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof Fp2 && y instanceof Fp2) {
    let ret = new Fp2();
    ret._setA(Mcl.fp2Mul(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  throw new Error('mul:mismatch type')
}

export const mulVec = (xVec: any, yVec: Fr[]) => {
  if (xVec.length == 0) throw new Error('mulVec:zero array')
  if (xVec[0] instanceof G1 && yVec[0] instanceof Fr) {
    let ret = new G1();
    ret._setA(Mcl.g1MulVec(xVec.map((a: G1) => Utils.Uint32ToUint8(a.a_)), yVec.map((a: Fr) => Utils.Uint32ToUint8(a.a_))));
    return ret;
  }
  if (xVec[0] instanceof G2 && yVec[0] instanceof Fr) {
    let ret = new G2();
    ret._setA(Mcl.g2MulVec(xVec.map((a: G2) => Utils.Uint32ToUint8(a.a_)), yVec.map((a: Fr) => Utils.Uint32ToUint8(a.a_))));
    return ret;
  }
  throw new Error('mulVec:mismatch type')
}

export const div = (x: any, y:any) => {
  if (x.constructor !== y.constructor) throw new Error('div:mismatch type')
  if (x instanceof Fp) {
    let ret = new Fp();
    ret._setA(Mcl.fpDiv(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof Fr) {
    let ret = new Fr();
    ret._setA(Mcl.frDiv(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof GT) {
    let ret = new GT();
    ret._setA(Mcl.gtDiv(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  if (x instanceof G2) {
    let ret = new G2();
    ret._setA(Mcl.g2Div(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  throw new Error('div:bad type')
}

export const dbl = (x: any) => {
  if (x instanceof G1) {
    let ret = new G1();
    ret._setA(Mcl.g1Dbl(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  if (x instanceof G2) {
    let ret = new G2();
    ret._setA(Mcl.g2Dbl(Utils.Uint32ToUint8(x.a_)));
    return ret;
  }
  throw new Error('inv:bad type')
}

export const hashToFr = (s: string | Uint8Array) => {
  const x = new Fr()
  x.setHashOf(s)
  return x
}
export const hashAndMapToG1 = (s: Uint8Array) => {
  const x = new G1()
  x.setHashOf(s)
  return x
}
export const hashAndMapToG2 = (s: Uint8Array) => {
  const x = new G2()
  x.setHashOf(s)
  return x
}
export const pow = (x: GT, y: Fr) => {
  if (x instanceof GT && y instanceof Fr) {
    let ret = new GT();
    ret.a_ = Utils.Uint8ToUint32(Mcl.gtPow(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  throw new Error('pow:bad type')
}
export const pairing = (x: G1, y: G2) => {
  if (x instanceof G1 && y instanceof G2) {
    let ret = new GT();
    ret.a_ = Utils.Uint8ToUint32(Mcl.pairing(Utils.Uint32ToUint8(x.a_), Utils.Uint32ToUint8(y.a_)));
    return ret;
  }
  throw new Error('pow:bad type')
}
export async function init(curve = CurveType.BLS12_381) {
  try {
    await Mcl.initialize(curve);
  } catch(e) {
    console.log(e);
  }
}

export const getPublicKey = (sk: Uint8Array) => {
  return new Uint8Array(Mcl.getPublicKey(sk));
}

export const sign = async (m: Uint8Array, pk: Uint8Array) => {
  let ret = new Uint8Array(Mcl.sign(new Uint8Array(m), new Uint8Array(pk)));
  return ret;
}

export const verify = async (sig: Uint8Array, m: Uint8Array, pk: Uint8Array) => {
  return Mcl.verify(new Uint8Array(sig), new Uint8Array(m), new Uint8Array(pk));
}

export const aggregateSignatures = (sigs: Uint8Array[]) => {
  return new Uint8Array(Mcl.aggregateSignatures(sigs.map(el => new Uint8Array(el))));
}

export const verifyBatch = async (sig: Uint8Array, ms: Uint8Array[], pks: Uint8Array[]) => {
  return Mcl.verifyBatch(new Uint8Array(sig), ms.map(el => new Uint8Array(el)), pks.map(el => new Uint8Array(el)));
}

export const getHashId = (ok: string | G1, sk: string | G1, vk: Fr) => {
  let ret = new G1();
  if (ok instanceof G1 && sk instanceof G1) {
    ret.a_ = Utils.Uint8ToUint32(Mcl.GetHashId(Utils.Uint32ToUint8(ok.a_), Utils.Uint32ToUint8(sk.a_), vk.serialize()));
  } else {
    ret.a_ = Utils.Uint8ToUint32(Mcl.GetHashId(Utils.fromHexStr(ok as string), Utils.fromHexStr(sk as string), vk.serialize()));
  }
  return ret;
}

export const utils = {
  setDSTLabel: (a: string) => {
    Mcl.setDSTLabel(a);
  }
}
