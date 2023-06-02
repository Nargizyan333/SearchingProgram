#ifndef BINARYNODE_H
#define BINARYNODE_H

template <class T>
class BinaryNode {
private:
    BinaryNode<T>* mLeftNodePtr;
    BinaryNode<T>* mRightNodePtr;
public:
    T mValue;
    BinaryNode();
    BinaryNode(const T& value);
    BinaryNode(const T& value, BinaryNode<T>* lPtr, BinaryNode<T>* rPtr);
    void setValue(const T& value);
    T getValue() const;
    bool isLeaf() const;
    BinaryNode<T>* getLeftChildPtr() const;
    BinaryNode<T>* getRightChildPtr() const;
    void setLeftChildPtr(BinaryNode<T>* lPtr);
    void setRightChildPtr(BinaryNode<T>* rPtr);
};

#endif
