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

export const fromHexStr = (s: string) => {
  if (s.length & 1)
    throw new Error('fromHexStr:length must be even ' + s.length);
  const n = s.length / 2;
  const a = new Uint8Array(n);
  for (let i = 0; i < n; i++) {
    a[i] = parseInt(s.slice(i * 2, i * 2 + 2), 16);
  }
  return a;
};
