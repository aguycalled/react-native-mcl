export const toHex = (a: number[], start: number, n: number) => {
  let s = '';
  for (let i = 0; i < n; i++) {
    s += ('0' + a[start + i].toString(16)).slice(-2);
  }
  return s;
};

export const toHexStr = (a: any) => {
  return exports.toHex(a, 0, a.length);
};

export const Uint8ToUint32 = (a: Uint8Array) => {
  let ret = new Uint32Array(Math.ceil(a.length/4));
  for (let i in a) {
    // @ts-ignore
    ret[Math.floor(i/4)] |= a[i] << 8*(i%4);
  }
  return ret;
}

export const Uint32ToUint8 = (a: Uint32Array) => {
  let ret = new Uint8Array(a.length*4);
  for (let i in a) {
    // @ts-ignore
    ret[i*4] = a[i] & 0xFF;
    // @ts-ignore
    ret[i*4+1] = a[i] >> 8 & 0xFF;
    // @ts-ignore
    ret[i*4+2] = a[i] >> 16 & 0xFF;
    // @ts-ignore
    ret[i*4+3] = a[i] >> 24 & 0xFF;
  }
  return ret;
}

export const fromHexStr = (s: string) => {
  if (s.length & 1)
    throw new Error('fromHexStr:length must be even ' + s.length);
  const n = Math.ceil(s.length / 2);
  const a = new Uint8Array(n);
  //s = s.match(/[a-fA-F0-9]{2}/g)?.reverse().join('')
  for (let i = 0; i < n; i++) {
    a[i] = parseInt(s.slice(i * 2, i * 2 + 2), 16)
    //a[Math.floor(i/4)] |= parseInt(s.slice(i * 2, i * 2 + 2), 16) << 24-8*(i%4);
  }
  return a;
};
