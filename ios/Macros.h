//
//  Macros.h
//  Mcl
//
//  Created by alex v. on 07.03.22.
//

#ifndef Macros_h
#define Macros_h

#define MCLBN_FP_UNIT_SIZE 6
#define MCLBN_FR_UNIT_SIZE 4
#define MCLBN_FP_SIZE 48
#define MCLBN_FR_SIZE 32
#define MCLBN_G1_SIZE 48
#define MCLBN_G2_SIZE 98
#define MCLBN_GT_SIZE 196

#define ARRAY_TO_G1(ba, g1) \
Byte* g1##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
g1##Bytes[[index integerValue]] = [number integerValue]; \
}]; \
mclBnG1 g1; \
size_t g1##DeserSize = mclBnG1_deserialize(&g1, &g1##Bytes[0], [[ba allValues] count]); \
free(g1##Bytes);

#define ARRAY_TO_FR(ba, fr) \
Byte* fr##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
fr##Bytes[[index integerValue]] = [number integerValue]; \
}]; \
mclBnFr fr; \
size_t fr##DeserSize = mclBnFr_deserialize(&fr, &fr##Bytes[0], [[ba allValues] count]); \
free(fr##Bytes);

#define ARRAY_TO_FP(ba, fp) \
Byte* fp##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
fp##Bytes[[index integerValue]] = [number integerValue]; \
}]; \
mclBnFp fp; \
size_t fp##DeserSize = mclBnFp_deserialize(&fp, &fp##Bytes[0], [[ba allValues] count]); \
free(fp##Bytes);

#define ARRAY_TO_FP2(ba, fp2) \
Byte* fp2##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
fp2##Bytes[[index integerValue]] = [number integerValue]; \
}]; \
mclBnFp2 fp2; \
size_t fp2##DeserSize = mclBnFp2_deserialize(&fp2, &fp2##Bytes[0], [[ba allValues] count]); \
free(fp2##Bytes);

#define ARRAY_TO_G2(ba, g2) \
Byte* g2##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
g2##Bytes[[index integerValue]] = [number integerValue]; \
}]; \
mclBnG2 g2; \
size_t g2##DeserSize = mclBnG2_deserialize(&g2, &g2##Bytes[0], [[ba allValues] count]); \
free(g2##Bytes);

#define ARRAY_TO_GT(ba, gt) \
Byte* gt##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
gt##Bytes[[index integerValue]] = [number integerValue]; \
}]; \
mclBnGT gt; \
size_t gt##DeserSize = mclBnGT_deserialize(&gt, &gt##Bytes[0], [[ba allValues] count]); \
free(gt##Bytes);

#define ARRAY_TO_BYTES(ba, fr) \
Byte* fr = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
fr[[index integerValue]] = [number integerValue]; \
}];

#define ARRAY_TO_CARRAY(ba, ca) \
Byte* ca = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
ca[[index integerValue]] = [number integerValue]; \
}];

#define G1_TO_ARRAY(g1, ba) \
char ba##C[MCLBN_G1_SIZE]; \
mclBnG1_serialize(&ba##C[0], MCLBN_G1_SIZE, &g1); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: MCLBN_G1_SIZE]; \
for (unsigned int i = 0; i < MCLBN_G1_SIZE; i++) \
{ \
[ba addObject: [[NSNumber alloc] initWithUnsignedChar:ba##C[i]]]; \
}

#define G2_TO_ARRAY(g2, ba) \
char ba##C[MCLBN_G2_SIZE]; \
mclBnG2_serialize(&ba##C[0], MCLBN_G2_SIZE, &g2); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: MCLBN_G2_SIZE]; \
for (unsigned int i = 0; i < MCLBN_G2_SIZE; i++) \
{ \
[ba addObject: [[NSNumber alloc] initWithUnsignedChar:ba##C[i]]]; \
}

#define GT_TO_ARRAY(gt, ba) \
char ba##C[MCLBN_GT_SIZE]; \
mclBnGT_serialize(&ba##C[0], MCLBN_GT_SIZE, &gt); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: MCLBN_GT_SIZE]; \
for (unsigned int i = 0; i < MCLBN_GT_SIZE; i++) \
{ \
[ba addObject: [[NSNumber alloc] initWithUnsignedChar:ba##C[i]]]; \
}

#define FR_TO_ARRAY(fr, ba) \
char ba##C[MCLBN_FR_SIZE]; \
mclBnFr_serialize(&ba##C[0], MCLBN_FR_SIZE, &fr); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: MCLBN_FR_SIZE]; \
for (unsigned int i = 0; i < MCLBN_FR_SIZE; i++) \
{ \
[ba addObject: [[NSNumber alloc] initWithUnsignedChar:ba##C[i]]]; \
}

#define FP_TO_ARRAY(fp, ba) \
char ba##C[MCLBN_FP_SIZE]; \
mclBnFp_serialize(&ba##C[0], MCLBN_FP_SIZE, &fp); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: MCLBN_FP_SIZE]; \
for (unsigned int i = 0; i < MCLBN_FP_SIZE; i++) \
{ \
[ba addObject: [[NSNumber alloc] initWithUnsignedChar:ba##C[i]]]; \
}

#define FP2_TO_ARRAY(fp2, ba) \
char ba##C[MCLBN_FP_SIZE*2]; \
mclBnFp2_serialize(&ba##C[0], MCLBN_FP_SIZE*2, &fp2); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: MCLBN_FP_SIZE*2]; \
for (unsigned int i = 0; i < MCLBN_FP_SIZE*2; i++) \
{ \
[ba addObject: [[NSNumber alloc] initWithUnsignedChar:ba##C[i]]]; \
}

#define CARRAY_TO_ARRAY(ca, ba)\
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: sizeof(ca)]; \
for (unsigned int i = 0; i < sizeof(ca); i++) \
{ \
[ba addObject: [[NSNumber alloc] initWithUnsignedChar:ca[i]]]; \
}

#endif /* Macros_h */