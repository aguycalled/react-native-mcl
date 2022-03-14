#import "Mcl.h"
#import "Macros.h"
#include <bls_framework/bls_framework.h>

@implementation Mcl

RCT_EXPORT_MODULE()

+ (BOOL)requiresMainQueueSetup
{
    return NO;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(initialize:(nonnull NSNumber*)curve)
{
    mclBn_init(curve.intValue, MCLBN_COMPILED_TIME_VAR);
    return [NSNull null];
}

// SCALAR Methods

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frSetLittleEndian:(nonnull NSDictionary*)b)
{
    mclBnFr fr;
    ARRAY_TO_BYTES(b, le)
    
    mclBnFr_setLittleEndian(&fr, le, b.count);
    
    free(le);
    
    FR_TO_ARRAY(fr, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frDeserialize:(nonnull NSDictionary*)b)
{
    DESER_ARRAY_TO_FR(b, fr)
    FR_TO_ARRAY(fr, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frSerialize:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FR(b, fr)
    FRSER_TO_ARRAY(fr, ret)
    
    return ret;
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frSetLittleEndianMod:(nonnull NSDictionary*)b)
{
    mclBnFr fr;
    ARRAY_TO_BYTES(b, le)
    
    mclBnFr_setLittleEndianMod(&fr, le, b.count);
    
    free(le);
    
    FR_TO_ARRAY(fr, ret)
    
    return ret;
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frSetBigEndianMod:(nonnull NSDictionary*)b)
{
    mclBnFr fr;
    ARRAY_TO_BYTES(b, le)
    
    mclBnFr_setBigEndianMod(&fr, le, b.count);
    
    free(le);
    
    FR_TO_ARRAY(fr, ret)
    
    return ret;
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frSetHashOf:(nonnull NSDictionary*)b)
{
    mclBnFr fr;
    ARRAY_TO_BYTES(b, le)
    
    mclBnFr_setHashOf(&fr, le, b.count);
    
    free(le);
    
    FR_TO_ARRAY(fr, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frSetInt32:(nonnull NSNumber*)b)
{
    mclBnFr fr;
    
    mclBnFr_setInt32(&fr, b.intValue);
        
    FR_TO_ARRAY(fr, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frSetStr:(nonnull NSString*)a ioMode:(nonnull NSNumber*)io)
{
    mclBnFr fr;
    
    NSUInteger numberOfBytes = [a lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    const char *buffer = [a UTF8String];
    
    mclBnFr_setStr(&fr, &buffer[0], numberOfBytes, io.intValue);
    
    FR_TO_ARRAY(fr, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frGetStr:(nonnull NSDictionary*)a ioMode:(nonnull NSNumber*)io)
{
    ARRAY_TO_FR(a, fr)
    
    char buf[1024];
    
    int len = mclBnFr_getStr(buf, sizeof(buf), &fr, io.intValue);
    
    NSString *ret = [[NSString alloc] initWithBytes:buf
        length:len encoding:NSUTF8StringEncoding];
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frIsZero:(nonnull NSDictionary*)a)
{
    ARRAY_TO_FR(a, fr)
    
    int ret = mclBnFr_isZero(&fr);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frIsOne:(nonnull NSDictionary*)a)
{
    ARRAY_TO_FR(a, fr)
    
    int ret = mclBnFr_isOne(&fr);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frIsEqual:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FR(a, fr)
    ARRAY_TO_FR(b, fr2)
    
    int ret = mclBnFr_isEqual(&fr, &fr2);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frNeg:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FR(a, fr)

    mclBnFr fr2;
    mclBnFr_neg(&fr2, &fr);
    
    FR_TO_ARRAY(fr2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frSqr:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FR(a, fr)

    mclBnFr fr2;
    mclBnFr_sqr(&fr2, &fr);
    
    FR_TO_ARRAY(fr2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frInv:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FR(a, fr)

    mclBnFr fr2;
    mclBnFr_inv(&fr2, &fr);
    
    FR_TO_ARRAY(fr2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frSquareRoot:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FR(a, fr)

    mclBnFr fr2;
    mclBnFr_squareRoot(&fr2, &fr);
    
    FR_TO_ARRAY(fr2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frAdd:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FR(a, op1)
    ARRAY_TO_FR(b, op2)

    mclBnFr result;
    mclBnFr_add(&result, &op1, &op2);
        
    FR_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frSub:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FR(a, op1)
    ARRAY_TO_FR(b, op2)

    mclBnFr result;
    mclBnFr_sub(&result, &op1, &op2);
        
    FR_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frMul:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FR(a, op1)
    ARRAY_TO_FR(b, op2)

    mclBnFr result;
    mclBnFr_mul(&result, &op1, &op2);
        
    FR_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(frDiv:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FR(a, op1)
    ARRAY_TO_FR(b, op2)

    mclBnFr result;
    mclBnFr_div(&result, &op1, &op2);
        
    FR_TO_ARRAY(result, ret)
            
    return ret;
}

// FP Methods

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpSetLittleEndian:(nonnull NSDictionary*)b)
{
    mclBnFp fp;
    ARRAY_TO_BYTES(b, le)
    
    mclBnFp_setLittleEndian(&fp, le, b.count);
    
    free(le);
    
    FP_TO_ARRAY(fp, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpDeserialize:(nonnull NSDictionary*)b)
{
    DESER_ARRAY_TO_FP(b, fp)
    FP_TO_ARRAY(fp, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpSerialize:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP(b, fp)
    FPSER_TO_ARRAY(fp, ret)
    
    return ret;
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpSetLittleEndianMod:(nonnull NSDictionary*)b)
{
    mclBnFp fp;
    ARRAY_TO_BYTES(b, le)
    
    mclBnFp_setLittleEndianMod(&fp, le, b.count);
    
    free(le);
    
    FP_TO_ARRAY(fp, ret)
    
    return ret;
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpSetBigEndianMod:(nonnull NSDictionary*)b)
{
    mclBnFp fp;
    ARRAY_TO_BYTES(b, le)
    
    mclBnFp_setBigEndianMod(&fp, le, b.count);
    
    free(le);
    
    FP_TO_ARRAY(fp, ret)
    
    return ret;
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpSetHashOf:(nonnull NSDictionary*)b)
{
    mclBnFp fp;
    ARRAY_TO_BYTES(b, le)
    
    mclBnFp_setHashOf(&fp, le, b.count);
    
    free(le);
    
    FP_TO_ARRAY(fp, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpSetInt32:(nonnull NSNumber*)b)
{
    mclBnFp fp;
    
    mclBnFp_setInt32(&fp, b.intValue);
        
    FP_TO_ARRAY(fp, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpSetStr:(nonnull NSString*)a ioMode:(nonnull NSNumber*)io)
{
    mclBnFp fp;
    
    NSUInteger numberOfBytes = [a lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    const char *buffer = [a UTF8String];
    
    mclBnFp_setStr(&fp, &buffer[0], numberOfBytes, io.intValue);
    
    FP_TO_ARRAY(fp, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpGetStr:(nonnull NSDictionary*)a ioMode:(nonnull NSNumber*)io)
{
    ARRAY_TO_FP(a, fp)
    
    char buf[1024];
    
    int len = mclBnFp_getStr(buf, sizeof(buf), &fp, io.intValue);
    
    NSString *ret = [[NSString alloc] initWithBytes:buf
        length:len encoding:NSUTF8StringEncoding];
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpIsZero:(nonnull NSDictionary*)a)
{
    ARRAY_TO_FP(a, fp)
    
    int ret = mclBnFp_isZero(&fp);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpIsOne:(nonnull NSDictionary*)a)
{
    ARRAY_TO_FP(a, fp)
    
    int ret = mclBnFp_isOne(&fp);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpIsEqual:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP(a, fp)
    ARRAY_TO_FP(b, fp2)
    
    int ret = mclBnFp_isEqual(&fp, &fp2);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpMapToG1:(nonnull NSDictionary*)a)
{
    ARRAY_TO_FP(a, fp)
    mclBnG1 g1;
    
    mclBnFp_mapToG1(&g1, &fp);
    
    G1_TO_ARRAY(g1, ret)
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpNeg:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FP(a, fp)

    mclBnFp fp2;
    mclBnFp_neg(&fp2, &fp);
    
    FP_TO_ARRAY(fp2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpSqr:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FP(a, fp)

    mclBnFp fp2;
    mclBnFp_sqr(&fp2, &fp);
    
    FP_TO_ARRAY(fp2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpInv:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FP(a, fp)

    mclBnFp fp2;
    mclBnFp_inv(&fp2, &fp);
    
    FP_TO_ARRAY(fp2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpSquareRoot:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FP(a, fp)

    mclBnFp fp2;
    mclBnFp_squareRoot(&fp2, &fp);
    
    FP_TO_ARRAY(fp2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpAdd:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP(a, op1)
    ARRAY_TO_FP(b, op2)

    mclBnFp result;
    mclBnFp_add(&result, &op1, &op2);
        
    FP_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpSub:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP(a, op1)
    ARRAY_TO_FP(b, op2)

    mclBnFp result;
    mclBnFp_sub(&result, &op1, &op2);
        
    FP_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpMul:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP(a, op1)
    ARRAY_TO_FP(b, op2)

    mclBnFp result;
    mclBnFp_mul(&result, &op1, &op2);
        
    FP_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fpDiv:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP(a, op1)
    ARRAY_TO_FP(b, op2)

    mclBnFp result;
    mclBnFp_div(&result, &op1, &op2);
        
    FP_TO_ARRAY(result, ret)
            
    return ret;
}

// Fp2 Methods

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2Deserialize:(nonnull NSDictionary*)b)
{
    DESER_ARRAY_TO_FP2(b, fp2)
    FP2_TO_ARRAY(fp2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2Serialize:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP2(b, fp2)
    FP2SER_TO_ARRAY(fp2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2IsEqual:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP2(a, fp2)
    ARRAY_TO_FP2(b, fp22)
    
    int ret = mclBnFp2_isEqual(&fp2, &fp22);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2MapToG2:(nonnull NSDictionary*)a)
{
    ARRAY_TO_FP2(a, fp2)
    mclBnG2 g2;
    
    mclBnFp2_mapToG2(&g2, &fp2);
    
    G2_TO_ARRAY(g2, ret)
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2Neg:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FP2(a, fp2)

    mclBnFp2 fp22;
    mclBnFp2_neg(&fp22, &fp2);
    
    FP2_TO_ARRAY(fp22, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2Sqr:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FP2(a, fp2)

    mclBnFp2 fp22;
    mclBnFp2_sqr(&fp22, &fp2);
    
    FP_TO_ARRAY(fp22, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2Inv:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FP2(a, fp2)

    mclBnFp2 fp22;
    mclBnFp2_inv(&fp22, &fp2);
    
    FP2_TO_ARRAY(fp22, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2SquareRoot:(nonnull NSDictionary*)a )
{
    ARRAY_TO_FP2(a, fp2)

    mclBnFp2 fp22;
    mclBnFp2_squareRoot(&fp22, &fp2);
    
    FP2_TO_ARRAY(fp22, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2Add:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP2(a, op1)
    ARRAY_TO_FP2(b, op2)

    mclBnFp2 result;
    mclBnFp2_add(&result, &op1, &op2);
        
    FP2_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2Sub:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP2(a, op1)
    ARRAY_TO_FP2(b, op2)

    mclBnFp2 result;
    mclBnFp2_sub(&result, &op1, &op2);
        
    FP2_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2Mul:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP2(a, op1)
    ARRAY_TO_FP2(b, op2)

    mclBnFp2 result;
    mclBnFp2_mul(&result, &op1, &op2);
        
    FP2_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(fp2Div:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_FP2(a, op1)
    ARRAY_TO_FP2(b, op2)

    mclBnFp2 result;
    mclBnFp2_div(&result, &op1, &op2);
        
    FP2_TO_ARRAY(result, ret)
            
    return ret;
}

// G1 Methods

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1Deserialize:(nonnull NSDictionary*)b)
{
    DESER_ARRAY_TO_G1(b, g1)
    G1_TO_ARRAY(g1, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1Serialize:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G1(b, g1)
    G1SER_TO_ARRAY(g1, ret)
    
    return ret;
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1SetHashAndMapTo:(nonnull NSDictionary*)b)
{
    mclBnG1 g1;
    ARRAY_TO_BYTES(b, le)
    
    mclBnG1_hashAndMapTo(&g1, le, b.count);
    
    free(le);
    
    G1_TO_ARRAY(g1, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1IsZero:(nonnull NSDictionary*)a)
{
    ARRAY_TO_G1(a, g1)
    
    int ret = mclBnG1_isZero(&g1);
    return [NSNumber numberWithInt:ret];
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1IsValid:(nonnull NSDictionary*)a)
{
    ARRAY_TO_G1(a, g1)
    
    int ret = mclBnG1_isValid(&g1);
    return [NSNumber numberWithInt:ret];
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1IsValidOrder:(nonnull NSDictionary*)a)
{
    ARRAY_TO_G1(a, g1)
    
    int ret = mclBnG1_isValidOrder(&g1);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1IsEqual:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G1(a, g1)
    ARRAY_TO_G1(b, g12)
    
    int ret = mclBnG1_isEqual(&g1, &g12);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1GetBasePoint)
{
    mclBnG1 g1;
    
    mclBnG1_getBasePoint(&g1);
    
    G1_TO_ARRAY(g1, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1Neg:(nonnull NSDictionary*)a )
{
    ARRAY_TO_G1(a, g1)

    mclBnG1 g12;
    mclBnG1_neg(&g12, &g1);
    
    G1_TO_ARRAY(g12, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1Normalize:(nonnull NSDictionary*)a )
{
    ARRAY_TO_G1(a, g1)

    mclBnG1 g12;
    mclBnG1_normalize(&g12, &g1);
    
    G1_TO_ARRAY(g12, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1Dbl:(nonnull NSDictionary*)a )
{
    ARRAY_TO_G1(a, g1)

    mclBnG1 g12;
    mclBnG1_dbl(&g12, &g1);
    
    G1_TO_ARRAY(g12, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1Add:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G1(a, op1)
    ARRAY_TO_G1(b, op2)

    mclBnG1 result;
    mclBnG1_add(&result, &op1, &op2);
        
    G1_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1Sub:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G1(a, op1)
    ARRAY_TO_G1(b, op2)

    mclBnG1 result;
    mclBnG1_sub(&result, &op1, &op2);
        
    G1_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1Mul:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G1(a, op1)
    ARRAY_TO_FR(b, op2)

    mclBnG1 result;
    mclBnG1_mul(&result, &op1, &op2);
        
    G1_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g1MulVec:(nonnull NSArray*)a withB:(nonnull NSArray*)b)
{
    size_t count = a.count;
    
    mclBnG1 g1Vec[count];
    mclBnFr frVec[count];
    
    NSUInteger idx = 0;
    for (id item in a)
    {
        ARRAY_TO_G1(item, op)
        g1Vec[idx] = op;
        idx++;
    }
    
    idx = 0;
    for (id item in b)
    {
        ARRAY_TO_FR(item, op)
        frVec[idx] = op;
        idx++;
    }

    mclBnG1 result;
    mclBnG1_mulVec(&result, &g1Vec[0], &frVec[0], count);
        
    G1_TO_ARRAY(result, ret)
            
    return ret;
}

// G2 Methods

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2Deserialize:(nonnull NSDictionary*)b)
{
    DESER_ARRAY_TO_G2(b, g2)
    G2_TO_ARRAY(g2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2Serialize:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G2(b, g2)
    G2SER_TO_ARRAY(g2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2SetHashAndMapTo:(nonnull NSDictionary*)b)
{
    mclBnG2 g2;
    ARRAY_TO_BYTES(b, le)
    
    mclBnG2_hashAndMapTo(&g2, le, b.count);
    
    free(le);
    
    G2_TO_ARRAY(g2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2IsZero:(nonnull NSDictionary*)a)
{
    ARRAY_TO_G2(a, g2)
    
    int ret = mclBnG2_isZero(&g2);
    return [NSNumber numberWithInt:ret];
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2IsValid:(nonnull NSDictionary*)a)
{
    ARRAY_TO_G2(a, g2)
    
    int ret = mclBnG2_isValid(&g2);
    return [NSNumber numberWithInt:ret];
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2IsValidOrder:(nonnull NSDictionary*)a)
{
    ARRAY_TO_G2(a, g2)
    
    int ret = mclBnG2_isValidOrder(&g2);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2IsEqual:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G2(a, g2)
    ARRAY_TO_G2(b, g22)
    
    int ret = mclBnG2_isEqual(&g2, &g22);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2Neg:(nonnull NSDictionary*)a )
{
    ARRAY_TO_G2(a, g2)

    mclBnG2 g22;
    mclBnG2_neg(&g22, &g2);
    
    G2_TO_ARRAY(g22, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2Dbl:(nonnull NSDictionary*)a )
{
    ARRAY_TO_G2(a, g2)

    mclBnG2 g22;
    mclBnG2_dbl(&g22, &g2);
    
    G2_TO_ARRAY(g22, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2Normalize:(nonnull NSDictionary*)a )
{
    ARRAY_TO_G2(a, g2)

    mclBnG2 g22;
    mclBnG2_normalize(&g22, &g2);
    
    G2_TO_ARRAY(g22, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2Add:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G2(a, op1)
    ARRAY_TO_G2(b, op2)

    mclBnG2 result;
    mclBnG2_add(&result, &op1, &op2);
        
    G2_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2Sub:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G2(a, op1)
    ARRAY_TO_G2(b, op2)

    mclBnG2 result;
    mclBnG2_sub(&result, &op1, &op2);
        
    G2_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2Mul:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G2(a, op1)
    ARRAY_TO_FR(b, op2)

    mclBnG2 result;
    mclBnG2_mul(&result, &op1, &op2);
        
    G2_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(g2MulVec:(nonnull NSArray*)a withB:(nonnull NSArray*)b)
{
    size_t count = a.count;
    
    mclBnG2 g2Vec[count];
    mclBnFr frVec[count];
    
    NSUInteger idx = 0;
    for (id item in a)
    {
        ARRAY_TO_G2(a[idx], op)
        g2Vec[idx] = op;
        idx++;
    }
    
    idx = 0;
    for (id item in b)
    {
        ARRAY_TO_FR(b[idx], op)
        frVec[idx] = op;
        idx++;
    }

    mclBnG2 result;
    mclBnG2_mulVec(&result, &g2Vec[0], &frVec[0], count);
        
    G2_TO_ARRAY(result, ret)
            
    return ret;
}

// GT Methods
RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtDeserialize:(nonnull NSDictionary*)b)
{
    DESER_ARRAY_TO_GT(b, gt)
    GT_TO_ARRAY(gt, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtSerialize:(nonnull NSDictionary*)b)
{
    ARRAY_TO_GT(b, gt)
    GTSER_TO_ARRAY(gt, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtSetInt32:(nonnull NSNumber*)b)
{
    mclBnGT gt;
    
    mclBnGT_setInt32(&gt, b.intValue);
        
    GT_TO_ARRAY(gt, ret)
    
    return ret;
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtIsEqual:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_GT(a, gt)
    ARRAY_TO_GT(b, gt2)
    
    int ret = mclBnGT_isEqual(&gt, &gt2);
    return [NSNumber numberWithInt:ret];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtSetStr:(nonnull NSString*)a ioMode:(nonnull NSNumber*)io)
{
    mclBnGT gt;
    
    NSUInteger numberOfBytes = [a lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    const char *buffer = [a UTF8String];
    
    mclBnGT_setStr(&gt, &buffer[0], numberOfBytes, io.intValue);
    
    GT_TO_ARRAY(gt, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtGetStr:(nonnull NSDictionary*)a ioMode:(nonnull NSNumber*)io)
{
    ARRAY_TO_GT(a, gt)
    
    char buf[1024];
    
    int len = mclBnGT_getStr(buf, sizeof(buf), &gt, io.intValue);
    
    NSString *ret = [[NSString alloc] initWithBytes:buf
        length:len encoding:NSUTF8StringEncoding];
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtNeg:(nonnull NSDictionary*)a )
{
    ARRAY_TO_GT(a, gt)

    mclBnGT gt2;
    mclBnGT_neg(&gt2, &gt);
    
    GT_TO_ARRAY(gt2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtSqr:(nonnull NSDictionary*)a )
{
    ARRAY_TO_GT(a, gt)

    mclBnGT gt2;
    mclBnGT_sqr(&gt2, &gt);
    
    GT_TO_ARRAY(gt2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtInv:(nonnull NSDictionary*)a )
{
    ARRAY_TO_GT(a, gt)

    mclBnGT gt2;
    mclBnGT_inv(&gt2, &gt);
    
    GT_TO_ARRAY(gt2, ret)
    
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtAdd:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_GT(a, op1)
    ARRAY_TO_GT(b, op2)

    mclBnGT result;
    mclBnGT_add(&result, &op1, &op2);
        
    GT_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtSub:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_GT(a, op1)
    ARRAY_TO_GT(b, op2)

    mclBnGT result;
    mclBnGT_sub(&result, &op1, &op2);
        
    GT_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtMul:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_GT(a, op1)
    ARRAY_TO_GT(b, op2)

    mclBnGT result;
    mclBnGT_mul(&result, &op1, &op2);
        
    GT_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtPow:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_GT(a, op1)
    ARRAY_TO_FR(b, op2)

    mclBnGT result;
    mclBnGT_pow(&result, &op1, &op2);
        
    GT_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(gtDiv:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_GT(a, op1)
    ARRAY_TO_GT(b, op2)

    mclBnGT result;
    mclBnGT_div(&result, &op1, &op2);
        
    GT_TO_ARRAY(result, ret)
            
    return ret;
}

// Other methods

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(getUint64NumToPrecompute)
{
    return [NSNumber numberWithInt:mclBn_getUint64NumToPrecompute()];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(precomputeG2:(nonnull NSDictionary*)a)
{
    ARRAY_TO_G2(a, g2)

    int byteSize = mclBn_getUint64NumToPrecompute() * 8;
    char buf[byteSize];
    
    mclBn_precomputeG2(buf, &g2);
    
    CARRAY_TO_ARRAY(buf, ret)
                
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(pairing:(nonnull NSDictionary*)a withB:(nonnull NSDictionary*)b)
{
    ARRAY_TO_G1(a, op1)
    ARRAY_TO_G2(b, op2)

    mclBnGT result;
    mclBn_pairing(&result, &op1, &op2);
        
    GT_TO_ARRAY(result, ret)
            
    return ret;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(finalExp:(nonnull NSDictionary*)a)
{
    ARRAY_TO_GT(a, op1)

    mclBnGT result;
    mclBn_finalExp(&result, &op1);
        
    GT_TO_ARRAY(result, ret)
            
    return ret;
}

// Setup methods

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(setMapToMode:(nonnull NSNumber*)a )
{
    mclBn_setMapToMode(a.intValue);
            
    return [NSNull null];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(setETHserialization:(nonnull NSNumber*)a )
{
    mclBn_setETHserialization(a.intValue);
            
    return [NSNull null];
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(verifyOrderG1:(nonnull NSNumber*)a )
{
    mclBn_verifyOrderG1(a.intValue);
            
    return [NSNull null];
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(verifyOrderG2:(nonnull NSNumber*)a )
{
    mclBn_verifyOrderG2(a.intValue);
            
    return [NSNull null];
}

@end
