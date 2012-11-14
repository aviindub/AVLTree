#ifndef __BST_H__
#define __BST_H__

#include "Node.h"
#include <string>

template <typename T>
class BST {
 private:
  Node<T>* root;
  void traversalPrint(Node<T>* root);
  void postOrderDelete(Node<T>* n);
  void leftSingleRotate(Node<T>** crit);
  void rightSingleRotate(Node<T>** crit);
  void leftRightRotate(Node<T>** crit);
  void rightLeftRotate(Node<T>** crit);
  void recalcBalance(Node<T>** crit);

 public:
  BST<T>();
  ~BST<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
};


#endif
