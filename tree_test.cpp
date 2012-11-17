#include "BST.h"
#include <iostream>
using namespace std;

int main() {

  BST<int>* bst = new BST<int>();
  
  bst->insert(5);
  bst->insert(4);
  bst->insert(3);
  bst->insert(2);
  bst->print();
  delete bst;
  
  bst = new BST<int>();
  cout << "constructor passed" << endl;
  bst->insert(5);
  cout << "1" << endl;
  bst->insert(20);
  cout << "2" << endl;
  bst->insert(19);
  cout << "3" << endl;
  bst->insert(2);
  cout << "4" << endl;
  //bst->insert(7);
  //bst->insert(8);
  //bst->insert(9);
  //bst->insert(10);
  bst->insert(4);
  bst->insert(11);
  bst->insert(13);
  cout << "5" << endl;
  bst->insert(14);
  bst->insert(40);
  bst->insert(12);
  cout << "6" << endl;
  bst -> print();
  bst->insert(12);
  cout << "inserts passed" << endl;

  bst->print();
  
  cout << "deleting" << endl;

  bst->remove(9);
  bst->remove(3);
  bst->remove(8);
  bst->print();

  
  delete bst;

  bst = new BST<int>();
  bst->insert(4);
  bst->insert(9);
  bst->insert(6);
  delete bst;
}
