/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.herumi.bls;

public class SecretKeyVec extends java.util.AbstractList<SecretKey> implements java.util.RandomAccess {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected SecretKeyVec(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(SecretKeyVec obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        BlsJNI.delete_SecretKeyVec(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public SecretKeyVec(SecretKey[] initialElements) {
    this();
    reserve(initialElements.length);

    for (SecretKey element : initialElements) {
      add(element);
    }
  }

  public SecretKeyVec(Iterable<SecretKey> initialElements) {
    this();
    for (SecretKey element : initialElements) {
      add(element);
    }
  }

  public SecretKey get(int index) {
    return doGet(index);
  }

  public SecretKey set(int index, SecretKey e) {
    return doSet(index, e);
  }

  public boolean add(SecretKey e) {
    modCount++;
    doAdd(e);
    return true;
  }

  public void add(int index, SecretKey e) {
    modCount++;
    doAdd(index, e);
  }

  public SecretKey remove(int index) {
    modCount++;
    return doRemove(index);
  }

  protected void removeRange(int fromIndex, int toIndex) {
    modCount++;
    doRemoveRange(fromIndex, toIndex);
  }

  public int size() {
    return doSize();
  }

  public SecretKeyVec() {
    this(BlsJNI.new_SecretKeyVec__SWIG_0(), true);
  }

  public SecretKeyVec(SecretKeyVec other) {
    this(BlsJNI.new_SecretKeyVec__SWIG_1(SecretKeyVec.getCPtr(other), other), true);
  }

  public long capacity() {
    return BlsJNI.SecretKeyVec_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    BlsJNI.SecretKeyVec_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return BlsJNI.SecretKeyVec_isEmpty(swigCPtr, this);
  }

  public void clear() {
    BlsJNI.SecretKeyVec_clear(swigCPtr, this);
  }

  public SecretKeyVec(int count, SecretKey value) {
    this(BlsJNI.new_SecretKeyVec__SWIG_2(count, SecretKey.getCPtr(value), value), true);
  }

  private int doSize() {
    return BlsJNI.SecretKeyVec_doSize(swigCPtr, this);
  }

  private void doAdd(SecretKey x) {
    BlsJNI.SecretKeyVec_doAdd__SWIG_0(swigCPtr, this, SecretKey.getCPtr(x), x);
  }

  private void doAdd(int index, SecretKey x) {
    BlsJNI.SecretKeyVec_doAdd__SWIG_1(swigCPtr, this, index, SecretKey.getCPtr(x), x);
  }

  private SecretKey doRemove(int index) {
    return new SecretKey(BlsJNI.SecretKeyVec_doRemove(swigCPtr, this, index), true);
  }

  private SecretKey doGet(int index) {
    return new SecretKey(BlsJNI.SecretKeyVec_doGet(swigCPtr, this, index), false);
  }

  private SecretKey doSet(int index, SecretKey val) {
    return new SecretKey(BlsJNI.SecretKeyVec_doSet(swigCPtr, this, index, SecretKey.getCPtr(val), val), true);
  }

  private void doRemoveRange(int fromIndex, int toIndex) {
    BlsJNI.SecretKeyVec_doRemoveRange(swigCPtr, this, fromIndex, toIndex);
  }

}
