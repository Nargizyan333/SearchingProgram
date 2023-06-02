#include "BinarySearchTree.h"
#include "BinaryNode.h"

#include <iostream>
#include <string>
#include <fstream>

template <class T>
BinaryNode<T> *BinarySearchTree<T>::copyTree(const BinaryNode<T> *treePtr) const {
    if (treePtr == nullptr) {
        return nullptr;
    } else {
        BinaryNode<T>* newNode = new BinaryNode<T>(treePtr->getValue());
        newNode -> setLeftChildPtr(copyTree(treePtr -> getLeftChildPtr()));
        newNode -> setRightChildPtr(copyTree(treePtr -> getRightChildPtr()));
        return newNode;
    }
}

template <class T>
BinaryNode<T> *BinarySearchTree<T>::insertInorder(BinaryNode<T> *subTreePtr, BinaryNode<T> *newNode, bool &success) {
    if (subTreePtr == nullptr) {
        subTreePtr = newNode;
        success = true;
    } else {
        if (newNode -> getValue() > subTreePtr -> getValue()) {
            BinaryNode<T> *rightPtr = insertInorder(subTreePtr -> getRightChildPtr(), newNode, success);
            subTreePtr->setRightChildPtr(rightPtr);
        } else if (newNode -> getValue() < subTreePtr -> getValue()) {
            BinaryNode<T> *leftPtr = insertInorder(subTreePtr -> getLeftChildPtr(), newNode, success);
            subTreePtr->setLeftChildPtr(leftPtr);
        } else {
            success = false;
        }
    }
    return subTreePtr;
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::findLeftmostNode(BinaryNode<T>* subTreePtr) const {
    if (subTreePtr == nullptr)
        return nullptr;

    BinaryNode<T>* currentNode = subTreePtr;
    while (currentNode->getLeftChildPtr() != nullptr)
        currentNode = currentNode->getLeftChildPtr();

    return currentNode;
}

template<class T>
BinaryNode<T>* BinarySearchTree<T>::removeLeftmostNode(BinaryNode<T>* subTreePtr) {
    if (subTreePtr == nullptr)
        return nullptr;

    BinaryNode<T>* currentNode = subTreePtr;
    BinaryNode<T>* parentNode = nullptr;

    while (currentNode->getLeftChildPtr() != nullptr) {
        parentNode = currentNode;
        currentNode = currentNode->getLeftChildPtr();
    }

    if (parentNode != nullptr)
        parentNode->setLeftChildPtr(currentNode->getRightChildPtr());
    else
        subTreePtr = currentNode->getRightChildPtr();

    delete currentNode;
    return subTreePtr;
}

template<class T>
BinaryNode<T>* BinarySearchTree<T>::removeValue(BinaryNode<T>* subTreePtr, const T& target, bool& success) {
    if (subTreePtr == nullptr) {
        success = false;
        return nullptr;
    }

    if (subTreePtr->getValue() == target) {
        subTreePtr = removeNode(subTreePtr);
        success = true;
        return subTreePtr;
    }

    BinaryNode<T>* tempNode = removeValue(subTreePtr->getLeftChildPtr(), target, success);
    subTreePtr->setLeftChildPtr(tempNode);

    if (!success) {
        tempNode = removeValue(subTreePtr->getRightChildPtr(), target, success);
        subTreePtr->setRightChildPtr(tempNode);
    }

    return subTreePtr;
}

template<class T>
BinaryNode<T>* BinarySearchTree<T>::removeNode(BinaryNode<T>* nodePtr) {
    if (nodePtr->isLeaf()) {
        delete nodePtr;
        return nullptr;
    }

    if (nodePtr->getLeftChildPtr() == nullptr) {
        BinaryNode<T>* rightChildPtr = nodePtr->getRightChildPtr();
        delete nodePtr;
        return rightChildPtr;
    }

    if (nodePtr->getRightChildPtr() == nullptr) {
        BinaryNode<T>* leftChildPtr = nodePtr->getLeftChildPtr();
        delete nodePtr;
        return leftChildPtr;
    }

    BinaryNode<T>* tempNode = findLeftmostNode(nodePtr->getRightChildPtr());
    nodePtr->setValue(tempNode->getValue());
    nodePtr->setRightChildPtr(removeLeftmostNode(nodePtr->getRightChildPtr()));
    return nodePtr;
}

template <class T>
void BinarySearchTree<T>::destroyTree(BinaryNode<T> *subTreePtr) {
    if (subTreePtr) {
        destroyTree(subTreePtr -> getLeftChildPtr());
        destroyTree(subTreePtr -> getRightChildPtr());
        delete subTreePtr;
    }
    mRoot = nullptr;
}

template <class T>
BinaryNode<T> *BinarySearchTree<T>::findNode(BinaryNode<T> *treePtr, const T &target) const {
    if (!treePtr) {
        return nullptr;
    }
    if (target < treePtr -> getValue()) {
        return findNode(treePtr -> getLeftChildPtr(), target);
    } else if (target > treePtr -> getValue()){
        return findNode(treePtr -> getRightChildPtr(), target);
    } else {
        return treePtr;
    }
}

template <class T>
int BinarySearchTree<T>::getNumberOfNodesHelper(BinaryNode<T> *subTreePtr) const {
    if (!subTreePtr) {
        return 0;
    }
    int left = getNumberOfNodesHelper(subTreePtr -> getLeftChildPtr());
    int right = getNumberOfNodesHelper(subTreePtr -> getRightChildPtr());
    return left + right + 1;
}

template <class T>
int BinarySearchTree<T>::getHeightHelper(BinaryNode<T> *subTreePtr) const {
    if (subTreePtr == nullptr) {
        return 0;
    } else {
        int leftHeight = getHeightHelper(subTreePtr->getLeftChildPtr());
        int rightHeight = getHeightHelper(subTreePtr->getRightChildPtr());
        return 1 + std::max(leftHeight, rightHeight);
    }
}

template <class T>
void BinarySearchTree<T>::preorder(BinaryNode<T> *subTreePtr, void visit(T&&)) {
    if (subTreePtr) {
        visit(subTreePtr -> getValue());
        preorder(subTreePtr -> getLeftChildPtr(), visit);
        preorder(subTreePtr -> getRightChildPtr(), visit);
    }
}

template <class T>
void BinarySearchTree<T>::inorder(BinaryNode<T> *subTreePtr, void visit(T&&)) {
    if (subTreePtr) {
        inorder(subTreePtr -> getLeftChildPtr(), visit);
        visit(subTreePtr -> getValue());
        inorder(subTreePtr -> getRightChildPtr(), visit);
    }
}

template <class T>
void BinarySearchTree<T>::postorder(BinaryNode<T> *subTreePtr, void visit(T&&)) {
    if (subTreePtr) {
        postorder(subTreePtr -> getLeftChildPtr(), visit);
        postorder(subTreePtr -> getRightChildPtr(), visit);
        visit(subTreePtr -> getValue());
    }
}

template <class T>
void BinarySearchTree<T>::toFileHelper(BinaryNode<T> *subTreePtr) const {
    std::string treeInStr;
    toString(subTreePtr, treeInStr);
    std::ofstream fout;
    fout.open("./BST.txt");
    fout << treeInStr << std::endl;
    fout.close();
}

template <class T>
void BinarySearchTree<T>::toString(BinaryNode<T> *subTreePtr, std::string& str) const {
    if (!subTreePtr) return;
    char num[sizeof(T)];
    memcpy(num, &(subTreePtr -> mValue), sizeof(T));
    for (int i = 0; i < sizeof(T); ++i) {
        str.push_back(num[i]);
    }
    toString(subTreePtr -> getLeftChildPtr(), str);
    toString(subTreePtr -> getRightChildPtr(), str);
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::toBSTHelper(const std::string& buffer, int& pos, int minValue, int maxValue) {
    if (pos >= buffer.size()) return NULL;
    int value;
    memcpy(&value, &buffer[pos], sizeof(T));
    if (value < minValue || value > maxValue) return NULL;

    BinaryNode<T>* node = new BinaryNode<T>(value);
    pos += sizeof(T);
    node -> setLeftChildPtr(toBSTHelper(buffer, pos, minValue, value));
    node ->setRightChildPtr(toBSTHelper(buffer, pos, value, maxValue));
    return node;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(const T& rootItem) : mRoot(new BinaryNode<T>(rootItem)) {}

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &tree) {
    mRoot = copyTree(tree.mRoot);
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
    clear();
}

template <class T>
bool BinarySearchTree<T>::isEmpty() const {
    return mRoot == nullptr;
}

template <class T>
int BinarySearchTree<T>::getHeight() const {
    return getHeightHelper(mRoot);
}

template <class T>
int BinarySearchTree<T>::getNumberOfNodes() const {
    return getNumberOfNodesHelper(mRoot);
}

template <class T>
T BinarySearchTree<T>::getRootData() const {
    return mRoot -> getValue();
}

template <class T>
bool BinarySearchTree<T>::add(const T &newEntry) {
    bool success = false;
    insertInorder(mRoot, new BinaryNode<T>(newEntry), success);
    return success;
}

template <class T>
bool BinarySearchTree<T>::remove(const T &anEntry) {
    bool success = false;
    removeValue(mRoot, anEntry, success);
    return success;
}

template <class T>
void BinarySearchTree<T>::clear() {
    destroyTree(mRoot);
}

template <class T>
bool BinarySearchTree<T>::contains(const T &anEntry) const {
    return findNode(mRoot, anEntry);
}

template <class T>
void BinarySearchTree<T>::preorderTraversal(void visit(T&&)) {
    preorder(mRoot, visit);
}

template <class T>
void BinarySearchTree<T>::inorderTraversal(void visit(T&&)) {
    inorder(mRoot, visit);
}

template <class T>
void BinarySearchTree<T>::postorderTraversal(void visit(T&&)) {
    postorder(mRoot, visit);
}

template <class T>
void BinarySearchTree<T>::toFile() const {
    toFileHelper(mRoot);
}

template <class T>
void BinarySearchTree<T>::toBST(std::ifstream &fin) {
    std::string data;
    fin >> data;
    int pos = 0;
    mRoot = toBSTHelper(data, pos, INT_MIN, INT_MAX);
}