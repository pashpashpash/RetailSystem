#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parentNode);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parentNode, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a balance of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parentNode)
    : Node<Key, Value>(key, value, parentNode),
      balance_(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* Getter function for the parentNode. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left childNode. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right childNode. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    // Methods for inserting/erasing (removing) elements from the tree. 
    // You must implement both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    virtual void erase(const Key& key);
    int p_size = 0;

private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */

    /* You should write these helpers for sure.  You may add others. */
    void rotateLeft (AVLNode<Key, Value> *n);
    void rotateRight (AVLNode<Key, Value> *n);
    void rotateHelper(AVLNode<Key, Value> *n, bool isLeft);
    void insertFix(AVLNode<Key, Value>* parentNode, AVLNode<Key,Value>* insertNode);
    void eraseFix(AVLNode<Key, Value>* parentNode, int diff);
    void splay(AVLNode<Key, Value>* node);
    /* A provided helper function to swap 2 nodes location in the tree */
    void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    AVLNode<Key, Value> *z = static_cast<AVLNode<Key,Value>*>(this->mRoot);
    AVLNode<Key, Value> *p = NULL;
    
    while( z != NULL ) 
    {
      p = z;
      if( z->getKey() < keyValuePair.first  ) z = z->getRight();
      else z = z->getLeft();
    }
    
    z = new AVLNode<Key, Value>( keyValuePair.first, keyValuePair.second, NULL );
    z->setParent(p);
    
    if( !p ) this->mRoot = static_cast<AVLNode<Key,Value>*>(z);
    else if( p->getKey() < z->getKey()) p->setRight(z);
    else p->setLeft(z);
    
    splay( z );
    p_size++;

    //------

    // AVLNode<Key, Value> *node = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::internalFind(keyValuePair.first));
    // if(node != NULL) //if a node with the same key already exists, we just want to update the value.
    // {
    //     node->setValue(keyValuePair.second);
    //     return;
    // }
    // AVLNode<Key, Value> *insertNode = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL); //(const Key& key, const Value& value, AVLNode<Key, Value>* parentNode

    //     if (this->mRoot == NULL) 
    //     {
    //         this->mRoot = insertNode;
    //         return;
    //     }

    //     AVLNode<Key, Value> *parentNode = NULL;
    //     AVLNode<Key, Value> *next = static_cast<AVLNode<Key,Value>*>(this->mRoot);

    //     while (true) 
    //     {
    //         if(next->getKey()== keyValuePair.first)
    //         {
    //             next->setValue(keyValuePair.second);
    //         }
    //         parentNode = next;
    //         if (keyValuePair.first < parentNode->getKey()) 
    //         {
    //             // cout << "parentNode's value is " << parentNode->getKey();
    //             if (parentNode->getLeft() == NULL) 
    //             {
    //                 parentNode->setLeft(insertNode);
    //                 insertNode->setParent(parentNode);
    //                 break;
    //             }
    //             next = parentNode->getLeft();
    //         } else 
    //         {
    //             if (parentNode->getRight() == NULL) 
    //             {
    //                 parentNode->setRight(insertNode);
    //                 insertNode->setParent(parentNode);
    //                 break;
    //             }
    //             next = parentNode->getRight();
    //         }
    //     }
    //     if (parentNode->getBalance() == -1 || parentNode->getBalance() == 1) 
    //     {
    //         parentNode->setBalance(0);

    //     } 
    //     else 
    //     {
    //         if (parentNode->getLeft() == insertNode) 
    //         {
    //             parentNode->setBalance(-1);
    //         } 
    //         else 
    //         {
    //             parentNode->setBalance(1);
    //         }
    //         splay(parentNode);
    //     }

    
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parentNode, AVLNode<Key, Value>* childNode)
{
        if (parentNode == NULL || parentNode->getParent() == NULL) 
        {
            return;
        }

        AVLNode<Key, Value> *grandparentNode = parentNode->getParent();

        if (parentNode == grandparentNode->getLeft()) 
        { 
            grandparentNode->setBalance(grandparentNode->getBalance() -1);


            if (grandparentNode->getBalance() == -1) 
            {
                insertFix(grandparentNode, parentNode);
                return;
            }

            if (grandparentNode->getBalance() == 0) //balanced
            {
                return; 
            }

        
            if (childNode == parentNode->getLeft()) 
            { // zig-zig 
                rotateRight(parentNode);
                parentNode->setBalance(0);
                grandparentNode->setBalance(0);

            } 
            else 
            { // zig-zag
                rotateLeft(childNode);
                rotateRight(childNode);

                if (childNode->getBalance() == -1) 
                {
                    parentNode->setBalance(0);
                    grandparentNode->setBalance(1);

                } 
                else if (childNode->getBalance() == 0) {
                    parentNode->setBalance(0);
                    grandparentNode->setBalance(0);

                } else {
                    parentNode->setBalance(-1);
                    grandparentNode->setBalance(0);
                }
                childNode->setBalance(0);
            }

        } 
        else 
        {
            grandparentNode->setBalance(grandparentNode->getBalance() + 1);

            if (grandparentNode->getBalance() == 1) {
                insertFix(grandparentNode, parentNode);
                return;
            }

            if (grandparentNode->getBalance() == 0) {
                return; //balanced
            }
            
            if (childNode == parentNode->getRight()) 
            { // zig-zig
                rotateLeft(parentNode);
                parentNode->setBalance(0);
                grandparentNode->setBalance(0);

            } 
            else 
            { // zig-zag 
                rotateRight(childNode);
                rotateLeft(childNode);

                if (childNode->getBalance() == 1) 
                {
                    parentNode->setBalance(0);
                    grandparentNode->setBalance(-1);

                } 
                else if (childNode->getBalance() == 0) 
                {
                    parentNode->setBalance(0);
                    grandparentNode->setBalance(0);

                } 
                else 
                {
                    parentNode->setBalance(1);
                    grandparentNode->setBalance(0);
                }
                childNode->setBalance(0);
            }
        }
}



/**
* Erase function for a given key. Finds the node, reattaches pointers, and then balances when finished.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::erase(const Key& key)
{




    //--


// find the node in the BST

    AVLNode<Key, Value> *node = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::internalFind(key));

    if (node == NULL) 
    {
        return;  // the value is not in the BST
    }

    if (node->getLeft() != NULL && node->getRight() != NULL) 
    {
        // find in-order successor
        AVLNode<Key, Value> *successor = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key, Value>::successor(node));
        // swap node with in-order successor
        nodeSwap(node, successor);
        // int temp_value = successor->value;
        // successor->value = node->value;
        // node->value = temp_value;
        // std::swap(node, successor);
    }

    // find childNode node (left or right)
    AVLNode<Key, Value> *childNode = node->getLeft();
    if (node->getRight() != NULL) 
    {
        childNode = node->getRight();
    }

    // update parentNodes (including root)
    AVLNode<Key, Value> *parentNode = node->getParent();
    if (childNode != NULL) {
        childNode->setParent(parentNode);
    }

    int diff;
    if (parentNode == NULL) {
        this->mRoot = childNode;
    } else {
        // If n is not in the root position determine its relationship with its parentNode
        if (node == parentNode->getLeft()) {
            parentNode->setLeft(childNode);
            diff = 1;
        } else {
            parentNode->setRight(childNode);
            diff = -1;
        }
    }

    // delete node
    delete node;

    splay(parentNode);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::eraseFix(AVLNode<Key, Value>* node, int diff)
{
    if (node == NULL) 
    {
        return;
    }

    AVLNode<Key, Value> *parentNode = node->getParent();
    int ndiff = -1;
    if (parentNode != NULL && node == parentNode->getLeft()) 
    {
        ndiff = 1;
    }

    if (node->getBalance() == -1 && diff == -1) 
    { 
        AVLNode<Key, Value> *childNode = node->getLeft();
        if (childNode->getBalance() <= 0) 
        { // zig-zig 
            rotateRight(childNode);

            if (childNode->getBalance() == -1) 
            {
                node->setBalance(0);
                childNode->setBalance(0);
                eraseFix(parentNode, ndiff);

            } 
            else 
            { // balance == 0
                node->setBalance(-1);
                childNode->setBalance(-1);
            }

        } 
        else 
        { // zig-zag case
            AVLNode<Key, Value> *grandchildNode = childNode->getRight();
            rotateLeft(grandchildNode);
            rotateRight(grandchildNode);

            if (grandchildNode->getBalance() == 1) 
            {
                node->setBalance(0);
                childNode->setBalance(-1);

            } 
            else if (grandchildNode->getBalance() == 0) 
            {
                node->setBalance(0);
                childNode->setBalance(0);

            } 
            else 
            {
                node->setBalance(1);
                childNode->setBalance(0);
            }
            grandchildNode->setBalance(0);
            eraseFix(parentNode, ndiff);
        }

    } 
    else if (node->getBalance() == 1 && diff == 1) 
    { 
        AVLNode<Key, Value> *childNode = node->getRight();
        if (childNode->getBalance() >= 0) 
        { // zig-zig case
            rotateLeft(childNode);

            if (childNode->getBalance() == 1) 
            {
                node->setBalance(0);
                childNode->setBalance(0);
                eraseFix(parentNode, ndiff);

            } 
            else 
            { // balance == 0
                node->setBalance(1);
                childNode->setBalance(-1);
            }

        } 
        else 
        { // zig-zag case
            AVLNode<Key, Value> *grandchildNode = childNode->getLeft();
            rotateRight(grandchildNode);
            rotateLeft(grandchildNode);

            if (grandchildNode->getBalance() == -1) 
            {
                node->setBalance(0);
                childNode->setBalance(1);

            } 
            else if (grandchildNode->getBalance() == 0) 
            {
                node->setBalance(0);
                childNode->setBalance(0);

            } 
            else 
            {
                node->setBalance(-1);
                childNode->setBalance(0);
            }
            grandchildNode->setBalance(0);
            eraseFix(parentNode, ndiff);
        }

    } else {
        if (node->getBalance() == 0) {
            node->updateBalance(diff);
            return;

        } else {
            node->setBalance(0);
        }
        eraseFix(parentNode, ndiff);
    }
}
/**
* Rotates n down and to the left
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *n)
{
    rotateHelper(n, true);
    // AVLNode<Key, Value> *q = n->getRight(); //Let Q be n's right childNode.
    // n->setRight(q->getLeft()); //Set n's right childNode to be Q's left childNode.
    // if(q->getLeft() != NULL)
    // {
    //     q->getLeft()->setParent(n); //Set Q's left-childNode's parentNode to n]
    // }
    // q->setLeft(n); //Set Q's left childNode to be n.
    // n->setParent(q); //[Set n's parentNode to Q]
    /*
    Let Q be n's right childNode.
    Set n's right childNode to be Q's left childNode.
    [Set Q's left-childNode's parentNode to n]
    Set Q's left childNode to be n.
    [Set n's parentNode to Q]
    */
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::splay(AVLNode<Key, Value> *n)
{
    while( n->getParent() ) {
      if( !n->getParent()->getParent() ) {
        if( n->getParent()->getLeft() == n ) rotateRight( n->getParent() );
        else rotateLeft( n->getParent() );
      } else if( n->getParent()->getLeft() == n && n->getParent()->getParent()->getLeft() == n->getParent() ) {
        rotateRight( n->getParent()->getParent() );
        rotateRight( n->getParent() );
      } else if( n->getParent()->getRight() == n && n->getParent()->getParent()->getRight() == n->getParent() ) {
        rotateLeft( n->getParent()->getParent() );
        rotateLeft( n->getParent() );
      } else if( n->getParent()->getLeft() == n && n->getParent()->getParent()->getRight() == n->getParent() ) {
        rotateRight( n->getParent() );
        rotateLeft( n->getParent() );
      } else {
        rotateLeft( n->getParent() );
        rotateRight( n->getParent() );
      }
    }
}


template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateHelper(AVLNode<Key, Value> *n, bool isLeft)
{
    AVLNode<Key, Value> *parentNode = n->getParent();
    if(parentNode->getParent() == NULL)
    {
        this->mRoot = n;
    }
    else
    {
        if(parentNode == parentNode->getParent()->getLeft())
        {
            parentNode->getParent()->setLeft(n);
        }
        else
        {
            parentNode->getParent()->setRight(n);
        }
    }
    n->setParent(parentNode->getParent());
    parentNode->setParent(n);

    if(isLeft)
    {
        parentNode->setRight(n->getLeft());
        if(n->getLeft() != NULL)
        {
            n->getLeft()->setParent(parentNode);
        }
        n->setLeft(parentNode);
    }
    else
    {
        parentNode->setLeft(n->getRight());
        if(n->getRight() != NULL)
        {
            n->getRight()->setParent(parentNode);
        }
        n->setRight(parentNode);
    }
}


/**
* Rotates n down and to the right
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *n)
{
    rotateHelper(n, false);
    // AVLNode<Key, Value> *p = n->getLeft();
    // n->setLeft(p->getRight() );
    // p->getRight()->setParent(n);
    // p->setRight(n);
    // n->setParent(p);
    /*
    Let P be Q's left childNode.
    Set Q's left childNode to be P's right childNode.
    [Set P's right-childNode's parentNode to Q]
    Set P's right childNode to be Q.
    [Set Q's parentNode to P]
    */

    
}

/**
 * Given a correct AVL tree, this functions relinks the tree in such a way that
 * the nodes swap positions in the tree.  Balances are also swapped.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    char temp2 = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(temp2);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->mRoot == n1) {
        this->mRoot = n2;
    }
    else if(this->mRoot == n2) {
        this->mRoot = n1;
    }

}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
