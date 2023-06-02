#include "BinaryNode.h"

template <class T>
BinaryNode<T>::BinaryNode() : mLeftNodePtr(nullptr), mRightNodePtr(nullptr) {}

template <class T>
BinaryNode<T>::BinaryNode(const T &value) : mValue(value), mLeftNodePtr(nullptr), mRightNodePtr(nullptr) {}

template <class T>
BinaryNode<T>::BinaryNode(const T &value, BinaryNode<T> *lPtr, BinaryNode<T> *rPtr) : mValue(value), mLeftNodePtr(lPtr), mRightNodePtr(rPtr) {}

template <class T>
void BinaryNode<T>::setValue(const T &value) {
    mValue = value;
}

template <class T>
T BinaryNode<T>::getValue() const {
    return mValue;
}

template <class T>
bool BinaryNode<T>::isLeaf() const {
    return !mRightNodePtr && !mLeftNodePtr;
}

template <class T>
BinaryNode<T> *BinaryNode<T>::getLeftChildPtr() const {
    return mLeftNodePtr;
}

template <class T>
BinaryNode<T> *BinaryNode<T>::getRightChildPtr() const {
    return mRightNodePtr;
}

template <class T>
void BinaryNode<T>::setLeftChildPtr(BinaryNode<T> *const lPtr) {
    mLeftNodePtr = lPtr;
}

template <class T>
void BinaryNode<T>::setRightChildPtr(BinaryNode<T> *const rPtr) {
    mRightNodePtr = rPtr;
}