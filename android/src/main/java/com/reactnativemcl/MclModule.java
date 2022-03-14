package com.reactnativemcl;

import android.util.Log;
import androidx.annotation.NonNull;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.ReadableMapKeySetIterator;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = MclModule.NAME)
public class MclModule extends ReactContextBaseJavaModule {
    public static final String NAME = "Mcl";

    public MclModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @Override
    @NonNull
    public String getName() {
        return NAME;
    }

    static {
        try {
            System.loadLibrary("cpp");
        } catch (Exception ignored) {
        }
    }

    static public int[] readableMapToIntArray(ReadableMap a) {
        int[] intArray = new int[a.toHashMap().size()];

        ReadableMapKeySetIterator iterator = a.keySetIterator();
        while (iterator.hasNextKey()) {
            String key = iterator.nextKey();
            intArray[Integer.parseInt(key)] = a.getInt(key);
        }

        return intArray;
    }

    static public int[][] readableMapArrayToIntArray(ReadableMap a) {
        int[][] intArray = new int[a.toHashMap().size()][];

        ReadableMapKeySetIterator iterator = a.keySetIterator();
        while (iterator.hasNextKey()) {
            String key = iterator.nextKey();
            intArray[Integer.parseInt(key)] = readableMapToIntArray(a.getMap(key));
        }

        return intArray;
    }

    // FR

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frDeserialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _frDeserialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frSetLittleEndian(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _frSetLittleEndian(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frSetLittleEndianMod(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _frSetLittleEndianMod(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frSetBigEndianMod(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _frSetBigEndianMod(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frSerialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _frSerialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        }
        catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frSetHashOf(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _frSetHashOf(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int frIsZero(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _frIsZero(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int frIsOne(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _frIsOne(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int frIsEqual(ReadableMap a, ReadableMap b) {
        int[] byteArray = readableMapToIntArray(a);
        int[] byteArray2 = readableMapToIntArray(b);

        int result = _frIsEqual(byteArray, byteArray2);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frNeg(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _frNeg(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frSqr(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _frSqr(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frInv(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _frInv(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frSquareRoot(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _frSquareRoot(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frAdd(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _frAdd(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frSub(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _frSub(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frMul(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _frMul(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frDiv(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _frDiv(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frSetInt32(int a) {
        int[] result = _frSetInt32(a);
        WritableArray array = Arguments.makeNativeArray(result);
        return array;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray frSetStr(java.lang.String a, int b) {
        int[] result = _frSetStr(a, b);
        WritableArray array = Arguments.makeNativeArray(result);
        return array;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public String frGetStr(ReadableMap a, int b) {
        int[] byteArray = readableMapToIntArray(a);
        String result = _frGetStr(byteArray, b);
        return result;
    }

    // FP

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpDeserialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpDeserialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpSetLittleEndian(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpSetLittleEndian(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpSetLittleEndianMod(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpSetLittleEndianMod(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpSetBigEndianMod(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpSetBigEndianMod(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpSerialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpSerialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        }
        catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpSetHashOf(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpSetHashOf(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int fpIsZero(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _fpIsZero(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int fpIsOne(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _fpIsOne(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int fpIsEqual(ReadableMap a, ReadableMap b) {
        int[] byteArray = readableMapToIntArray(a);
        int[] byteArray2 = readableMapToIntArray(b);

        int result = _fpIsEqual(byteArray, byteArray2);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpNeg(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpNeg(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpSqr(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpSqr(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpInv(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpInv(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpSquareRoot(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpSquareRoot(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpMapToG1(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fpMapToG1(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpAdd(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _fpAdd(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpSub(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _fpSub(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpMul(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _fpMul(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpDiv(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _fpDiv(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpSetInt32(int a) {
        int[] result = _fpSetInt32(a);
        WritableArray array = Arguments.makeNativeArray(result);
        return array;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fpSetStr(java.lang.String a, int b) {
        int[] result = _fpSetStr(a, b);
        WritableArray array = Arguments.makeNativeArray(result);
        return array;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public String fpGetStr(ReadableMap a, int b) {
        int[] byteArray = readableMapToIntArray(a);
        String result = _fpGetStr(byteArray, b);
        return result;
    }

    // FP2

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2Deserialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fp2Deserialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2Serialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fp2Serialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        }
        catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int fp2IsZero(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _fp2IsZero(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int fp2IsOne(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _fp2IsOne(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int fp2IsEqual(ReadableMap a, ReadableMap b) {
        int[] byteArray = readableMapToIntArray(a);
        int[] byteArray2 = readableMapToIntArray(b);

        int result = _fp2IsEqual(byteArray, byteArray2);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2Neg(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fp2Neg(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2Sqr(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fp2Sqr(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2Inv(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fp2Inv(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2SquareRoot(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fp2SquareRoot(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2MapToG2(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _fp2MapToG2(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2Add(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _fp2Add(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2Sub(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _fp2Sub(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2Mul(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _fp2Mul(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray fp2Div(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _fp2Div(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    // G1

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1Deserialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g1Deserialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1Serialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g1Serialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        }
        catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1SetHashAndMapTo(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g1SetHashAndMapTo(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int g1IsZero(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _g1IsZero(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int g1IsValid(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _g1IsValid(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int g1IsValidOrder(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _g1IsValidOrder(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int g1IsEqual(ReadableMap a, ReadableMap b) {
        int[] byteArray = readableMapToIntArray(a);
        int[] byteArray2 = readableMapToIntArray(b);

        int result = _g1IsEqual(byteArray, byteArray2);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1GetBasePoint() {
        int[] result = _g1GetBasePoint();

        WritableArray array = Arguments.makeNativeArray(result);
        return array;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1Neg(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g1Neg(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1Normalize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g1Normalize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1Dbl(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g1Dbl(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1Add(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _g1Add(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1Sub(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _g1Sub(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1Mul(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _g1Mul(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g1MulVec(ReadableMap a, ReadableMap b) {
        try {
            int[][] byteArray = readableMapArrayToIntArray(a);
            int[][] byteArray2 = readableMapArrayToIntArray(b);

            int[] result = _g1MulVec(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    // G2

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g2Deserialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g2Deserialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g2Serialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g2Serialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        }
        catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g2SetHashAndMapTo(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g2SetHashAndMapTo(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int g2IsZero(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _g2IsZero(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int g2IsValid(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _g2IsValid(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int g2IsValidOrder(ReadableMap a) {
        int[] byteArray = readableMapToIntArray(a);

        int result = _g2IsValidOrder(byteArray);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int g2IsEqual(ReadableMap a, ReadableMap b) {
        int[] byteArray = readableMapToIntArray(a);
        int[] byteArray2 = readableMapToIntArray(b);

        int result = _g2IsEqual(byteArray, byteArray2);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g2Neg(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g2Neg(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g2Normalize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g2Normalize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g2Dbl(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _g2Dbl(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g2Add(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _g2Add(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g2Sub(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _g2Sub(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g2Mul(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _g2Mul(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray g2MulVec(ReadableMap a, ReadableMap b) {
        try {
            int[][] byteArray = readableMapArrayToIntArray(a);
            int[][] byteArray2 = readableMapArrayToIntArray(b);

            int[] result = _g2MulVec(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    // GT

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtDeserialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _gtDeserialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }


    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtSerialize(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _gtSerialize(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        }
        catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int gtIsEqual(ReadableMap a, ReadableMap b) {
        int[] byteArray = readableMapToIntArray(a);
        int[] byteArray2 = readableMapToIntArray(b);

        int result = _gtIsEqual(byteArray, byteArray2);

        return result;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtNeg(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _gtNeg(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtSqr(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _gtSqr(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtInv(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _gtInv(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtAdd(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _gtAdd(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtSub(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _gtSub(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtMul(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _gtMul(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtDiv(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _gtDiv(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtPow(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _gtPow(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtSetInt32(int a) {
        int[] result = _gtSetInt32(a);
        WritableArray array = Arguments.makeNativeArray(result);
        return array;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray gtSetStr(java.lang.String a, int b) {
        int[] result = _gtSetStr(a, b);
        WritableArray array = Arguments.makeNativeArray(result);
        return array;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public String gtGetStr(ReadableMap a, int b) {
        int[] byteArray = readableMapToIntArray(a);
        String result = _gtGetStr(byteArray, b);
        return result;
    }

    // Other methods
    @ReactMethod(isBlockingSynchronousMethod = true)
    public void setMapToMode(int a) {
        _setMapToMode(a);
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public void setETHserialization(int a) {
        _setETHserialization(a);
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public void verifyOrderG1(int a) {
        _verifyOrderG1(a);
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public void verifyOrderG2(int a) {
        _verifyOrderG2(a);
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public int getUint64NumToPrecompute() {
        return getUint64NumToPrecompute();
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray pairing(ReadableMap a, ReadableMap b) {
        try {
            int[] byteArray = readableMapToIntArray(a);
            int[] byteArray2 = readableMapToIntArray(b);

            int[] result = _pairing(byteArray, byteArray2);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray finalExp(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _finalExp(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public WritableArray precomputeG2(ReadableMap a) {
        try {
            int[] byteArray = readableMapToIntArray(a);

            int[] result = _precomputeG2(byteArray);

            if (result != null) {
                WritableArray array = Arguments.makeNativeArray(result);
                return array;
            }
        } catch (Exception e) {
            Log.d("ReactNative", e.toString());
        }
        return null;
    }

    @ReactMethod
    public void initialize(int a, Promise promise) {
        if (_initialize(a)) {
          Log.d("ReactNative","init ok");
          promise.resolve(true);
        }
        else
          promise.reject("","");
    }

    public static native boolean _initialize(int curve);

    public static native int[] _frDeserialize(int[] a);
    public static native int[] _frSerialize(int[] a);
    public static native int[] _frSetLittleEndian(int[] a);
    public static native int[] _frSetLittleEndianMod(int[] a);
    public static native int[] _frSetBigEndianMod(int[] a);
    public static native int[] _frSetHashOf(int[] a);
    public static native int[] _frSetInt32(int a);
    public static native int[] _frSetStr(java.lang.String a, int b);
    public static native java.lang.String _frGetStr(int[] a, int b);
    public static native int _frIsZero(int[] a);
    public static native int _frIsOne(int[] a);
    public static native int _frIsEqual(int[] a, int[] b);
    public static native int[] _frNeg(int[] a);
    public static native int[] _frSqr(int[] a);
    public static native int[] _frInv(int[] a);
    public static native int[] _frSquareRoot(int[] a);
    public static native int[] _frAdd(int[] a, int[] b);
    public static native int[] _frSub(int[] a, int[] b);
    public static native int[] _frMul(int[] a, int[] b);
    public static native int[] _frDiv(int[] a, int[] b);

    public static native int[] _fpDeserialize(int[] a);
    public static native int[] _fpSerialize(int[] a);
    public static native int[] _fpSetLittleEndian(int[] a);
    public static native int[] _fpSetLittleEndianMod(int[] a);
    public static native int[] _fpSetBigEndianMod(int[] a);
    public static native int[] _fpSetHashOf(int[] a);
    public static native int[] _fpMapToG1(int[] a);
    public static native int[] _fpSetInt32(int a);
    public static native int[] _fpSetStr(java.lang.String a, int b);
    public static native java.lang.String _fpGetStr(int[] a, int b);
    public static native int _fpIsZero(int[] a);
    public static native int _fpIsOne(int[] a);
    public static native int _fpIsEqual(int[] a, int[] b);
    public static native int[] _fpNeg(int[] a);
    public static native int[] _fpSqr(int[] a);
    public static native int[] _fpInv(int[] a);
    public static native int[] _fpSquareRoot(int[] a);
    public static native int[] _fpAdd(int[] a, int[] b);
    public static native int[] _fpSub(int[] a, int[] b);
    public static native int[] _fpMul(int[] a, int[] b);
    public static native int[] _fpDiv(int[] a, int[] b);

    public static native int[] _fp2Deserialize(int[] a);
    public static native int[] _fp2Serialize(int[] a);
    public static native int[] _fp2MapToG2(int[] a);
    public static native int _fp2IsZero(int[] a);
    public static native int _fp2IsOne(int[] a);
    public static native int _fp2IsEqual(int[] a, int[] b);
    public static native int[] _fp2Neg(int[] a);
    public static native int[] _fp2Sqr(int[] a);
    public static native int[] _fp2Inv(int[] a);
    public static native int[] _fp2SquareRoot(int[] a);
    public static native int[] _fp2Add(int[] a, int[] b);
    public static native int[] _fp2Sub(int[] a, int[] b);
    public static native int[] _fp2Mul(int[] a, int[] b);
    public static native int[] _fp2Div(int[] a, int[] b);

    public static native int[] _g1Deserialize(int[] a);
    public static native int[] _g1Serialize(int[] a);
    public static native int[] _g1SetHashAndMapTo(int[] a);
    public static native int _g1IsZero(int[] a);
    public static native int _g1IsValid(int[] a);
    public static native int _g1IsEqual(int[] a, int[] b);
    public static native int _g1IsValidOrder(int[] a);
    public static native int[] _g1GetBasePoint();
    public static native int[] _g1Neg(int[] a);
    public static native int[] _g1Normalize(int[] a);
    public static native int[] _g1Dbl(int[] a);
    public static native int[] _g1Add(int[] a, int[] b);
    public static native int[] _g1Sub(int[] a, int[] b);
    public static native int[] _g1Mul(int[] a, int[] b);
    public static native int[] _g1MulVec(int[][] a, int[][] b);

    public static native int[] _g2Deserialize(int[] a);
    public static native int[] _g2Serialize(int[] a);
    public static native int[] _g2SetHashAndMapTo(int[] a);
    public static native int _g2IsZero(int[] a);
    public static native int _g2IsValid(int[] a);
    public static native int _g2IsEqual(int[] a, int[] b);
    public static native int _g2IsValidOrder(int[] a);
    public static native int[] _g2Neg(int[] a);
    public static native int[] _g2Normalize(int[] a);
    public static native int[] _g2Dbl(int[] a);
    public static native int[] _g2Add(int[] a, int[] b);
    public static native int[] _g2Sub(int[] a, int[] b);
    public static native int[] _g2Mul(int[] a, int[] b);
    public static native int[] _g2MulVec(int[][] a, int[][] b);

    public static native int[] _gtDeserialize(int[] a);
    public static native int[] _gtSerialize(int[] a);
    public static native int[] _gtSetInt32(int a);
    public static native int[] _gtSetStr(java.lang.String a, int b);
    public static native java.lang.String _gtGetStr(int[] a, int b);
    public static native int _gtIsEqual(int[] a, int[] b);
    public static native int[] _gtNeg(int[] a);
    public static native int[] _gtSqr(int[] a);
    public static native int[] _gtInv(int[] a);
    public static native int[] _gtAdd(int[] a, int[] b);
    public static native int[] _gtSub(int[] a, int[] b);
    public static native int[] _gtMul(int[] a, int[] b);
    public static native int[] _gtDiv(int[] a, int[] b);
    public static native int[] _gtPow(int[] a, int[] b);

    public static native int _getUint64NumToPrecompute();
    public static native int[] _precomputeG2(int[] a);
    public static native int[] _pairing(int a[], int b[]);
    public static native int[] _finalExp(int[] a);

    public static native void _setMapToMode(int a);
    public static native void _setETHserialization(int a);
    public static native void _verifyOrderG1(int a);
    public static native void _verifyOrderG2(int a);
}
