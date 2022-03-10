import './shim.js';
import crypto from 'crypto';
import { NativeModules, Platform } from 'react-native';
import * as utils from './Utils';

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
  a_: Uint8Array;

  constructor(size: number) {
    this.a_ = new Uint8Array(size);
  }
  deserialize(b: Uint8Array) {
    this.a_ = new Uint8Array(Buffer.from(b).buffer);
  }
  serialize() {}
  deserializeHexStr(s: string) {
    this.deserialize(utils.fromHexStr(s));
  }
  serializeToHexStr() {
    return utils.toHexStr(this.serialize());
  }
  dump(msg = '') {
    console.log(msg + this.serializeToHexStr());
  }
  clear() {
    this.a_.fill(0);
  }
  // divide Uint8Array a into n and chose the idx-th
  _getSubArray(idx: number, n: number) {
    const d = this.a_.length / n;
    return new Uint8Array(this.a_.buffer, d * idx * 4, d);
  }
  // set array lhs to idx
  _setSubArray(lhs: Common, idx: number, n: number) {
    const d = this.a_.length / n;
    this.a_.set(lhs.a_, d * idx);
  }
}

export class Fr extends Common {
  constructor() {
    super(MCLBN_FR_SIZE);
  }
  setInt(x: number) {
    this.a_ = new Uint8Array(Mcl.frSetInt32(x));
  }
  deserialize(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.frDeserialize(new Uint8Array(Buffer.from(s).buffer)));
  }
  serialize() {
    return this.a_;
  }
  setStr(s: string, base = 0) {
    this.a_ = new Uint8Array(Mcl.frSetStr(s, base));
  }
  getStr(base = 0) {
    return Mcl.frGetStr(this.a_, base);
  }
  isZero() {
    return Mcl.frIsZero(this.a_) === 1;
  }
  isOne() {
    return Mcl.frIsOne(this.a_) === 1;
  }
  isEqual(rhs: this) {
    return Mcl.frIsEqual(this.a_, rhs.a_) === 1;
  }
  setLittleEndian(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.frSetLittleEndian(new Uint8Array(Buffer.from(s).buffer)));
  }
  setLittleEndianMod(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.frSetLittleEndianMod(new Uint8Array(Buffer.from(s).buffer)));
  }
  setBigEndianMod(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.frSetBigEndianMod(new Uint8Array(Buffer.from(s).buffer)));
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
      this.a_ = new Uint8Array(Mcl.frSetHashOf(new Uint8Array(Buffer.from(a).buffer)));
    }
  }
}

export const deserializeHexStrToFr = (s: string) => {
  const r = new exports.Fr();
  r.deserializeHexStr(s);
  return r;
};

export class Fp extends Common {
  constructor() {
    super(MCLBN_FP_SIZE);
  }
  setInt(x: number) {
    this.a_ = new Uint8Array(Mcl.fpSetInt32(x));
  }
  deserialize(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.fpDeserialize(new Uint8Array(Buffer.from(s).buffer)));
  }
  serialize() {
    return this.a_;
  }
  setStr(s: string, base = 0) {
    this.a_ = new Uint8Array(Mcl.fpSetStr(s, base));
  }
  getStr(base = 0) {
    return Mcl.fpGetStr(this.a_, base);
  }
  isEqual(rhs: this) {
    return Mcl.fpIsEqual(this.a_, rhs.a_) === 1;
  }
  setLittleEndian(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.fpSetLittleEndian(new Uint8Array(Buffer.from(s).buffer)));
  }
  setLittleEndianMod(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.fpSetLittleEndianMod(new Uint8Array(Buffer.from(s).buffer)));
  }
  setBigEndianMod(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.fpSetBigEndianMod(new Uint8Array(Buffer.from(s).buffer)));
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
      this.a_ = new Uint8Array(Mcl.fpSetHashOf(new Uint8Array(Buffer.from(a).buffer)));
    }
  }
  mapToG1() {
    const y = new G1();
    y.a_ = new Uint8Array(Mcl.fpMapToG1(this.a_));
    return y;
  }
}

export const deserializeHexStrToFp = (s: string) => {
  const r = new exports.Fp();
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
    this.a_ = new Uint8Array(Mcl.fp2Deserialize(new Uint8Array(Buffer.from(s).buffer)));
  }
  serialize() {
    return this.a_;
  }
  isEqual(rhs: this) {
    return Mcl.fp2IsEqual(this.a_, rhs.a_) === 1;
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
    y.a_ = new Uint8Array(Mcl.fpMapToG2(this.a_));
    return y;
  }
}
export const deserializeHexStrToFp2 = (s: string) => {
  const r = new exports.Fp2();
  r.deserializeHexStr(s);
  return r;
};

export class G1 extends Common {
  constructor() {
    super(MCLBN_G1_SIZE);
  }
  deserialize(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.g1Deserialize(new Uint8Array(Buffer.from(s).buffer)));
  }
  serialize() {
    return this.a_;
  }
  setStr(s: string, base = 0) {
    this.a_ = new Uint8Array(Mcl.g1SetStr(s, base));
  }
  getStr(base = 0) {
    return Mcl.g1GetStr(this.a_, base);
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
    return Mcl.g1IsZero(this.a_) === 1;
  }
  isValid() {
    return Mcl.g1IsValid(this.a_) === 1;
  }
  isValidOrder() {
    return Mcl.g1IsValidOrder(this.a_) === 1;
  }
  isEqual(rhs: this) {
    return Mcl.g1IsEqual(this.a_, rhs.a_) === 1;
  }
  setHashOf(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.g1SetHashAndMapTo(new Uint8Array(Buffer.from(s).buffer)));
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
    this.a_ = new Uint8Array(Mcl.g2Deserialize(new Uint8Array(Buffer.from(s).buffer)));
  }
  serialize() {
    return this.a_;
  }
  setStr(s: string, base = 0) {
    this.a_ = new Uint8Array(Mcl.g2SetStr(s, base));
  }
  getStr(base = 0) {
    return Mcl.g2GetStr(this.a_, base);
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
    return Mcl.g2IsZero(this.a_) === 1;
  }
  isValid() {
    return Mcl.g2IsValid(this.a_) === 1;
  }
  isValidOrder() {
    return Mcl.g2IsValidOrder(this.a_) === 1;
  }
  isEqual(rhs: this) {
    return Mcl.g2IsEqual(this.a_, rhs.a_) === 1;
  }
  setHashOf(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.g2SetHashAndMapTo(new Uint8Array(Buffer.from(s).buffer)));
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
    this.a_ = new Uint8Array(Mcl.gtSetInt32(x));
  }
  deserialize(s: Uint8Array) {
    this.a_ = new Uint8Array(Mcl.gtDeserialize(new Uint8Array(Buffer.from(s).buffer)));
  }
  serialize() {
    return this.a_;
  }
  setStr(s: string, base = 0) {
    this.a_ = new Uint8Array(Mcl.gtSetStr(s, base));
  }
  getStr(base = 0) {
    return Mcl.gtGetStr(this.a_, base);
  }
  isEqual(rhs: this) {
    return Mcl.g1IsEqual(this.a_, rhs.a_) === 1;
  }
  isZero() {
    return Mcl.g1IsZero(this.a_) === 1;
  }
  isOne() {
    return Mcl.g1IsOne(this.a_) === 1;
  }
}

export const deserializeHexStrToGT = (s: string) => {
  const r = new GT();
  r.deserializeHexStr(s);
  return r;
};

export class PrecomputedG2 {
  p: Uint8Array | null;

  constructor(Q: G2) {
    if (!(Q instanceof G2)) throw new Error('PrecomputedG2:bad type');
    //const byteSize = Mcl.getUint64NumToPrecompute() * 8;
    //this.p = new Uint8Array(byteSize);
    this.p = new Uint8Array(Mcl.precomputeG2(Q.a_));
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
    ret.a_ = new Uint8Array(Mcl.frNeg(x.a_));
    return ret;
  }
  if (x instanceof Fp) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.fpNeg(x.a_));
    return ret;
  }
  if (x instanceof G1) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.g1Neg(x.a_));
    return ret;
  }
  if (x instanceof G2) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.g2Neg(x.a_));
    return ret;
  }
  if (x instanceof GT) {
    let ret = new GT();
    ret.a_ = new Uint8Array(Mcl.gtNeg(x.a_));
    return ret;
  }
  if (x instanceof Fp2) {
    let ret = new Fp2();
    ret.a_ = new Uint8Array(Mcl.fp2Neg(x.a_));
    return ret;
  }
  throw new Error('neg:bad type')
}

export const sqr = (x: any) => {
  if (x instanceof Fr) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.frSqr(x.a_));
    return ret;
  }
  if (x instanceof Fp) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.fpSqr(x.a_));
    return ret;
  }
  if (x instanceof GT) {
    let ret = new GT();
    ret.a_ = new Uint8Array(Mcl.gtSqr(x.a_));
    return ret;
  }
  if (x instanceof Fp2) {
    let ret = new Fp2();
    ret.a_ = new Uint8Array(Mcl.fp2Sqr(x.a_));
    return ret;
  }
  throw new Error('sqr:bad type')
}

export const inv = (x: any) => {
  if (x instanceof Fr) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.frInv(x.a_));
    return ret;
  }
  if (x instanceof Fp) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.fpInv(x.a_));
    return ret;
  }
  if (x instanceof GT) {
    let ret = new GT();
    ret.a_ = new Uint8Array(Mcl.gtInv(x.a_));
    return ret;
  }
  if (x instanceof Fp2) {
    let ret = new Fp2();
    ret.a_ = new Uint8Array(Mcl.fp2Inv(x.a_));
    return ret;
  }
  throw new Error('inv:bad type')
}

export const normalize = (x: any) => {
  if (x instanceof G1) {
    let ret = new G1();
    ret.a_ = new Uint8Array(Mcl.g1Normalize(x.a_));
    return ret;
  }
  if (x instanceof G2) {
    let ret = new G2();
    ret.a_ = new Uint8Array(Mcl.g2Normalize(x.a_));
    return ret;
  }
  throw new Error('normalize:bad type')
}

export const add = (x: any, y: any) => {
  if (x.constructor !== y.constructor) throw new Error('add:mismatch type')
  if (x instanceof exports.Fp) {
    let ret = new Fp();
    ret.a_ = new Uint8Array(Mcl.fpAdd(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.Fr) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.frAdd(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.G1) {
    let ret = new G1();
    ret.a_ = new Uint8Array(Mcl.g1Add(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.G2) {
    let ret = new G2();
    ret.a_ = new Uint8Array(Mcl.g2Add(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.GT) {
    let ret = new GT();
    ret.a_ = new Uint8Array(Mcl.gtAdd(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.G2) {
    let ret = new G2();
    ret.a_ = new Uint8Array(Mcl.g2Add(x.a_, y.a_));
    return ret;
  }
  throw new Error('add:bad type')
}

export const sub = (x: any, y: any) => {
  if (x.constructor !== y.constructor) throw new Error('sub:mismatch type')
  if (x instanceof exports.Fp) {
    let ret = new Fp();
    ret.a_ = new Uint8Array(Mcl.fpSub(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.Fr) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.frSub(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.G1) {
    let ret = new G1();
    ret.a_ = new Uint8Array(Mcl.g1Sub(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.G2) {
    let ret = new G2();
    ret.a_ = new Uint8Array(Mcl.g2Sub(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.GT) {
    let ret = new GT();
    ret.a_ = new Uint8Array(Mcl.gtSub(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.G2) {
    let ret = new G2();
    ret.a_ = new Uint8Array(Mcl.g2Sub(x.a_, y.a_));
    return ret;
  }
  throw new Error('sub:bad type')
}

export const mul = (x: any, y:any) => {
  if (x instanceof Fp && y instanceof Fp) {
    let ret = new Fp();
    ret.a_ = new Uint8Array(Mcl.fpMul(x.a_, y.a_));
    return ret;
  }
  if (x instanceof Fr && y instanceof Fr) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.frMul(x.a_, y.a_));
    return ret;
  }
  if (x instanceof G1 && y instanceof Fr) {
    let ret = new G1();
    ret.a_ = new Uint8Array(Mcl.g1Mul(x.a_, y.a_));
    return ret;
  }
  if (x instanceof G2 && y instanceof Fr) {
    let ret = new G2();
    ret.a_ = new Uint8Array(Mcl.g2Mul(x.a_, y.a_));
    return ret;
  }
  if (x instanceof GT && y instanceof GT) {
    let ret = new GT();
    ret.a_ = new Uint8Array(Mcl.gtMul(x.a_, y.a_));
    return ret;
  }
  if (x instanceof Fp2 && y instanceof Fp2) {
    let ret = new Fp2();
    ret.a_ = new Uint8Array(Mcl.fp2Mul(x.a_, y.a_));
    return ret;
  }
  throw new Error('mul:mismatch type')
}

export const mulVec = (xVec: any, yVec: Fr[]) => {
  if (xVec.length == 0) throw new Error('mulVec:zero array')
  if (xVec[0] instanceof G1 && yVec[0] instanceof Fr) {
    let ret = new G1();
    ret.a_ = new Uint8Array(Mcl.g1MulVec(xVec.map((a: G1) => a.a_), yVec.map((a: Fr) => a.a_)));
    return ret;
  }
  if (xVec[0] instanceof G2 && yVec[0] instanceof Fr) {
    let ret = new G2();
    ret.a_ = new Uint8Array(Mcl.g2Mul(xVec.map((a: G2) => a.a_), yVec.map((a: Fr) => a.a_)));
    return ret;
  }
  throw new Error('mulVec:mismatch type')
}

export const div = (x: any, y:any) => {
  if (x.constructor !== y.constructor) throw new Error('div:mismatch type')
  if (x instanceof exports.Fp) {
    let ret = new Fp();
    ret.a_ = new Uint8Array(Mcl.fpDiv(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.Fr) {
    let ret = new Fr();
    ret.a_ = new Uint8Array(Mcl.frDiv(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.GT) {
    let ret = new GT();
    ret.a_ = new Uint8Array(Mcl.gtDiv(x.a_, y.a_));
    return ret;
  }
  if (x instanceof exports.G2) {
    let ret = new G2();
    ret.a_ = new Uint8Array(Mcl.g2Div(x.a_, y.a_));
    return ret;
  }
  throw new Error('div:bad type')
}

export const dbl = (x: any) => {
  if (x instanceof G1) {
    let ret = new G1();
    ret.a_ = new Uint8Array(Mcl.g1Inv(x.a_));
    return ret;
  }
  if (x instanceof G2) {
    let ret = new G2();
    ret.a_ = new Uint8Array(Mcl.g2Inv(x.a_));
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
    ret.a_ = Mcl.gtPow(x.a_, y.a_);
    return ret;
  }
  throw new Error('pow:bad type')
}
export const pairing = (x: G1, y: G2) => {
  if (x instanceof G1 && y instanceof G2) {
    let ret = new GT();
    ret.a_ = Mcl.pairing(x.a_, y.a_);
    return ret;
  }
  throw new Error('pow:bad type')
}
export async function init(curve = CurveType.BLS12_381): Promise<any> {
  return new Promise((res: any) => {
    Mcl.initialize(curve);
    res();
  })
}
