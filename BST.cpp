#include "BST.h"
#include <iostream>
using namespace std;

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
void BST<T>::postOrderDelete(Node<T>* n) {
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
    int critBalance, childBalance;

    //Node<T>*& Node<T>::getLeftChild() 
    while (*curr != 0) {
        if ((*curr)->getBalance() != 0) {
            critNode = curr;
        }
        if (v < (*curr)->getValue()) {
            curr = &((*curr)->getLeftChild());
        } else if (v > (*curr)->getValue()) {
            curr = &((*curr)->getRightChild());
        }
    }
    *curr = temp;
    //cout << "passed insert, going to balance" << endl;
    critBalance = recalcBalance(critNode);
    if (critNode != 0) {
        if (critBalance == 2) {
            childBalance = (*critNode)->getRightChild()->getBalance();
            if (childBalance == 1) {
                leftSingleRotate(critNode);
            } else if (childBalance == -1) {
                rightLeftRotate(critNode);
            }
        } else if (critBalance == -2) {
            childBalance = (*critNode)->getLeftChild()->getBalance();
            if (childBalance == 1) {
                leftRightRotate(critNode);
            } else if (childBalance == -1) {
                rightSingleRotate(critNode);
            }
        }
    }
    recalcBalance(critNode);
}

template <typename T>
int BST<T>::recalcBalance(Node<T>** curr) {
    if ((*curr) == 0) {
        return 1;
    }
    (*curr)->setBalance(
        recalcBalance(&(*curr)->getLeftChild()) + 
        (-1 * recalcBalance(&(*curr)->getRightChild()))
    );
    return (*curr)->getBalance();
}

template <typename T>
void BST<T>::leftSingleRotate(Node<T>** curr) {
    //crit node +1 -> +2
    //crit node Rchild 0 -> +1
    Node<T>* a = *curr;
    Node<T>* c = (*curr)->getRightChild();
    a->setRightChild(*(c->getLeftChild()));
    c->setLeftChild(*a);
    *curr = c;
}

template <typename T>
void BST<T>::rightSingleRotate(Node<T>** curr) {
    //crit node -1 -> -2
    //crit node Lchild 0 -> -1 
    Node<T>* a = *curr;
    Node<T>* c = (*curr)->getLeftChild();
    a->setLeftChild(*(c->getRightChild()));
    c->setRightChild(*a);
    *curr = c;
}

template <typename T>
void BST<T>::rightLeftRotate(Node<T>** curr) {
    //crit node +1 -> +2
    //crit node Rchild 0 -> -1
    Node<T>* a = *curr;
    Node<T>* c = a->getRightChild();
    Node<T>* b = c->getLeftChild();
    c->setLeftChild(*(b->getRightChild()));
    a->setRightChild(*(b->getLeftChild()));
    b->setLeftChild(*a);
    b->setRightChild(*c);
    *curr = b;
}

template <typename T>
void BST<T>::leftRightRotate(Node<T>** curr) {
    //crit node -1 -> -2
    //crit node Lchild 0 -> +1
    Node<T>* a = *curr;
    Node<T>* c = a->getLeftChild();
    Node<T>* b = c->getRightChild();
    c->setRightChild(*(b->getLeftChild()));
    a->setLeftChild(*(b->getRightChild()));
    b->setRightChild(*a);
    b->setLeftChild(*c);
    *curr = b;
}

template <typename T>
void BST<T>::remove(T v) {
    /*
    do the standard BST remove
    recalcBalance(node that is now in position of removed node)
    rotate if needed
    recalcBalance(again)
    */
    Node<T>** curr = &root;
    while (*curr != 0 && (*curr)->getValue() != v) {
        if (v < (*curr)->getValue()) {
            curr = &((*curr)->getLeftChild());
        } else {
            curr = &((*curr)->getRightChild());
        }
    }
    if (*curr == 0) { return;}
    Node<T>* toDelete = 0;
    if ((*curr)->getRightChild() == 0) {
        toDelete = *curr;
        *curr = (*curr)->getLeftChild();
    } else if ((*curr)->getLeftChild() == 0) {
        toDelete = *curr;
        *curr = (*curr)->getRightChild();
    } else {
        Node<T>** successor = &((*curr)->getRightChild());
        while ((*successor)->getLeftChild() != 0) {
            successor = &((*successor)->getLeftChild());
        }
        toDelete = *curr;
        *curr = *successor;
        *successor = (*successor)->getRightChild();
        (*curr)->setRightChild(*((*curr)->getRightChild()));
        (*curr)->setLeftChild(*((*curr)->getLeftChild())); 
    }
    if (toDelete != 0) {
        delete toDelete;
    }
}

/*
template <typename T>
void BST<T>::printTree() {
}
*/

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
