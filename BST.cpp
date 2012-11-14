#include "BST.h"
#include <iostream>

template <typename T>
BST<T>::BST() {
    root = 0;
}

template <typename T>
BST<T>::~BST() {
    if (root != 0) {
        postOrderDelete(root);
    }    
}

template <typename T>
BST<T>::postOrderDelete(Node<T>* n) {
    if (n->getLeftChild() != 0) {
        postOrderDelete(n->getLeftChild());
    }
    if (n->getRightChild() != 0) {
        postOrderDelete(n->getRightChild());
    }
    delete n;
}

template <typename T>
bool BST<T>::find(T v) {
    Node<T>* temp = new Node<T>(v);
    root = temp;    
    return true;
}

template <typename T>
void BST<T>::insert(T v) {
    Node<T>* temp = new Node<T>(v);
    Node<T>** curr = &root;
    Node<T>** critNode = 0;
    int oldBalance = 0;
    int childBalance = 0;

    //Node<T>*& Node<T>::getLeftChild() 
    while (*curr != 0) {
        if ((*curr)->getBalance() != 0) {
            critNode = curr;
            oldBalance = (*curr)->getBalance();
        }
        if (v < (*curr)->getValue()) {
            curr = &((*curr)->getLeftChild());

        } else if (v > (*curr)->getValue()) {
            curr = &((*curr)->getRightChild());
        }
    }
    *curr = temp;
    recalcBalance(critNode);
    critBalance = (*critNode)->getBalance();
    if (critNode != 0) {
        if (critBalance == 2) {
            childBalance = (*critNode)->getRightChild->getBalance();
            if (childBalance == 1) {
                leftSingleRotate(critNode);
            } else if (childBalance == -1) {
                leftRightRotate(critNode);
            }
        } else if (critBalance == -2) {
            childBalance = (*critNode)->getLeftChild->getBalance();
            if (childBalance == 1) {
                rightLeftRotate(critNode);
            } else if (childBalance == -1) {
                rightSingleRotate(critNode);
            }
        }
    }
}

template <typename T>
void BST<T>::recalcBalance(Node<T>** crit) {

}

template <typename T>
void BST<T>::leftSingleRotate(Node<T>** crit) {
    //crit node +1 -> +2
    //crit node Rchild 0 -> +1
}

template <typename T>
void BST<T>::rightSingleRotate(Node<T>** crit) {
    //crit node -1 -> -2
    //crit node Lchild 0 -> -1
}

template <typename T>
void BST<T>::leftRightRotate(Node<T>** crit) {
    //crit node +1 -> +2
    //crit node Rchild 0 -> -1
}

template <typename T>
void BST<T>::rightLeftRotate(Node<T>** crit) {
    //crit node -1 -> -2
    //crit node Lchild 0 -> +1
}

template <typename T>
Node<T>* BST<T>::findPointer(Node<T>* curr, T v) {
    curV = curr->getValue();
    if (currV == v) {
        return curr;
    } else if (v < currV && curr->getLeftChild() != 0) {
        return findPointer(curr->getLeftChild());
    } else if (v > currV && curr->getRightChild() != 0){
        return findPointer(curr->getRightChild());
    }
}

template <typename T>
Note<T>* BST<T>::findParent(Node<T>* curr, Node<T>* child) { 
    Node<T>* RC = curr->getRightChild();
    Node<T>* LC = curr->getLeftChild();
    if (LC == child || RC == child) {
        return curr;
    } else {
        if (RC != 0) {
            return findParent(RC, child);
        }
        if (LC != 0) {
            return findParent(LC, child);
        }
    }
}

template <typename T>
void BST<T>::remove(T v) {
    
}

template <typename T>
void BST<T>::printTree() {
}


template <typename T>
void BST<T>::print() {
    traversalPrint(root);
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
    if(root != 0) {
        traversalPrint(root->getLeftChild());
        std::cout << root->getValue() << std::endl;
        traversalPrint(root->getRightChild());
    }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
