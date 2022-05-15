#include <jni.h>
#include <mcl/bn_c384_256.h>
#include <bls/bls.h>
#include "hashes.h"
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "ReactNative", __VA_ARGS__)

////// SHA-256
namespace sha256 {
uint32_t inline Ch(uint32_t x, uint32_t y, uint32_t z) { return z ^ (x & (y ^ z)); }
uint32_t inline Maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) | (z & (x | y)); }
uint32_t inline Sigma0(uint32_t x) { return (x >> 2 | x << 30) ^ (x >> 13 | x << 19) ^ (x >> 22 | x << 10); }
uint32_t inline Sigma1(uint32_t x) { return (x >> 6 | x << 26) ^ (x >> 11 | x << 21) ^ (x >> 25 | x << 7); }
uint32_t inline sigma0(uint32_t x) { return (x >> 7 | x << 25) ^ (x >> 18 | x << 14) ^ (x >> 3); }
uint32_t inline sigma1(uint32_t x) { return (x >> 17 | x << 15) ^ (x >> 19 | x << 13) ^ (x >> 10); }

/** One round of SHA-256. */
void inline Round(uint32_t a, uint32_t b, uint32_t c, uint32_t& d, uint32_t e, uint32_t f, uint32_t g, uint32_t& h, uint32_t k)
{
    uint32_t t1 = h + Sigma1(e) + Ch(e, f, g) + k;
    uint32_t t2 = Sigma0(a) + Maj(a, b, c);
    d += t1;
    h = t1 + t2;
}

/** Initialize SHA-256 state. */
void inline Initialize(uint32_t* s)
{
    s[0] = 0x6a09e667ul;
    s[1] = 0xbb67ae85ul;
    s[2] = 0x3c6ef372ul;
    s[3] = 0xa54ff53aul;
    s[4] = 0x510e527ful;
    s[5] = 0x9b05688cul;
    s[6] = 0x1f83d9abul;
    s[7] = 0x5be0cd19ul;
}

/** Perform a number of SHA-256 transformations, processing 64-byte chunks. */
void Transform(uint32_t* s, const unsigned char* chunk, size_t blocks)
{
    while (blocks--) {
        uint32_t a = s[0], b = s[1], c = s[2], d = s[3], e = s[4], f = s[5], g = s[6], h = s[7];
        uint32_t w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15;

        Round(a, b, c, d, e, f, g, h, 0x428a2f98 + (w0 = ReadBE32(chunk + 0)));
        Round(h, a, b, c, d, e, f, g, 0x71374491 + (w1 = ReadBE32(chunk + 4)));
        Round(g, h, a, b, c, d, e, f, 0xb5c0fbcf + (w2 = ReadBE32(chunk + 8)));
        Round(f, g, h, a, b, c, d, e, 0xe9b5dba5 + (w3 = ReadBE32(chunk + 12)));
        Round(e, f, g, h, a, b, c, d, 0x3956c25b + (w4 = ReadBE32(chunk + 16)));
        Round(d, e, f, g, h, a, b, c, 0x59f111f1 + (w5 = ReadBE32(chunk + 20)));
        Round(c, d, e, f, g, h, a, b, 0x923f82a4 + (w6 = ReadBE32(chunk + 24)));
        Round(b, c, d, e, f, g, h, a, 0xab1c5ed5 + (w7 = ReadBE32(chunk + 28)));
        Round(a, b, c, d, e, f, g, h, 0xd807aa98 + (w8 = ReadBE32(chunk + 32)));
        Round(h, a, b, c, d, e, f, g, 0x12835b01 + (w9 = ReadBE32(chunk + 36)));
        Round(g, h, a, b, c, d, e, f, 0x243185be + (w10 = ReadBE32(chunk + 40)));
        Round(f, g, h, a, b, c, d, e, 0x550c7dc3 + (w11 = ReadBE32(chunk + 44)));
        Round(e, f, g, h, a, b, c, d, 0x72be5d74 + (w12 = ReadBE32(chunk + 48)));
        Round(d, e, f, g, h, a, b, c, 0x80deb1fe + (w13 = ReadBE32(chunk + 52)));
        Round(c, d, e, f, g, h, a, b, 0x9bdc06a7 + (w14 = ReadBE32(chunk + 56)));
        Round(b, c, d, e, f, g, h, a, 0xc19bf174 + (w15 = ReadBE32(chunk + 60)));

        Round(a, b, c, d, e, f, g, h, 0xe49b69c1 + (w0 += sigma1(w14) + w9 + sigma0(w1)));
        Round(h, a, b, c, d, e, f, g, 0xefbe4786 + (w1 += sigma1(w15) + w10 + sigma0(w2)));
        Round(g, h, a, b, c, d, e, f, 0x0fc19dc6 + (w2 += sigma1(w0) + w11 + sigma0(w3)));
        Round(f, g, h, a, b, c, d, e, 0x240ca1cc + (w3 += sigma1(w1) + w12 + sigma0(w4)));
        Round(e, f, g, h, a, b, c, d, 0x2de92c6f + (w4 += sigma1(w2) + w13 + sigma0(w5)));
        Round(d, e, f, g, h, a, b, c, 0x4a7484aa + (w5 += sigma1(w3) + w14 + sigma0(w6)));
        Round(c, d, e, f, g, h, a, b, 0x5cb0a9dc + (w6 += sigma1(w4) + w15 + sigma0(w7)));
        Round(b, c, d, e, f, g, h, a, 0x76f988da + (w7 += sigma1(w5) + w0 + sigma0(w8)));
        Round(a, b, c, d, e, f, g, h, 0x983e5152 + (w8 += sigma1(w6) + w1 + sigma0(w9)));
        Round(h, a, b, c, d, e, f, g, 0xa831c66d + (w9 += sigma1(w7) + w2 + sigma0(w10)));
        Round(g, h, a, b, c, d, e, f, 0xb00327c8 + (w10 += sigma1(w8) + w3 + sigma0(w11)));
        Round(f, g, h, a, b, c, d, e, 0xbf597fc7 + (w11 += sigma1(w9) + w4 + sigma0(w12)));
        Round(e, f, g, h, a, b, c, d, 0xc6e00bf3 + (w12 += sigma1(w10) + w5 + sigma0(w13)));
        Round(d, e, f, g, h, a, b, c, 0xd5a79147 + (w13 += sigma1(w11) + w6 + sigma0(w14)));
        Round(c, d, e, f, g, h, a, b, 0x06ca6351 + (w14 += sigma1(w12) + w7 + sigma0(w15)));
        Round(b, c, d, e, f, g, h, a, 0x14292967 + (w15 += sigma1(w13) + w8 + sigma0(w0)));

        Round(a, b, c, d, e, f, g, h, 0x27b70a85 + (w0 += sigma1(w14) + w9 + sigma0(w1)));
        Round(h, a, b, c, d, e, f, g, 0x2e1b2138 + (w1 += sigma1(w15) + w10 + sigma0(w2)));
        Round(g, h, a, b, c, d, e, f, 0x4d2c6dfc + (w2 += sigma1(w0) + w11 + sigma0(w3)));
        Round(f, g, h, a, b, c, d, e, 0x53380d13 + (w3 += sigma1(w1) + w12 + sigma0(w4)));
        Round(e, f, g, h, a, b, c, d, 0x650a7354 + (w4 += sigma1(w2) + w13 + sigma0(w5)));
        Round(d, e, f, g, h, a, b, c, 0x766a0abb + (w5 += sigma1(w3) + w14 + sigma0(w6)));
        Round(c, d, e, f, g, h, a, b, 0x81c2c92e + (w6 += sigma1(w4) + w15 + sigma0(w7)));
        Round(b, c, d, e, f, g, h, a, 0x92722c85 + (w7 += sigma1(w5) + w0 + sigma0(w8)));
        Round(a, b, c, d, e, f, g, h, 0xa2bfe8a1 + (w8 += sigma1(w6) + w1 + sigma0(w9)));
        Round(h, a, b, c, d, e, f, g, 0xa81a664b + (w9 += sigma1(w7) + w2 + sigma0(w10)));
        Round(g, h, a, b, c, d, e, f, 0xc24b8b70 + (w10 += sigma1(w8) + w3 + sigma0(w11)));
        Round(f, g, h, a, b, c, d, e, 0xc76c51a3 + (w11 += sigma1(w9) + w4 + sigma0(w12)));
        Round(e, f, g, h, a, b, c, d, 0xd192e819 + (w12 += sigma1(w10) + w5 + sigma0(w13)));
        Round(d, e, f, g, h, a, b, c, 0xd6990624 + (w13 += sigma1(w11) + w6 + sigma0(w14)));
        Round(c, d, e, f, g, h, a, b, 0xf40e3585 + (w14 += sigma1(w12) + w7 + sigma0(w15)));
        Round(b, c, d, e, f, g, h, a, 0x106aa070 + (w15 += sigma1(w13) + w8 + sigma0(w0)));

        Round(a, b, c, d, e, f, g, h, 0x19a4c116 + (w0 += sigma1(w14) + w9 + sigma0(w1)));
        Round(h, a, b, c, d, e, f, g, 0x1e376c08 + (w1 += sigma1(w15) + w10 + sigma0(w2)));
        Round(g, h, a, b, c, d, e, f, 0x2748774c + (w2 += sigma1(w0) + w11 + sigma0(w3)));
        Round(f, g, h, a, b, c, d, e, 0x34b0bcb5 + (w3 += sigma1(w1) + w12 + sigma0(w4)));
        Round(e, f, g, h, a, b, c, d, 0x391c0cb3 + (w4 += sigma1(w2) + w13 + sigma0(w5)));
        Round(d, e, f, g, h, a, b, c, 0x4ed8aa4a + (w5 += sigma1(w3) + w14 + sigma0(w6)));
        Round(c, d, e, f, g, h, a, b, 0x5b9cca4f + (w6 += sigma1(w4) + w15 + sigma0(w7)));
        Round(b, c, d, e, f, g, h, a, 0x682e6ff3 + (w7 += sigma1(w5) + w0 + sigma0(w8)));
        Round(a, b, c, d, e, f, g, h, 0x748f82ee + (w8 += sigma1(w6) + w1 + sigma0(w9)));
        Round(h, a, b, c, d, e, f, g, 0x78a5636f + (w9 += sigma1(w7) + w2 + sigma0(w10)));
        Round(g, h, a, b, c, d, e, f, 0x84c87814 + (w10 += sigma1(w8) + w3 + sigma0(w11)));
        Round(f, g, h, a, b, c, d, e, 0x8cc70208 + (w11 += sigma1(w9) + w4 + sigma0(w12)));
        Round(e, f, g, h, a, b, c, d, 0x90befffa + (w12 += sigma1(w10) + w5 + sigma0(w13)));
        Round(d, e, f, g, h, a, b, c, 0xa4506ceb + (w13 += sigma1(w11) + w6 + sigma0(w14)));
        Round(c, d, e, f, g, h, a, b, 0xbef9a3f7 + (w14 + sigma1(w12) + w7 + sigma0(w15)));
        Round(b, c, d, e, f, g, h, a, 0xc67178f2 + (w15 + sigma1(w13) + w8 + sigma0(w0)));

        s[0] += a;
        s[1] += b;
        s[2] += c;
        s[3] += d;
        s[4] += e;
        s[5] += f;
        s[6] += g;
        s[7] += h;
        chunk += 64;
    }
}
}

namespace ripemd160
{
uint32_t inline f1(uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; }
uint32_t inline f2(uint32_t x, uint32_t y, uint32_t z) { return (x & y) | (~x & z); }
uint32_t inline f3(uint32_t x, uint32_t y, uint32_t z) { return (x | ~y) ^ z; }
uint32_t inline f4(uint32_t x, uint32_t y, uint32_t z) { return (x & z) | (y & ~z); }
uint32_t inline f5(uint32_t x, uint32_t y, uint32_t z) { return x ^ (y | ~z); }

/** Initialize RIPEMD-160 state. */
void inline Initialize(uint32_t* s)
{
    s[0] = 0x67452301ul;
    s[1] = 0xEFCDAB89ul;
    s[2] = 0x98BADCFEul;
    s[3] = 0x10325476ul;
    s[4] = 0xC3D2E1F0ul;
}

uint32_t inline rol(uint32_t x, int i) { return (x << i) | (x >> (32 - i)); }

void inline Round(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t f, uint32_t x, uint32_t k, int r)
{
    a = rol(a + f + x + k, r) + e;
    c = rol(c, 10);
}

void inline R11(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t x, int r) { Round(a, b, c, d, e, f1(b, c, d), x, 0, r); }
void inline R21(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t x, int r) { Round(a, b, c, d, e, f2(b, c, d), x, 0x5A827999ul, r); }
void inline R31(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t x, int r) { Round(a, b, c, d, e, f3(b, c, d), x, 0x6ED9EBA1ul, r); }
void inline R41(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t x, int r) { Round(a, b, c, d, e, f4(b, c, d), x, 0x8F1BBCDCul, r); }
void inline R51(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t x, int r) { Round(a, b, c, d, e, f5(b, c, d), x, 0xA953FD4Eul, r); }

void inline R12(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t x, int r) { Round(a, b, c, d, e, f5(b, c, d), x, 0x50A28BE6ul, r); }
void inline R22(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t x, int r) { Round(a, b, c, d, e, f4(b, c, d), x, 0x5C4DD124ul, r); }
void inline R32(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t x, int r) { Round(a, b, c, d, e, f3(b, c, d), x, 0x6D703EF3ul, r); }
void inline R42(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t x, int r) { Round(a, b, c, d, e, f2(b, c, d), x, 0x7A6D76E9ul, r); }
void inline R52(uint32_t& a, uint32_t b, uint32_t& c, uint32_t d, uint32_t e, uint32_t x, int r) { Round(a, b, c, d, e, f1(b, c, d), x, 0, r); }

/** Perform a RIPEMD-160 transformation, processing a 64-byte chunk. */
void Transform(uint32_t* s, const unsigned char* chunk)
{
    uint32_t a1 = s[0], b1 = s[1], c1 = s[2], d1 = s[3], e1 = s[4];
    uint32_t a2 = a1, b2 = b1, c2 = c1, d2 = d1, e2 = e1;
    uint32_t w0 = ReadLE32(chunk + 0), w1 = ReadLE32(chunk + 4), w2 = ReadLE32(chunk + 8), w3 = ReadLE32(chunk + 12);
    uint32_t w4 = ReadLE32(chunk + 16), w5 = ReadLE32(chunk + 20), w6 = ReadLE32(chunk + 24), w7 = ReadLE32(chunk + 28);
    uint32_t w8 = ReadLE32(chunk + 32), w9 = ReadLE32(chunk + 36), w10 = ReadLE32(chunk + 40), w11 = ReadLE32(chunk + 44);
    uint32_t w12 = ReadLE32(chunk + 48), w13 = ReadLE32(chunk + 52), w14 = ReadLE32(chunk + 56), w15 = ReadLE32(chunk + 60);

    R11(a1, b1, c1, d1, e1, w0, 11);
    R12(a2, b2, c2, d2, e2, w5, 8);
    R11(e1, a1, b1, c1, d1, w1, 14);
    R12(e2, a2, b2, c2, d2, w14, 9);
    R11(d1, e1, a1, b1, c1, w2, 15);
    R12(d2, e2, a2, b2, c2, w7, 9);
    R11(c1, d1, e1, a1, b1, w3, 12);
    R12(c2, d2, e2, a2, b2, w0, 11);
    R11(b1, c1, d1, e1, a1, w4, 5);
    R12(b2, c2, d2, e2, a2, w9, 13);
    R11(a1, b1, c1, d1, e1, w5, 8);
    R12(a2, b2, c2, d2, e2, w2, 15);
    R11(e1, a1, b1, c1, d1, w6, 7);
    R12(e2, a2, b2, c2, d2, w11, 15);
    R11(d1, e1, a1, b1, c1, w7, 9);
    R12(d2, e2, a2, b2, c2, w4, 5);
    R11(c1, d1, e1, a1, b1, w8, 11);
    R12(c2, d2, e2, a2, b2, w13, 7);
    R11(b1, c1, d1, e1, a1, w9, 13);
    R12(b2, c2, d2, e2, a2, w6, 7);
    R11(a1, b1, c1, d1, e1, w10, 14);
    R12(a2, b2, c2, d2, e2, w15, 8);
    R11(e1, a1, b1, c1, d1, w11, 15);
    R12(e2, a2, b2, c2, d2, w8, 11);
    R11(d1, e1, a1, b1, c1, w12, 6);
    R12(d2, e2, a2, b2, c2, w1, 14);
    R11(c1, d1, e1, a1, b1, w13, 7);
    R12(c2, d2, e2, a2, b2, w10, 14);
    R11(b1, c1, d1, e1, a1, w14, 9);
    R12(b2, c2, d2, e2, a2, w3, 12);
    R11(a1, b1, c1, d1, e1, w15, 8);
    R12(a2, b2, c2, d2, e2, w12, 6);

    R21(e1, a1, b1, c1, d1, w7, 7);
    R22(e2, a2, b2, c2, d2, w6, 9);
    R21(d1, e1, a1, b1, c1, w4, 6);
    R22(d2, e2, a2, b2, c2, w11, 13);
    R21(c1, d1, e1, a1, b1, w13, 8);
    R22(c2, d2, e2, a2, b2, w3, 15);
    R21(b1, c1, d1, e1, a1, w1, 13);
    R22(b2, c2, d2, e2, a2, w7, 7);
    R21(a1, b1, c1, d1, e1, w10, 11);
    R22(a2, b2, c2, d2, e2, w0, 12);
    R21(e1, a1, b1, c1, d1, w6, 9);
    R22(e2, a2, b2, c2, d2, w13, 8);
    R21(d1, e1, a1, b1, c1, w15, 7);
    R22(d2, e2, a2, b2, c2, w5, 9);
    R21(c1, d1, e1, a1, b1, w3, 15);
    R22(c2, d2, e2, a2, b2, w10, 11);
    R21(b1, c1, d1, e1, a1, w12, 7);
    R22(b2, c2, d2, e2, a2, w14, 7);
    R21(a1, b1, c1, d1, e1, w0, 12);
    R22(a2, b2, c2, d2, e2, w15, 7);
    R21(e1, a1, b1, c1, d1, w9, 15);
    R22(e2, a2, b2, c2, d2, w8, 12);
    R21(d1, e1, a1, b1, c1, w5, 9);
    R22(d2, e2, a2, b2, c2, w12, 7);
    R21(c1, d1, e1, a1, b1, w2, 11);
    R22(c2, d2, e2, a2, b2, w4, 6);
    R21(b1, c1, d1, e1, a1, w14, 7);
    R22(b2, c2, d2, e2, a2, w9, 15);
    R21(a1, b1, c1, d1, e1, w11, 13);
    R22(a2, b2, c2, d2, e2, w1, 13);
    R21(e1, a1, b1, c1, d1, w8, 12);
    R22(e2, a2, b2, c2, d2, w2, 11);

    R31(d1, e1, a1, b1, c1, w3, 11);
    R32(d2, e2, a2, b2, c2, w15, 9);
    R31(c1, d1, e1, a1, b1, w10, 13);
    R32(c2, d2, e2, a2, b2, w5, 7);
    R31(b1, c1, d1, e1, a1, w14, 6);
    R32(b2, c2, d2, e2, a2, w1, 15);
    R31(a1, b1, c1, d1, e1, w4, 7);
    R32(a2, b2, c2, d2, e2, w3, 11);
    R31(e1, a1, b1, c1, d1, w9, 14);
    R32(e2, a2, b2, c2, d2, w7, 8);
    R31(d1, e1, a1, b1, c1, w15, 9);
    R32(d2, e2, a2, b2, c2, w14, 6);
    R31(c1, d1, e1, a1, b1, w8, 13);
    R32(c2, d2, e2, a2, b2, w6, 6);
    R31(b1, c1, d1, e1, a1, w1, 15);
    R32(b2, c2, d2, e2, a2, w9, 14);
    R31(a1, b1, c1, d1, e1, w2, 14);
    R32(a2, b2, c2, d2, e2, w11, 12);
    R31(e1, a1, b1, c1, d1, w7, 8);
    R32(e2, a2, b2, c2, d2, w8, 13);
    R31(d1, e1, a1, b1, c1, w0, 13);
    R32(d2, e2, a2, b2, c2, w12, 5);
    R31(c1, d1, e1, a1, b1, w6, 6);
    R32(c2, d2, e2, a2, b2, w2, 14);
    R31(b1, c1, d1, e1, a1, w13, 5);
    R32(b2, c2, d2, e2, a2, w10, 13);
    R31(a1, b1, c1, d1, e1, w11, 12);
    R32(a2, b2, c2, d2, e2, w0, 13);
    R31(e1, a1, b1, c1, d1, w5, 7);
    R32(e2, a2, b2, c2, d2, w4, 7);
    R31(d1, e1, a1, b1, c1, w12, 5);
    R32(d2, e2, a2, b2, c2, w13, 5);

    R41(c1, d1, e1, a1, b1, w1, 11);
    R42(c2, d2, e2, a2, b2, w8, 15);
    R41(b1, c1, d1, e1, a1, w9, 12);
    R42(b2, c2, d2, e2, a2, w6, 5);
    R41(a1, b1, c1, d1, e1, w11, 14);
    R42(a2, b2, c2, d2, e2, w4, 8);
    R41(e1, a1, b1, c1, d1, w10, 15);
    R42(e2, a2, b2, c2, d2, w1, 11);
    R41(d1, e1, a1, b1, c1, w0, 14);
    R42(d2, e2, a2, b2, c2, w3, 14);
    R41(c1, d1, e1, a1, b1, w8, 15);
    R42(c2, d2, e2, a2, b2, w11, 14);
    R41(b1, c1, d1, e1, a1, w12, 9);
    R42(b2, c2, d2, e2, a2, w15, 6);
    R41(a1, b1, c1, d1, e1, w4, 8);
    R42(a2, b2, c2, d2, e2, w0, 14);
    R41(e1, a1, b1, c1, d1, w13, 9);
    R42(e2, a2, b2, c2, d2, w5, 6);
    R41(d1, e1, a1, b1, c1, w3, 14);
    R42(d2, e2, a2, b2, c2, w12, 9);
    R41(c1, d1, e1, a1, b1, w7, 5);
    R42(c2, d2, e2, a2, b2, w2, 12);
    R41(b1, c1, d1, e1, a1, w15, 6);
    R42(b2, c2, d2, e2, a2, w13, 9);
    R41(a1, b1, c1, d1, e1, w14, 8);
    R42(a2, b2, c2, d2, e2, w9, 12);
    R41(e1, a1, b1, c1, d1, w5, 6);
    R42(e2, a2, b2, c2, d2, w7, 5);
    R41(d1, e1, a1, b1, c1, w6, 5);
    R42(d2, e2, a2, b2, c2, w10, 15);
    R41(c1, d1, e1, a1, b1, w2, 12);
    R42(c2, d2, e2, a2, b2, w14, 8);

    R51(b1, c1, d1, e1, a1, w4, 9);
    R52(b2, c2, d2, e2, a2, w12, 8);
    R51(a1, b1, c1, d1, e1, w0, 15);
    R52(a2, b2, c2, d2, e2, w15, 5);
    R51(e1, a1, b1, c1, d1, w5, 5);
    R52(e2, a2, b2, c2, d2, w10, 12);
    R51(d1, e1, a1, b1, c1, w9, 11);
    R52(d2, e2, a2, b2, c2, w4, 9);
    R51(c1, d1, e1, a1, b1, w7, 6);
    R52(c2, d2, e2, a2, b2, w1, 12);
    R51(b1, c1, d1, e1, a1, w12, 8);
    R52(b2, c2, d2, e2, a2, w5, 5);
    R51(a1, b1, c1, d1, e1, w2, 13);
    R52(a2, b2, c2, d2, e2, w8, 14);
    R51(e1, a1, b1, c1, d1, w10, 12);
    R52(e2, a2, b2, c2, d2, w7, 6);
    R51(d1, e1, a1, b1, c1, w14, 5);
    R52(d2, e2, a2, b2, c2, w6, 8);
    R51(c1, d1, e1, a1, b1, w1, 12);
    R52(c2, d2, e2, a2, b2, w2, 13);
    R51(b1, c1, d1, e1, a1, w3, 13);
    R52(b2, c2, d2, e2, a2, w13, 6);
    R51(a1, b1, c1, d1, e1, w8, 14);
    R52(a2, b2, c2, d2, e2, w14, 5);
    R51(e1, a1, b1, c1, d1, w11, 11);
    R52(e2, a2, b2, c2, d2, w0, 15);
    R51(d1, e1, a1, b1, c1, w6, 8);
    R52(d2, e2, a2, b2, c2, w3, 13);
    R51(c1, d1, e1, a1, b1, w15, 5);
    R52(c2, d2, e2, a2, b2, w9, 11);
    R51(b1, c1, d1, e1, a1, w13, 6);
    R52(b2, c2, d2, e2, a2, w11, 11);

    uint32_t t = s[0];
    s[0] = s[1] + c1 + d2;
    s[1] = s[2] + d1 + e2;
    s[2] = s[3] + e1 + a2;
    s[3] = s[4] + a1 + b2;
    s[4] = t + b1 + c2;
}

} // namespace ripemd160

////// RIPEMD160

CRIPEMD160::CRIPEMD160() : bytes(0)
{
    ripemd160::Initialize(s);
}

CRIPEMD160& CRIPEMD160::Write(const unsigned char* data, size_t len)
{
    const unsigned char* end = data + len;
    size_t bufsize = bytes % 64;
    if (bufsize && bufsize + len >= 64) {
        // Fill the buffer, and process it.
        memcpy(buf + bufsize, data, 64 - bufsize);
        bytes += 64 - bufsize;
        data += 64 - bufsize;
        ripemd160::Transform(s, buf);
        bufsize = 0;
    }
    while (end - data >= 64) {
        // Process full chunks directly from the source.
        ripemd160::Transform(s, data);
        bytes += 64;
        data += 64;
    }
    if (end > data) {
        // Fill the buffer with what remains.
        memcpy(buf + bufsize, data, end - data);
        bytes += end - data;
    }
    return *this;
}

void CRIPEMD160::Finalize(unsigned char hash[OUTPUT_SIZE])
{
    static const unsigned char pad[64] = {0x80};
    unsigned char sizedesc[8];
    WriteLE64(sizedesc, bytes << 3);
    Write(pad, 1 + ((119 - (bytes % 64)) % 64));
    Write(sizedesc, 8);
    WriteLE32(hash, s[0]);
    WriteLE32(hash + 4, s[1]);
    WriteLE32(hash + 8, s[2]);
    WriteLE32(hash + 12, s[3]);
    WriteLE32(hash + 16, s[4]);
}

CRIPEMD160& CRIPEMD160::Reset()
{
    bytes = 0;
    ripemd160::Initialize(s);
    return *this;
}

CSHA256::CSHA256() : bytes(0)
{
    sha256::Initialize(s);
}

CSHA256& CSHA256::Write(const unsigned char* data, size_t len)
{
    const unsigned char* end = data + len;
    size_t bufsize = bytes % 64;
    if (bufsize && bufsize + len >= 64) {
        // Fill the buffer, and process it.
        memcpy(buf + bufsize, data, 64 - bufsize);
        bytes += 64 - bufsize;
        data += 64 - bufsize;
        sha256::Transform(s, buf, 1);
        bufsize = 0;
    }
    if (end - data >= 64) {
        size_t blocks = (end - data) / 64;
        sha256::Transform(s, data, blocks);
        data += 64 * blocks;
        bytes += 64 * blocks;
    }
    if (end > data) {
        // Fill the buffer with what remains.
        memcpy(buf + bufsize, data, end - data);
        bytes += end - data;
    }
    return *this;
}

void CSHA256::Finalize(unsigned char hash[OUTPUT_SIZE])
{
    static const unsigned char pad[64] = {0x80};
    unsigned char sizedesc[8];
    WriteBE64(sizedesc, bytes << 3);
    Write(pad, 1 + ((119 - (bytes % 64)) % 64));
    Write(sizedesc, 8);
    WriteBE32(hash, s[0]);
    WriteBE32(hash + 4, s[1]);
    WriteBE32(hash + 8, s[2]);
    WriteBE32(hash + 12, s[3]);
    WriteBE32(hash + 16, s[4]);
    WriteBE32(hash + 20, s[5]);
    WriteBE32(hash + 24, s[6]);
    WriteBE32(hash + 28, s[7]);
}

CSHA256& CSHA256::Reset()
{
    bytes = 0;
    sha256::Initialize(s);
    return *this;
}

extern "C"
{

// PublicKey

blsPublicKey jintArrayToPk(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  blsPublicKey pk;
  blsPublicKeyDeserialize(&pk, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return pk;
}

jintArray pkToJintArray(JNIEnv* env, const blsPublicKey& pk)
{
  unsigned char ba[3096];
  int baLen = blsPublicKeySerialize(&ba[0], 3096, &pk);

  jint bab[baLen];

  for (int i = 0; i < baLen; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(baLen);

  env->SetIntArrayRegion(ret, 0, baLen, &bab[0]);

  return ret;
}

// SecretKey

blsSecretKey jintArrayToSk(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  blsSecretKey sk;
  blsSecretKeyDeserialize(&sk, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return sk;
}

jintArray skToJintArray(JNIEnv* env, const blsSecretKey& sk)
{
  unsigned char ba[3096];
  int baLen = blsSecretKeySerialize(&ba[0], 3096, &sk);

  jint bab[baLen];

  for (int i = 0; i < baLen; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(baLen);

  env->SetIntArrayRegion(ret, 0, baLen, &bab[0]);

  return ret;
}

// Signature

blsSignature jintArrayToSig(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  blsSignature sig;
  blsSignatureDeserialize(&sig, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return sig;
}

jintArray sigToJintArray(JNIEnv* env, const blsSignature& sig)
{
  unsigned char ba[3096];
  int baLen = blsSignatureSerialize(&ba[0], 3096, &sig);

  jint bab[baLen];

  for (int i = 0; i < baLen; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(baLen);

  env->SetIntArrayRegion(ret, 0, baLen, &bab[0]);

  return ret;
}

// Fr

mclBnFr jintArrayToFrDeser(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
    LOGI(" frdeser %d %x", i, b[i] & 0xFF);
  }

  mclBnFr fr;
  mclBnFr_deserialize(&fr, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return fr;
}

mclBnFr jintArrayToFr(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnFr fr;
  memcpy(&fr, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return fr;
}

jintArray frToJintArray(JNIEnv* env, const mclBnFr& fr)
{
  unsigned char ba[32];
  memcpy(&ba[0], &fr, 32);

  jint bab[32];

  for (int i = 0; i < 32; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(32);
  env->SetIntArrayRegion(ret, 0, 32, &bab[0]);

  return ret;
}

jintArray frToJintArraySer(JNIEnv* env, const mclBnFr& fr)
{
  unsigned char ba[3096];
  int baLen = mclBnFr_serialize(&ba[0], 3096, &fr);

  jint bab[baLen];

  for (int i = 0; i < baLen; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(baLen);

  env->SetIntArrayRegion(ret, 0, baLen, &bab[0]);

  return ret;
}


// Fp

mclBnFp jintArrayToFpDeser(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnFp fp;
  mclBnFp_deserialize(&fp, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return fp;
}

mclBnFp jintArrayToFp(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnFp fp;
  memcpy(&fp, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return fp;
}

jintArray fpToJintArray(JNIEnv* env, const mclBnFp& fp)
{
  unsigned char ba[48];
  memcpy(&ba[0], &fp, 48);

  jint bab[48];

  for (int i = 0; i < 48; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(48);
  env->SetIntArrayRegion(ret, 0, 48, &bab[0]);

  return ret;
}

jintArray fpToJintArraySer(JNIEnv* env, const mclBnFp& fp)
{
  unsigned char ba[3096];
  int baLen = mclBnFp_serialize(&ba[0], 3096, &fp);

  jint bab[baLen];

  for (int i = 0; i < baLen; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(baLen);

  env->SetIntArrayRegion(ret, 0, baLen, &bab[0]);

  return ret;
}

// Fp2

mclBnFp2 jintArrayToFp2Deser(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnFp2 fp2;
  mclBnFp2_deserialize(&fp2, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return fp2;
}

mclBnFp2 jintArrayToFp2(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnFp2 fp2;
  memcpy(&fp2, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return fp2;
}

jintArray fp2ToJintArray(JNIEnv* env, const mclBnFp2& fp2)
{
  unsigned char ba[96];
  memcpy(&ba[0], &fp2, 96);

  jint bab[96];

  for (int i = 0; i < 96; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(96);
  env->SetIntArrayRegion(ret, 0, 96, &bab[0]);

  return ret;
}

jintArray fp2ToJintArraySer(JNIEnv* env, const mclBnFp2& fp2)
{
  unsigned char ba[3096];
  int baLen = mclBnFp2_serialize(&ba[0], 3096, &fp2);

  jint bab[baLen];

  for (int i = 0; i < baLen; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(baLen);

  env->SetIntArrayRegion(ret, 0, baLen, &bab[0]);

  return ret;
}


// G1

mclBnG1 jintArrayToG1Deser(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnG1 g1;
  mclBnG1_deserialize(&g1, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return g1;
}

mclBnG1 jintArrayToG1(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnG1 g1;
  memcpy(&g1, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return g1;
}

jintArray g1ToJintArray(JNIEnv* env, const mclBnG1& g1)
{
  unsigned char ba[48*3];
  memcpy(&ba[0], &g1, 48*3);

  jint bab[48*3];

  for (int i = 0; i < 48*3; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(48*3);
  env->SetIntArrayRegion(ret, 0, 48*3, &bab[0]);

  return ret;
}

jintArray g1ToJintArraySer(JNIEnv* env, const mclBnG1& g1)
{
  unsigned char ba[3096];
  int baLen = mclBnG1_serialize(&ba[0], 3096, &g1);

  jint bab[baLen];

  for (int i = 0; i < baLen; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(baLen);

  env->SetIntArrayRegion(ret, 0, baLen, &bab[0]);

  return ret;
}

// G2

mclBnG2 jintArrayToG2Deser(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnG2 g2;
  mclBnG2_deserialize(&g2, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return g2;
}

mclBnG2 jintArrayToG2(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnG2 g2;
  memcpy(&g2, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return g2;
}

jintArray g2ToJintArray(JNIEnv* env, const mclBnG2& g2)
{
  unsigned char ba[96*3];
  memcpy(&ba[0], &g2, 96*3);

  jint bab[96*3];

  for (int i = 0; i < 96*3; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(96*3);
  env->SetIntArrayRegion(ret, 0, 96*3, &bab[0]);

  return ret;
}

jintArray g2ToJintArraySer(JNIEnv* env, const mclBnG2& g2)
{
  unsigned char ba[3096];
  int baLen = mclBnG2_serialize(&ba[0], 3096, &g2);

  jint bab[baLen];

  for (int i = 0; i < baLen; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(baLen);

  env->SetIntArrayRegion(ret, 0, baLen, &bab[0]);

  return ret;
}

// GT

mclBnGT jintArrayToGTDeser(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnGT gt;
  mclBnGT_deserialize(&gt, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return gt;
}

mclBnGT jintArrayToGT(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  mclBnGT gt;
  memcpy(&gt, bb, len);

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return gt;
}

jintArray gtToJintArray(JNIEnv* env, const mclBnGT& gt)
{
  unsigned char ba[4*48*3];
  memcpy(&ba[0], &gt, 4*48*3);

  jint bab[4*48*3];

  for (int i = 0; i < 4*48*3; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(4*48*3);
  env->SetIntArrayRegion(ret, 0, 4*48*3, &bab[0]);

  return ret;
}

jintArray gtToJintArraySer(JNIEnv* env, const mclBnGT& gt)
{
  unsigned char ba[3096];
  int baLen = mclBnGT_serialize(&ba[0], 3096, &gt);

  jint bab[baLen];

  for (int i = 0; i < baLen; i++){
    bab[i] = ba[i];
  }

  jintArray ret = env->NewIntArray(baLen);

  env->SetIntArrayRegion(ret, 0, baLen, &bab[0]);

  return ret;
}

unsigned char* jintArrayToIntArray(JNIEnv* env, jintArray *a, jsize len)
{
  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char* bb = (unsigned char*)calloc(len, sizeof(unsigned char));

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
  }

  env->ReleaseIntArrayElements (*a, b, JNI_ABORT);

  return bb;
}

// Fr

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frDeserialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr = jintArrayToFrDeser(env, &a);

  jintArray ret = frToJintArray(env, fr);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frSetLittleEndian(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr;
  jsize len = env->GetArrayLength(a);
  unsigned char * array = jintArrayToIntArray(env, &a, len);

  mclBnFr_setLittleEndian(&fr, array, len);
  jintArray ret = frToJintArray(env, fr);

  free(array);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frSetLittleEndianMod(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr;
  jsize len = env->GetArrayLength(a);
  unsigned char * array = jintArrayToIntArray(env, &a, len);

  mclBnFr_setLittleEndianMod(&fr, array, len);
  jintArray ret = frToJintArray(env, fr);

  free(array);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frSetBigEndianMod(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr;
  jsize len = env->GetArrayLength(a);
  unsigned char * array = jintArrayToIntArray(env, &a, len);

  mclBnFr_setBigEndianMod(&fr, array, len);
  jintArray ret = frToJintArray(env, fr);

  free(array);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frSetHashOf(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr;
  jsize len = env->GetArrayLength(a);
  unsigned char * array = jintArrayToIntArray(env, &a, len);

  mclBnFr_setHashOf(&fr, array, len);
  jintArray ret = frToJintArray(env, fr);

  free(array);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frSerialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr = jintArrayToFr(env, &a);

  jintArray ret = frToJintArraySer(env, fr);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frSetInt32(JNIEnv *env, jclass type, jint a) {
  mclBnFr fr;
  mclBnFr_setInt32(&fr, (int)a);

  jintArray ret = frToJintArray(env, fr);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frSetStr(JNIEnv *env, jclass type, jstring a, jint b) {
  const char *c_str;

  c_str = env->GetStringUTFChars (a, NULL);

  mclBnFr fr;
  mclBnFr_setStr(&fr, c_str, strlen(c_str), (int)b);

  jintArray ret = frToJintArray(env, fr);

  env->ReleaseStringUTFChars (a, c_str);

  return ret;
}

JNIEXPORT jstring JNICALL
Java_com_reactnativemcl_MclModule__1frGetStr(JNIEnv *env, jclass type, jintArray a, jint b) {
  mclBnFr fr = jintArrayToFr(env, &a);

  char buf[1024];
  mclBnFr_getStr(buf, sizeof(buf), &fr, (int)b);

  return env->NewStringUTF (buf);
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1frIsZero(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr = jintArrayToFr(env, &a);

  jint ret = mclBnFr_isZero(&fr);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1frIsOne(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr = jintArrayToFr(env, &a);

  jint ret = mclBnFr_isOne(&fr);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1frIsEqual(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFr fr = jintArrayToFr(env, &a);
  mclBnFr fr2 = jintArrayToFr(env, &b);

  jint ret = mclBnFr_isEqual(&fr, &fr2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frNeg(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr = jintArrayToFr(env, &a);

  mclBnFr fr2;
  mclBnFr_neg(&fr2, &fr);

  jintArray ret = frToJintArray(env, fr2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frSqr(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr = jintArrayToFr(env, &a);

  mclBnFr fr2;
  mclBnFr_sqr(&fr2, &fr);

  jintArray ret = frToJintArray(env, fr2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frInv(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr = jintArrayToFr(env, &a);

  mclBnFr fr2;
  mclBnFr_inv(&fr2, &fr);

  jintArray ret = frToJintArray(env, fr2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frSquareRoot(JNIEnv *env, jclass type, jintArray a) {
  mclBnFr fr = jintArrayToFr(env, &a);

  mclBnFr fr2;
  mclBnFr_squareRoot(&fr2, &fr);

  jintArray ret = frToJintArray(env, fr2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frAdd(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFr fr = jintArrayToFr(env, &a);
  mclBnFr fr2 = jintArrayToFr(env, &b);

  mclBnFr result;
  mclBnFr_add(&result, &fr, &fr2);

  jintArray ret = frToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frSub(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFr fr = jintArrayToFr(env, &a);
  mclBnFr fr2 = jintArrayToFr(env, &b);

  mclBnFr result;
  mclBnFr_sub(&result, &fr, &fr2);

  jintArray ret = frToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frMul(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFr fr = jintArrayToFr(env, &a);
  mclBnFr fr2 = jintArrayToFr(env, &b);

  mclBnFr result;
  mclBnFr_mul(&result, &fr, &fr2);

  jintArray ret = frToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1frDiv(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFr fr = jintArrayToFr(env, &a);
  mclBnFr fr2 = jintArrayToFr(env, &b);

  mclBnFr result;
  mclBnFr_div(&result, &fr, &fr2);

  jintArray ret = frToJintArray(env, result);

  return ret;
}

// Fp

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpDeserialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp = jintArrayToFpDeser(env, &a);

  jintArray ret = fpToJintArray(env, fp);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpSetLittleEndian(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp;
  jsize len = env->GetArrayLength(a);
  unsigned char * array = jintArrayToIntArray(env, &a, len);

  mclBnFp_setLittleEndian(&fp, array, len);
  jintArray ret = fpToJintArray(env, fp);

  free(array);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpSetLittleEndianMod(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp;
  jsize len = env->GetArrayLength(a);
  unsigned char * array = jintArrayToIntArray(env, &a, len);

  mclBnFp_setLittleEndianMod(&fp, array, len);
  jintArray ret = fpToJintArray(env, fp);

  free(array);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpSetBigEndianMod(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp;
  jsize len = env->GetArrayLength(a);
  unsigned char * array = jintArrayToIntArray(env, &a, len);

  mclBnFp_setBigEndianMod(&fp, array, len);
  jintArray ret = fpToJintArray(env, fp);

  free(array);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpSetHashOf(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp;
  jsize len = env->GetArrayLength(a);
  unsigned char * array = jintArrayToIntArray(env, &a, len);

  mclBnFp_setHashOf(&fp, array, len);
  jintArray ret = fpToJintArray(env, fp);

  free(array);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpSerialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp = jintArrayToFp(env, &a);

  jintArray ret = fpToJintArraySer(env, fp);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpSetInt32(JNIEnv *env, jclass type, jint a) {
  mclBnFp fp;
  mclBnFp_setInt32(&fp, (int)a);

  jintArray ret = fpToJintArray(env, fp);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpSetStr(JNIEnv *env, jclass type, jstring a, jint b) {
  const char *c_str;

  c_str = env->GetStringUTFChars (a, NULL);

  mclBnFp fp;
  mclBnFp_setStr(&fp, c_str, strlen(c_str), (int)b);

  jintArray ret = fpToJintArray(env, fp);

  env->ReleaseStringUTFChars (a, c_str);

  return ret;
}

JNIEXPORT jstring JNICALL
Java_com_reactnativemcl_MclModule__1fpGetStr(JNIEnv *env, jclass type, jintArray a, jint b) {
  mclBnFp fp = jintArrayToFp(env, &a);

  char buf[1024];
  mclBnFp_getStr(buf, sizeof(buf), &fp, (int)b);

  return env->NewStringUTF (buf);
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1fpIsZero(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp = jintArrayToFp(env, &a);

  jint ret = mclBnFp_isZero(&fp);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1fpIsOne(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp = jintArrayToFp(env, &a);

  jint ret = mclBnFp_isOne(&fp);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1fpIsEqual(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFp fp = jintArrayToFp(env, &a);
  mclBnFp fp2 = jintArrayToFp(env, &b);

  jint ret = mclBnFp_isEqual(&fp, &fp2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpNeg(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp = jintArrayToFp(env, &a);

  mclBnFp fp2;
  mclBnFp_neg(&fp2, &fp);

  jintArray ret = fpToJintArray(env, fp2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpSqr(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp = jintArrayToFp(env, &a);

  mclBnFp fp2;
  mclBnFp_sqr(&fp2, &fp);

  jintArray ret = fpToJintArray(env, fp2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpInv(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp = jintArrayToFp(env, &a);

  mclBnFp fp2;
  mclBnFp_inv(&fp2, &fp);

  jintArray ret = fpToJintArray(env, fp2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpMapToG1(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp = jintArrayToFp(env, &a);

  mclBnG1 g1;
  mclBnFp_mapToG1(&g1, &fp);

  jintArray ret = g1ToJintArray(env, g1);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpSquareRoot(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp fp = jintArrayToFp(env, &a);

  mclBnFp fp2;
  mclBnFp_squareRoot(&fp2, &fp);

  jintArray ret = fpToJintArray(env, fp2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpAdd(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFp fp = jintArrayToFp(env, &a);
  mclBnFp fp2 = jintArrayToFp(env, &b);

  mclBnFp result;
  mclBnFp_add(&result, &fp, &fp2);

  jintArray ret = fpToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpSub(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFp fp = jintArrayToFp(env, &a);
  mclBnFp fp2 = jintArrayToFp(env, &b);

  mclBnFp result;
  mclBnFp_sub(&result, &fp, &fp2);

  jintArray ret = fpToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpMul(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFp fp = jintArrayToFp(env, &a);
  mclBnFp fp2 = jintArrayToFp(env, &b);

  mclBnFp result;
  mclBnFp_mul(&result, &fp, &fp2);

  jintArray ret = fpToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fpDiv(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFp fp = jintArrayToFp(env, &a);
  mclBnFp fp2 = jintArrayToFp(env, &b);

  mclBnFp result;
  mclBnFp_div(&result, &fp, &fp2);

  jintArray ret = fpToJintArray(env, result);

  return ret;
}

// Fp2

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2Deserialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp2 fp2 = jintArrayToFp2Deser(env, &a);

  jintArray ret = fp2ToJintArray(env, fp2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2Serialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);

  jintArray ret = fp2ToJintArraySer(env, fp2);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1fp2IsZero(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);

  jint ret = mclBnFp2_isZero(&fp2);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1fp2IsOne(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);

  jint ret = mclBnFp2_isOne(&fp2);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1fp2IsEqual(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);
  mclBnFp2 fp22 = jintArrayToFp2(env, &b);

  jint ret = mclBnFp2_isEqual(&fp2, &fp22);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2Neg(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);

  mclBnFp2 fp22;
  mclBnFp2_neg(&fp22, &fp2);

  jintArray ret = fp2ToJintArray(env, fp22);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2Sqr(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);

  mclBnFp2 fp22;
  mclBnFp2_sqr(&fp22, &fp2);

  jintArray ret = fp2ToJintArray(env, fp22);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2Inv(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);

  mclBnFp2 fp22;
  mclBnFp2_inv(&fp22, &fp2);

  jintArray ret = fp2ToJintArray(env, fp22);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2MapToG2(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);

  mclBnG2 g2;
  mclBnFp2_mapToG2(&g2, &fp2);

  jintArray ret = g2ToJintArray(env, g2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2SquareRoot(JNIEnv *env, jclass type, jintArray a) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);

  mclBnFp2 fp22;
  mclBnFp2_squareRoot(&fp22, &fp2);

  jintArray ret = fp2ToJintArray(env, fp22);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2Add(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);
  mclBnFp2 fp22 = jintArrayToFp2(env, &b);

  mclBnFp2 result;
  mclBnFp2_add(&result, &fp2, &fp22);

  jintArray ret = fp2ToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2Sub(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);
  mclBnFp2 fp22 = jintArrayToFp2(env, &b);

  mclBnFp2 result;
  mclBnFp2_sub(&result, &fp2, &fp22);

  jintArray ret = fp2ToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2Mul(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);
  mclBnFp2 fp22 = jintArrayToFp2(env, &b);

  mclBnFp2 result;
  mclBnFp2_mul(&result, &fp2, &fp22);

  jintArray ret = fp2ToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1fp2Div(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnFp2 fp2 = jintArrayToFp2(env, &a);
  mclBnFp2 fp22 = jintArrayToFp2(env, &b);

  mclBnFp2 result;
  mclBnFp2_div(&result, &fp2, &fp22);

  jintArray ret = fp2ToJintArray(env, result);

  return ret;
}

// G1

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1Deserialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnG1 g1 = jintArrayToG1Deser(env, &a);

  jintArray ret = g1ToJintArray(env, g1);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1SetHashAndMapTo(JNIEnv *env, jclass type, jintArray a) {
  mclBnG1 g1;
  jsize len = env->GetArrayLength(a);
  unsigned char * array = jintArrayToIntArray(env, &a, len);

  mclBnG1_hashAndMapTo(&g1, array, len);
  jintArray ret = g1ToJintArray(env, g1);

  free(array);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1Serialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnG1 g1 = jintArrayToG1(env, &a);

  jintArray ret = g1ToJintArraySer(env, g1);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1g1IsZero(JNIEnv *env, jclass type, jintArray a) {
  mclBnG1 g1 = jintArrayToG1(env, &a);

  jint ret = mclBnG1_isZero(&g1);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1g1IsValid(JNIEnv *env, jclass type, jintArray a) {
  mclBnG1 g1 = jintArrayToG1(env, &a);

  jint ret = mclBnG1_isValid(&g1);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1g1IsValidOrder(JNIEnv *env, jclass type, jintArray a) {
  mclBnG1 g1 = jintArrayToG1(env, &a);

  jint ret = mclBnG1_isValid(&g1);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1g1IsEqual(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnG1 g1 = jintArrayToG1(env, &a);
  mclBnG1 g12 = jintArrayToG1(env, &b);

  jint ret = mclBnG1_isEqual(&g1, &g12);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1GetBasePoint(JNIEnv *env, jclass type) {
  mclBnG1 g1;
  mclBnG1_getBasePoint(&g1);

  jintArray ret = g1ToJintArray(env, g1);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1Neg(JNIEnv *env, jclass type, jintArray a) {
  mclBnG1 g1 = jintArrayToG1(env, &a);

  mclBnG1 g12;
  mclBnG1_neg(&g12, &g1);

  jintArray ret = g1ToJintArray(env, g12);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1Normalize(JNIEnv *env, jclass type, jintArray a) {
  mclBnG1 g1 = jintArrayToG1(env, &a);

  mclBnG1 g12;
  mclBnG1_normalize(&g12, &g1);

  jintArray ret = g1ToJintArray(env, g12);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1Dbl(JNIEnv *env, jclass type, jintArray a) {
  mclBnG1 g1 = jintArrayToG1(env, &a);

  mclBnG1 g12;
  mclBnG1_dbl(&g12, &g1);

  jintArray ret = g1ToJintArray(env, g12);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1Add(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnG1 g1 = jintArrayToG1(env, &a);
  mclBnG1 g12 = jintArrayToG1(env, &b);

  mclBnG1 result;
  mclBnG1_add(&result, &g1, &g12);

  jintArray ret = g1ToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1Sub(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnG1 g1 = jintArrayToG1(env, &a);
  mclBnG1 g12 = jintArrayToG1(env, &b);

  mclBnG1 result;
  mclBnG1_sub(&result, &g1, &g12);

  jintArray ret = g1ToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1Mul(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnG1 g1 = jintArrayToG1(env, &a);
  mclBnFr fr = jintArrayToFr(env, &b);

  mclBnG1 result;
  mclBnG1_mul(&result, &g1, &fr);

  jintArray ret = g1ToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g1MulVec(JNIEnv *env, jclass type, jobjectArray a, jobjectArray b) {
  jsize len = env->GetArrayLength(a);

  mclBnG1 g1Vec[len];
  mclBnFr frVec[len];

  for(int i = 0; i < len; i++) {
    jintArray g1Ba = (jintArray) env->GetObjectArrayElement(a, i);
    mclBnG1 g1 = jintArrayToG1(env, &g1Ba);
    g1Vec[i] = g1;

    jintArray frBa = (jintArray) env->GetObjectArrayElement(b, i);
    mclBnFr fr = jintArrayToFr(env, &frBa);
    frVec[i] = fr;

    env->DeleteLocalRef(g1Ba);
    env->DeleteLocalRef(frBa);
  }

  mclBnG1 result;
  mclBnG1_mulVec(&result, &g1Vec[0], &frVec[0], len);

  jintArray ret = g1ToJintArray(env, result);

  return ret;
}

// G2

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g2Deserialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnG2 g2 = jintArrayToG2Deser(env, &a);

  jintArray ret = g2ToJintArray(env, g2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g2SetHashAndMapTo(JNIEnv *env, jclass type, jintArray a) {
  mclBnG2 g2;
  jsize len = env->GetArrayLength(a);
  unsigned char * array = jintArrayToIntArray(env, &a, len);

  mclBnG2_hashAndMapTo(&g2, array, len);
  jintArray ret = g2ToJintArray(env, g2);

  free(array);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g2Serialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnG2 g2 = jintArrayToG2(env, &a);

  jintArray ret = g2ToJintArraySer(env, g2);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1g2IsZero(JNIEnv *env, jclass type, jintArray a) {
  mclBnG2 g2 = jintArrayToG2(env, &a);

  jint ret = mclBnG2_isZero(&g2);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1g2IsValid(JNIEnv *env, jclass type, jintArray a) {
  mclBnG2 g2 = jintArrayToG2(env, &a);

  jint ret = mclBnG2_isValid(&g2);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1g2IsValidOrder(JNIEnv *env, jclass type, jintArray a) {
  mclBnG2 g2 = jintArrayToG2(env, &a);

  jint ret = mclBnG2_isValid(&g2);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1g2IsEqual(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnG2 g2 = jintArrayToG2(env, &a);
  mclBnG2 g22 = jintArrayToG2(env, &b);

  jint ret = mclBnG2_isEqual(&g2, &g22);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g2Neg(JNIEnv *env, jclass type, jintArray a) {
  mclBnG2 g2 = jintArrayToG2(env, &a);

  mclBnG2 g22;
  mclBnG2_neg(&g22, &g2);

  jintArray ret = g2ToJintArray(env, g22);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g2Normalize(JNIEnv *env, jclass type, jintArray a) {
  mclBnG2 g2 = jintArrayToG2(env, &a);

  mclBnG2 g22;
  mclBnG2_normalize(&g22, &g2);

  jintArray ret = g2ToJintArray(env, g22);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g2Dbl(JNIEnv *env, jclass type, jintArray a) {
  mclBnG2 g2 = jintArrayToG2(env, &a);

  mclBnG2 g22;
  mclBnG2_dbl(&g22, &g2);

  jintArray ret = g2ToJintArray(env, g22);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g2Add(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnG2 g2 = jintArrayToG2(env, &a);
  mclBnG2 g22 = jintArrayToG2(env, &b);

  mclBnG2 result;
  mclBnG2_add(&result, &g2, &g22);

  jintArray ret = g2ToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g2Sub(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnG2 g2 = jintArrayToG2(env, &a);
  mclBnG2 g22 = jintArrayToG2(env, &b);

  mclBnG2 result;
  mclBnG2_sub(&result, &g2, &g22);

  jintArray ret = g2ToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g2Mul(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnG2 g2 = jintArrayToG2(env, &a);
  mclBnFr fr = jintArrayToFr(env, &b);

  mclBnG2 result;
  mclBnG2_mul(&result, &g2, &fr);

  jintArray ret = g2ToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1g2MulVec(JNIEnv *env, jclass type, jobjectArray a, jobjectArray b) {
  jsize len = env->GetArrayLength(a);

  mclBnG2 g2Vec[len];
  mclBnFr frVec[len];

  for(int i = 0; i < len; i++) {
    jintArray g2Ba = (jintArray) env->GetObjectArrayElement(a, i);
    mclBnG2 g2 = jintArrayToG2(env, &g2Ba);
    g2Vec[i] = g2;

    jintArray frBa = (jintArray) env->GetObjectArrayElement(b, i);
    mclBnFr fr = jintArrayToFr(env, &frBa);
    frVec[i] = fr;

    env->DeleteLocalRef(g2Ba);
    env->DeleteLocalRef(frBa);
  }

  mclBnG2 result;
  mclBnG2_mulVec(&result, &g2Vec[0], &frVec[0], len);

  jintArray ret = g2ToJintArray(env, result);

  return ret;
}

// GT

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtDeserialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnGT gt = jintArrayToGTDeser(env, &a);

  jintArray ret = gtToJintArray(env, gt);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtSerialize(JNIEnv *env, jclass type, jintArray a) {
  mclBnGT gt = jintArrayToGT(env, &a);

  jintArray ret = gtToJintArraySer(env, gt);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtSetInt32(JNIEnv *env, jclass type, jint a) {
  mclBnGT gt;
  mclBnGT_setInt32(&gt, (int)a);

  jintArray ret = gtToJintArray(env, gt);

  return ret;
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1gtIsEqual(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnGT gt = jintArrayToGT(env, &a);
  mclBnGT gt2 = jintArrayToGT(env, &b);

  jint ret = mclBnGT_isEqual(&gt, &gt2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtSetStr(JNIEnv *env, jclass type, jstring a, jint b) {
  const char *c_str;

  c_str = env->GetStringUTFChars (a, NULL);

  mclBnGT gt;
  mclBnGT_setStr(&gt, c_str, strlen(c_str), (int)b);

  jintArray ret = gtToJintArray(env, gt);

  env->ReleaseStringUTFChars (a, c_str);

  return ret;
}

JNIEXPORT jstring JNICALL
Java_com_reactnativemcl_MclModule__1gtGetStr(JNIEnv *env, jclass type, jintArray a, jint b) {
  mclBnGT gt = jintArrayToGT(env, &a);

  char buf[1024];
  mclBnGT_getStr(buf, sizeof(buf), &gt, (int)b);

  return env->NewStringUTF (buf);
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtNeg(JNIEnv *env, jclass type, jintArray a) {
  mclBnGT gt = jintArrayToGT(env, &a);

  mclBnGT gt2;
  mclBnGT_neg(&gt2, &gt);

  jintArray ret = gtToJintArray(env, gt2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtSqr(JNIEnv *env, jclass type, jintArray a) {
  mclBnGT gt = jintArrayToGT(env, &a);

  mclBnGT gt2;
  mclBnGT_sqr(&gt2, &gt);

  jintArray ret = gtToJintArray(env, gt2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtInv(JNIEnv *env, jclass type, jintArray a) {
  mclBnGT gt = jintArrayToGT(env, &a);

  mclBnGT gt2;
  mclBnGT_inv(&gt2, &gt);

  jintArray ret = gtToJintArray(env, gt2);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtAdd(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnGT gt = jintArrayToGT(env, &a);
  mclBnGT gt2 = jintArrayToGT(env, &b);

  mclBnGT result;
  mclBnGT_add(&result, &gt, &gt2);

  jintArray ret = gtToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtSub(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnGT gt = jintArrayToGT(env, &a);
  mclBnGT gt2 = jintArrayToGT(env, &b);

  mclBnGT result;
  mclBnGT_sub(&result, &gt, &gt2);

  jintArray ret = gtToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtMul(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnGT gt = jintArrayToGT(env, &a);
  mclBnGT gt2 = jintArrayToGT(env, &b);

  mclBnGT result;
  mclBnGT_mul(&result, &gt, &gt2);

  jintArray ret = gtToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtDiv(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnGT gt = jintArrayToGT(env, &a);
  mclBnGT gt2 = jintArrayToGT(env, &b);

  mclBnGT result;
  mclBnGT_div(&result, &gt, &gt2);

  jintArray ret = gtToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1gtPow(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnGT gt = jintArrayToGT(env, &a);
  mclBnFr fr = jintArrayToFr(env, &b);

  mclBnGT result;
  mclBnGT_pow(&result, &gt, &fr);

  jintArray ret = gtToJintArray(env, result);

  return ret;
}


// Other methods

JNIEXPORT void JNICALL
Java_com_reactnativemcl_MclModule__1verifyOrderG1(JNIEnv *env, jclass type, int a) {
  mclBn_verifyOrderG1(a);
}

JNIEXPORT void JNICALL
Java_com_reactnativemcl_MclModule__1verifyOrderG2(JNIEnv *env, jclass type, int a) {
  mclBn_verifyOrderG2(a);
}

JNIEXPORT void JNICALL
Java_com_reactnativemcl_MclModule__1setMapToMode(JNIEnv *env, jclass type, int a) {
  mclBn_setMapToMode(a);
}

JNIEXPORT void JNICALL
Java_com_reactnativemcl_MclModule__1setETHserialization(JNIEnv *env, jclass type, int a) {
  mclBn_setETHserialization(a);
}

JNIEXPORT jint JNICALL
Java_com_reactnativemcl_MclModule__1getUint64NumToPrecompute(JNIEnv *env, jclass type) {
  return mclBn_getUint64NumToPrecompute();
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1precomputeG2(JNIEnv *env, jclass type, jintArray a) {
  mclBnG2 g2 = jintArrayToG2(env, &a);

  int byteSize = mclBn_getUint64NumToPrecompute() * 8;
  uint64_t buf[byteSize];

  mclBn_precomputeG2(&buf[0], &g2);

  jintArray ret = env->NewIntArray(byteSize);

  env->SetIntArrayRegion(ret, 0, byteSize, (jint*)&buf[0]);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1pairing(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  mclBnG1 g1 = jintArrayToG1(env, &a);
  mclBnG2 g2 = jintArrayToG2(env, &b);

  mclBnGT gt;
  mclBn_pairing(&gt, &g1, &g2);

  jintArray ret = gtToJintArray(env, gt);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1finalExp(JNIEnv *env, jclass type, jintArray a) {
  mclBnGT gt = jintArrayToGT(env, &a);

  mclBnGT result;
  mclBn_finalExp(&result, &gt);

  jintArray ret = gtToJintArray(env, gt);

  return ret;
}

JNIEXPORT bool JNICALL
Java_com_reactnativemcl_MclModule__1initialize(JNIEnv *env, jclass type, int curve = 5) {
  return blsInit(curve, MCLBN_COMPILED_TIME_VAR) == 0;
}

// noble

JNIEXPORT void JNICALL
Java_com_reactnativemcl_MclModule__1setDSTLabel(JNIEnv *env, jclass type, jstring a) {
    const char *c_str;

    c_str = env->GetStringUTFChars (a, NULL);

    mclBnG1_setDst(c_str, strlen(c_str));
    mclBnG2_setDst(c_str, strlen(c_str));
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1getPublicKey(JNIEnv *env, jclass type, jintArray a) {
  blsSecretKey sk = jintArrayToSk(env, &a);

  blsPublicKey result;
  blsGetPublicKey(&result, &sk);

  jintArray ret = pkToJintArray(env, result);

  return ret;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1sign(JNIEnv *env, jclass type, jintArray a, jintArray b) {
  jsize len = env->GetArrayLength(a);
  unsigned char * msg = jintArrayToIntArray(env, &a, len);
  blsSecretKey sk = jintArrayToSk(env, &b);

  blsSignature result;
  blsSign(&result, &sk, msg, len);

  jintArray ret = sigToJintArray(env, result);

  return ret;
}

JNIEXPORT bool JNICALL
Java_com_reactnativemcl_MclModule__1verify(JNIEnv *env, jclass type, jintArray a, jintArray b, jintArray c) {
  blsSignature sig = jintArrayToSig(env, &a);
  jsize len = env->GetArrayLength(b);
  unsigned char * msg = jintArrayToIntArray(env, &b, len);
  blsPublicKey pk = jintArrayToPk(env, &c);

  return blsVerify(&sig, &pk, msg, len) == 1;
}

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1aggregateSignatures(JNIEnv *env, jclass type, jobjectArray a) {
  jsize len = env->GetArrayLength(a);

  blsSignature sigVec[len];

  for(int i = 0; i < len; i++) {
    jintArray sigBa = (jintArray) env->GetObjectArrayElement(a, i);
    blsSignature sig = jintArrayToSig(env, &sigBa);
    sigVec[i] = sig;

    env->DeleteLocalRef(sigBa);
  }

  blsSignature result;
  blsAggregateSignature(&result, &sigVec[0], len);

  jintArray ret = sigToJintArray(env, result);

  return ret;
}

JNIEXPORT bool JNICALL
Java_com_reactnativemcl_MclModule__1verifyBatch(JNIEnv *env, jclass type, jintArray a, jobjectArray b, jobjectArray c) {
  blsSignature sig = jintArrayToSig(env, &a);

  jsize len = env->GetArrayLength(b);

  blsPublicKey pkVec[len];

  jsize msgLen = 0;

  for(int i = 0; i < len; i++) {
    jintArray pkBa = (jintArray) env->GetObjectArrayElement(c, i);
    blsPublicKey pk = jintArrayToPk(env, &pkBa);
    pkVec[i] = pk;

    if (i == 0) {
      jintArray msgBa = (jintArray) env->GetObjectArrayElement(b, i);
      msgLen = env->GetArrayLength(msgBa);
      env->DeleteLocalRef(msgBa);
    }

    env->DeleteLocalRef(pkBa);
  }

  unsigned char msgVec[len*msgLen];

  for(int i = 0; i < len; i++) {
    jintArray pkBa = (jintArray) env->GetObjectArrayElement(b, i);
    unsigned char * msg = jintArrayToIntArray(env, &pkBa, msgLen);
    memcpy(msgVec+i*msgLen, msg, msgLen);
  }

  return blsAggregateVerifyNoCheck(&sig, &pkVec[0], &msgVec[0], msgLen, len) == 1;
}

// Fp2

JNIEXPORT jintArray JNICALL
Java_com_reactnativemcl_MclModule__1getHashId(JNIEnv *env, jclass type, jintArray a, jintArray b, jintArray c) {
  mclBnG1 ok = jintArrayToG1Deser(env, &a);
  mclBnG1 sk = jintArrayToG1Deser(env, &b);
  mclBnFr vk = jintArrayToFrDeser(env, &c);

  mclBnG1 t;
  mclBnG1_mul(&t, &ok, &vk);

  unsigned char toHash[57];
  toHash[0] = 48;
  mclBnG1_serialize(&toHash[1], 48, &t);
  toHash[49] = 0;
  toHash[50] = 0;
  toHash[51] = 0;
  toHash[52] = 0;
  toHash[53] = 0;
  toHash[54] = 0;
  toHash[55] = 0;
  toHash[56] = 0;

  CSHA256 hash;
  unsigned char hashed[32];
  hash.Write(&toHash[0], 57);
  hash.Finalize(hashed);
  hash.Reset();
  hash.Write(&hashed[0], 32);
  hash.Finalize(hashed);

  mclBnFr hash_t;
  mclBnFr_setBigEndianMod(&hash_t, &hashed[0], 32);

  mclBnG1 gen;
  blsGetGeneratorOfPublicKey((blsPublicKey *)&gen);

  mclBnG1 hash_t_g1;
  mclBnG1_mul(&hash_t_g1, &gen, &hash_t);

  mclBnFr one;
  mclBnFr oneNeg;
  mclBnFr_setInt32(&one, 1);
  mclBnFr_neg(&oneNeg, &one);

  mclBnG1 hash_t_g1Neg;
  mclBnG1_mul(&hash_t_g1Neg, &hash_t_g1, &oneNeg);

  mclBnG1 res;
  mclBnG1_add(&res, &hash_t_g1Neg, &sk);

  jintArray ret = g1ToJintArray(env, res);

  return ret;
}

}
