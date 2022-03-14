#include <jni.h>
#include <mcl/bn_c384_256.h>
#include<android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "ReactNative", __VA_ARGS__)

extern "C"
{

// Fr

mclBnFr jintArrayToFrDeser(JNIEnv* env, jintArray *a)
{
  jsize len = env->GetArrayLength(*a);

  jint *b = env->GetIntArrayElements (*a, 0);

  unsigned char bb[len];

  for (int i = 0; i < len; i++){
    bb[i] = b[i];
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
    return mclBn_init(curve, MCLBN_COMPILED_TIME_VAR) == 0;
}
}
