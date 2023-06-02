#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <functional>

template <class T>
class BinaryNode;

template <class T>
class BinarySearchTree {
private:
    BinaryNode<T>* mRoot;
protected:
    BinaryNode<T>* copyTree(const BinaryNode<T> *treePtr) const;
    BinaryNode<T>* insertInorder(BinaryNode<T>* subTreePtr, BinaryNode<T>* newNode, bool& success);
    BinaryNode<T>* findLeftmostNode(BinaryNode<T>* subTreePtr) const;
    BinaryNode<T>* removeLeftmostNode(BinaryNode<T>* subTreePtr);
    BinaryNode<T>* removeValue(BinaryNode<T>* subTreePtr, const T& target, bool& success);
    BinaryNode<T>* removeNode(BinaryNode<T>* nodePtr);
    void destroyTree(BinaryNode<T>* subTreePtr);
    BinaryNode<T>* findNode(BinaryNode<T>* treePtr, const T& target) const;
    int getNumberOfNodesHelper(BinaryNode<T>* subTreePtr) const;
    int getHeightHelper(BinaryNode<T>* subTreePtr) const;
    void preorder(BinaryNode<T>* subTreePtr, void visit(T&&));
    void inorder(BinaryNode<T>* subTreePtr, void visit(T&&));
    void postorder(BinaryNode<T>* subTreePtr, void visit(T&&));
    void toFileHelper(BinaryNode<T>* subTreePtr) const;
    void toString(BinaryNode<T>* subTreePtr, std::string& str) const;
    BinaryNode<T>* toBSTHelper(const std::string& buffer, int& pos, int minValue, int maxValue);
public:
    BinarySearchTree(const T& rootItem);
    BinarySearchTree(const BinarySearchTree<T>& tree);
    ~BinarySearchTree();
    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;
    T getRootData() const;
    bool add(const T& newEntry);
    bool remove(const T& anEntry);
    void clear();
    bool contains(const T& anEntry) const;
    void preorderTraversal(void visit(T&&));
    void inorderTraversal(void visit(T&&));
    void postorderTraversal(void visit(T&&));
    void toFile() const;
    void toBST(std::ifstream& fin);
};

#endif