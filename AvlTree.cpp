#include "AvlTree.h"

//Constructor
template <class Comparable>
AvlTree<Comparable>::AvlTree(const Comparable & notFound) : ITEM_NOT_FOUND(notFound), root(nullptr) { }

//Copy Constructor
template <class Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree<Comparable> & rhs) : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), root(nullptr) {
    *this = rhs;
}

//Destructor
template <class Comparable>
AvlTree<Comparable>::~AvlTree() {
    makeEmpty();
}

//Assignment Operator
template <class Comparable>
const AvlTree<Comparable> & AvlTree<Comparable>::operator=(const AvlTree<Comparable> & rhs) {
    if (this != &rhs) {
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}

//UTILITY
template <class Comparable>
void AvlTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

template <class Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode<Comparable> * & t) const {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template <class Comparable>
void AvlTree<Comparable>::printTree() const {
    if (isEmpty())
        std::cout << "The tree is empty." << std::endl;
    else
        printTree(root);
}

template <class Comparable>
void AvlTree<Comparable>::printTree(AvlNode<Comparable> *t) const {
    if (t != nullptr) {
        printTree(t->left);
        std::cout << t->element << " ";
        printTree(t->right);
    }
}

template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable & x) {
    remove(x, root);
}

template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable & x, AvlNode<Comparable> * & t) const {
    if (t == nullptr) return; // Item not found; do nothing.

    // Step 1: Perform standard BST delete
    if (x < t->element)
        remove(x, t->left);
    else if (x > t->element)
        remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr) { // Two children
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else {
        AvlNode<Comparable> *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }

    if (t == nullptr) return; // Tree had only one node.

    // Step 2: Update height of the current node.
    t->height = max(height(t->left), height(t->right)) + 1;

    // Step 3: Rebalance the tree
    balance(t);
}

template <class Comparable>
void AvlTree<Comparable>::balance(AvlNode<Comparable> * & t) const {
    if (t == nullptr) return;
    if (height(t->left) - height(t->right) > 1) {
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    }
    else if (height(t->right) - height(t->left) > 1) {
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);
        else
            doubleWithRightChild(t);
    }
    t->height = max(height(t->left), height(t->right)) + 1;
}


template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::clone(AvlNode<Comparable> *t) const {
    if (t == nullptr)
        return nullptr;
    else
        return new AvlNode<Comparable>(t->element, clone(t->left), clone(t->right), t->height);
}

template <class Comparable>
const Comparable & AvlTree<Comparable>::elementAt(AvlNode<Comparable> *t) const {
    return t == nullptr ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
const Comparable & AvlTree<Comparable>::findMin() const {
    return elementAt(findMin(root));
}

template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::findMin(AvlNode<Comparable> *t) const {
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

template <class Comparable>
const Comparable & AvlTree<Comparable>::findMax() const {
    return elementAt(findMax(root));
}


template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::findMax(AvlNode<Comparable> *t) const {
    if (t != nullptr)
        while (t->right != nullptr)
            t = t->right;
    return t;
}

template <class Comparable>
const Comparable & AvlTree<Comparable>::find(const Comparable & x) const {
    return elementAt(find(x, root));
}

template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::find(const Comparable & x, AvlNode<Comparable> *t) const {
    while (t != nullptr)
        if (x < t->element)
            t = t->left;
        else if (t->element < x)
            t = t->right;
        else
            return t;    // Match

    return nullptr;   // No match
}

template <class Comparable>
bool AvlTree<Comparable>::isEmpty() const {
    return root == nullptr;
}

template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable & x) {
    insert(x, root);
}

template <class Comparable>
int AvlTree<Comparable>::height(AvlNode<Comparable> *t) const
{
    if (t == nullptr)
        return -1;
    return t->height;
}

template <class Comparable>
int AvlTree<Comparable>::max(int lhs, int rhs) const
{
    if (lhs > rhs)
        return lhs;

    return rhs;            
}

template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable & x, AvlNode<Comparable> * & t) const
{
    if (t == nullptr){
        t = new AvlNode<Comparable>(x, nullptr, nullptr);
    }
    else if (x < t->element){
        // X should be inserted to the left tree!
        insert(x, t->left);
        // Check if the left tree is out of balance (left subtree grew in height!)
        if (height(t->left) - height(t->right) == 2){
            if (x < t->left->element)  // X was inserted to the left-left subtree!
                rotateWithLeftChild(t);
            else			     // X was inserted to the left-right subtree!
                doubleWithLeftChild(t);
        }
    }
    else if( t->element < x ){
        // Otherwise X is inserted to the right subtree
        insert(x, t->right);
        if (height(t->right) - height(t->left) == 2)
        // height of the right subtree increased
            if (t->right->element < x)
        // X was inserted to right-right subtree
            rotateWithRightChild(t);
        else // X was inserted to right-left subtree
            doubleWithRightChild(t);
    }
    else
        ;  // Duplicate; do nothing
    
    // update the height the node
    t->height = max( height(t->left), height(t->right)) + 1;
}

template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode<Comparable> * & k2) const
{
    AvlNode<Comparable> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild(AvlNode<Comparable> * & k1) const
{
    AvlNode<Comparable> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const
{
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild( AvlNode<Comparable> * & k1 ) const
{
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}





