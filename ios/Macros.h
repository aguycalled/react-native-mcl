//
//  Macros.h
//  Mcl
//
//  Created by alex v. on 07.03.22.
//

#ifndef Macros_h
#define Macros_h

#define ARRAY_TO_G1(ba, g1) \
Byte* g1##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
g1##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnG1 g1; \
memcpy(&g1, &g1##Bytes[0], [[ba allValues] count]); \
free(g1##Bytes);

#define DESER_ARRAY_TO_G1(ba, g1) \
Byte* g1##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
g1##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnG1 g1; \
size_t g1##DeserSize = mclBnG1_deserialize(&g1, &g1##Bytes[0], [[ba allValues] count]); \
free(g1##Bytes);

#define ARRAY_TO_FR(ba, fr) \
Byte* fr##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
fr##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnFr fr; \
memcpy(&fr, &fr##Bytes[0], [[ba allValues] count]); \
free(fr##Bytes);

#define DESER_ARRAY_TO_FR(ba, fr) \
Byte* fr##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
fr##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnFr fr; \
mclBnFr_deserialize(&fr, &fr##Bytes[0], [[ba allValues] count]); \
free(fr##Bytes);

#define ARRAY_TO_FP(ba, fp) \
Byte* fp##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
fp##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnFp fp; \
memcpy(&fp, &fp##Bytes[0], [[ba allValues] count]); \
free(fp##Bytes);

#define DESER_ARRAY_TO_FP(ba, fp) \
Byte* fp##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
fp##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnFp fp; \
size_t fp##DeserSize = mclBnFp_deserialize(&fp, &fp##Bytes[0], [[ba allValues] count]); \
free(fp##Bytes);

#define ARRAY_TO_FP2(ba, fp2) \
Byte* fp2##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
fp2##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnFp2 fp2; \
memcpy(&fp2, &fp2##Bytes[0], [[ba allValues] count]); \
free(fp2##Bytes);

#define DESER_ARRAY_TO_FP2(ba, fp2) \
Byte* fp2##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
fp2##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnFp2 fp2; \
size_t fp2##DeserSize = mclBnFp2_deserialize(&fp2, &fp2##Bytes[0], [[ba allValues] count]); \
free(fp2##Bytes);

#define ARRAY_TO_G2(ba, g2) \
Byte* g2##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
g2##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnG2 g2; \
memcpy(&g2, &g2##Bytes[0], [[ba allValues] count]); \
free(g2##Bytes);

#define DESER_ARRAY_TO_G2(ba, g2) \
Byte* g2##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
g2##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnG2 g2; \
size_t g2##DeserSize = mclBnG2_deserialize(&g2, &g2##Bytes[0], [[ba allValues] count]); \
free(g2##Bytes);

#define ARRAY_TO_GT(ba, gt) \
Byte* gt##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
gt##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnGT gt; \
memcpy(&gt, &gt##Bytes[0], [[ba allValues] count]); \
free(gt##Bytes);

#define DESER_ARRAY_TO_GT(ba, gt) \
Byte* gt##Bytes = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
gt##Bytes[[index integerValue]] = [number intValue]; \
} \
}]; \
mclBnGT gt; \
size_t gt##DeserSize = mclBnGT_deserialize(&gt, &gt##Bytes[0], [[ba allValues] count]); \
free(gt##Bytes);

#define ARRAY_TO_BYTES(ba, fr) \
Byte* fr = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
fr[[index integerValue]] = [number intValue]; \
} \
}];

#define ARRAY_TO_CARRAY(ba, ca) \
Byte* ca = calloc([[ba allValues] count], sizeof(Byte)); \
[ba enumerateKeysAndObjectsUsingBlock:^(id index, id number, BOOL* stop){ \
if(![number isEqual:[NSNull null]]) { \
ca[[index integerValue]] = [number intValue]; \
} \
}];

#define G1_TO_ARRAY(g1, ba) \
Byte ba##C[48*3]; \
memcpy(&ba##C[0], &g1, 48*3); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: 48*3];\
for (unsigned int i = 0; i < 48*3; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
};

#define G1SER_TO_ARRAY(g1, ba) \
Byte ba##C[3096]; \
int ba##len = mclBnG1_serialize(&ba##C[0], 3096, &g1); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: ba##len]; \
for (unsigned int i = 0; i < ba##len; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
};

#define G2_TO_ARRAY(g2, ba) \
Byte ba##C[2*48*3]; \
memcpy(&ba##C[0], &g2, 2*48*3); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: 2*48*3];\
for (unsigned int i = 0; i < 2*48*3; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
};

#define G2SER_TO_ARRAY(g2, ba) \
Byte ba##C[3096]; \
int ba##len = mclBnG2_serialize(&ba##C[0], 3096, &g2); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: ba##len]; \
for (unsigned int i = 0; i < ba##len; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
}

#define GT_TO_ARRAY(gt, ba) \
Byte ba##C[4*48*3]; \
memcpy(&ba##C[0], &gt, 4*48*3); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: 4*48*3];\
for (unsigned int i = 0; i < 4*48*3; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
};

#define GTSER_TO_ARRAY(gt, ba) \
Byte ba##C[3096]; \
int ba##len = mclBnGT_serialize(&ba##C[0], 3096, &gt); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: ba##len]; \
for (unsigned int i = 0; i < ba##len; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
}

#define FR_TO_ARRAY(fr, ba) \
Byte ba##C[32]; \
memcpy(&ba##C[0], &fr, 32); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: 32]; \
for (unsigned int i = 0; i < 32; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
}

#define FRSER_TO_ARRAY(fr, ba) \
Byte ba##C[3096]; \
int ba##len = mclBnFr_serialize(&ba##C[0], 3096, &fr); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: ba##len]; \
for (unsigned int i = 0; i < ba##len; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
}

#define FP_TO_ARRAY(fp, ba) \
Byte ba##C[48]; \
memcpy(&ba##C[0], &fp, 48); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: 48]; \
for (unsigned int i = 0; i < 48; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
}

#define FPSER_TO_ARRAY(fp, ba) \
Byte ba##C[3096]; \
int ba##len = mclBnFp_serialize(&ba##C[0], 3096, &fp); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: ba##len]; \
for (unsigned int i = 0; i < ba##len; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
}

#define FP2_TO_ARRAY(fp2, ba) \
Byte ba##C[96]; \
memcpy(&ba##C[0], &fp2, 96); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: 96]; \
for (unsigned int i = 0; i < 96; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
}

#define FP2SER_TO_ARRAY(fp2, ba) \
Byte ba##C[3096]; \
int ba##len = mclBnFp2_serialize(&ba##C[0], 3096, &fp2); \
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: ba##len]; \
for (unsigned int i = 0; i < ba##len; i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ba##C[i]]]; \
}

#define CARRAY_TO_ARRAY(ca, ba)\
NSMutableArray *ba = [[NSMutableArray alloc] initWithCapacity: sizeof(ca)]; \
for (unsigned int i = 0; i < sizeof(ca); i++) \
{ \
[ba addObject: [NSNumber numberWithUnsignedChar:ca[i]]]; \
}

#endif /* Macros_h */
