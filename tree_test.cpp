#include "BST.h"
#include <iostream>
using namespace std;

int main() {
  BST<int>* bst = new BST<int>();
  cout << "constructor passed" << endl;
  bst->insert(5);
  //cout << "1" << endl;
  bst->insert(6);
  //cout << "2" << endl;
  bst->insert(3);
  //cout << "3" << endl;
  bst->insert(2);
  //cout << "4" << endl;
  bst->insert(7);
  bst->insert(8);
  bst->insert(9);
  bst->insert(10);
  bst->insert(11);
  bst->insert(12);
  bst->insert(13);
  bst->insert(14);

  cout << "inserts passed" << endl;

  bst->print();


}
