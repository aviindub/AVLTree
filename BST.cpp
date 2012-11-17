#include "BST.h"
#include <iostream>
#include <stack>

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
    if (critNode != 0) {
        critBalance = balance(*critNode); 
        //cout << "passed balance calc" << endl;
        if (critBalance == 2) {
            childBalance = balance((*critNode)->getRightChild());
            if (childBalance == 1) {
                leftSingleRotate(critNode);
            } else if (childBalance == -1) {
                rightLeftRotate(critNode);
            }
        } else if (critBalance == -2) {
            childBalance = balance((*critNode)->getLeftChild());
            if (childBalance == 1) {
                leftRightRotate(critNode);
            } else if (childBalance == -1) {
                rightSingleRotate(critNode);
            }
        }
        recalcBalance(*critNode);
    } else {
        recalcBalance(root);
    }
}

template <typename T>
void BST<T>::recalcBalance(Node<T>* curr) {
    //cout << "recalc balance" << endl;
    if (curr->getLeftChild() != 0) {
        recalcBalance(curr->getLeftChild());
    }
    if (curr->getRightChild() != 0) {
        recalcBalance(curr->getRightChild());
    }
    curr->setBalance(balance(curr));
}

template <typename T>
int BST<T>::leftHeight(Node<T>* curr) {
    //cout << "left height" << endl;
    if (curr->getLeftChild() == 0) {
        return 0;
    } else {
        return 1 + height(curr->getLeftChild());
    }
}

template <typename T>
int BST<T>::rightHeight(Node<T>* curr) {
    //cout << "right height" << endl;
    if (curr->getRightChild() == 0) {
        return 0;
    } else {
        return 1 + height(curr->getRightChild());
    }
}

template <typename T>
int BST<T>::height(Node<T>* curr) {
    //cout << "height" << endl;
    int lHeight = leftHeight(curr);
    int rHeight = rightHeight(curr);
    if (lHeight > rHeight) {
        return lHeight;
    } else {
        return rHeight;
    }
}

template <typename T>
int BST<T>::balance(Node<T>* curr) {
    //cout << "balance" << endl;
    return rightHeight(curr) - leftHeight(curr);
}

template <typename T>
void BST<T>::leftSingleRotate(Node<T>** curr) {
    //crit node +1 -> +2
    //crit node Rchild 0 -> +1
    cout << "rotating L" << endl;
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
    cout << "rotating R" << endl;
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
    cout << "rotating RL" << endl;
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
    cout << "rotating LR" << endl;
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
    stack< Node<T>* > path;
    Node<T>** curr = &root;
    while (*curr != 0 && (*curr)->getValue() != v) {
        path.push(*curr);
        if (v < (*curr)->getValue()) { 
            curr = &((*curr)->getLeftChild());
        } else {
            curr = &((*curr)->getRightChild());
        }
    }
    if (*curr == 0) { return;}
    Node<T>* toDelete = *curr;
    if ((*curr)->getRightChild() == 0) {
        *curr = (*curr)->getLeftChild();
    } else if ((*curr)->getLeftChild() == 0) {
        *curr = (*curr)->getRightChild();
    } else {
        Node<T>** successor = &((*curr)->getRightChild());
        path.push(*successor);
        while ((*successor)->getLeftChild() != 0) {
            successor = &((*successor)->getLeftChild());
            path.push(*successor);
        }
        *curr = *successor;
        *successor = (*successor)->getRightChild();
        (*curr)->setRightChild(*(toDelete->getRightChild()));
        (*curr)->setLeftChild(*(toDelete->getLeftChild()));
    }
    delete toDelete;

    /* now rebalance */
    //pop one off to get the parent of the removed node to the top
    path.pop();
    recalcBalance(path.top());
    int bal = path.top()->getBalance();
    int childBalance;
    while (bal != 1 && bal != -1 && !path.empty()) {
        if (bal == 2) {
            childBalance = balance(path.top()->getRightChild());
            if (childBalance == 1) {
                leftSingleRotate(&(path.top()));
            } else if (childBalance == -1) {
                rightLeftRotate(&(path.top()));
            }
        } else if (bal == -2) {
            childBalance = balance(path.top()->getLeftChild());
            if (childBalance == 1) {
                leftRightRotate(&(path.top()));
            } else if (childBalance == -1) {
                rightSingleRotate(&(path.top()));
            }
        }
        recalcBalance(path.top());
        path.pop();
        if (!path.empty()) {
            recalcBalance(path.top());
            bal = path.top()->getBalance();
        }
    }
}

/*
template <typename T>1
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
        cout << "v: " << root->getValue() <<
            " b: " << root->getBalance() << endl;
        traversalPrint(root->getRightChild());
    }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
