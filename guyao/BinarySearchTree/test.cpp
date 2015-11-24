#include<iostream>
#include "BST.h"

using namespace std;

int main()
{
  ///this is a test!!!
  BSTree tree1;
  ///BST->insert
  tree1.insertData(1);
  tree1.insertData(2222);
  tree1.insertData(30);
  tree1.insertData(-4);
  tree1.insertData(5);
  cout<<"initialization BST: ";
  tree1.printByInOrderTraversal();
  ///BST->deletion
  tree1.deletion(5);
  cout<<"after delete 5: ";
  tree1.printByInOrderTraversal();
  tree1.deletion(4);
  cout<<"after delete 4: ";
  tree1.printByInOrderTraversal();
  ///BST->extended function:Delete all the elements which are greater than the provided value K
  tree1.deletionRangeUp(29);
  cout<<"after delete numbers that greater than 29: ";
  tree1.printByInOrderTraversal();
  ///BST->extended function:Delete all the elements which are less than the provided value K
  tree1.deletionRangeDown(0);
  cout<<"after delete numbers that less than 0: ";
  tree1.printByInOrderTraversal();
  tree1.insertData(11);
  tree1.insertData(22221);
  tree1.insertData(301);
  tree1.insertData(-41);
  tree1.insertData(51);
  cout<<"initialization BST: ";
  tree1.printByInOrderTraversal();
  ///BST->extended function:Delete all the elements which are within the range K1 ~K2;
  tree1.deletionRange(-50,300);
  cout<<"after delete numbers which are within the range -50~300: ";
  tree1.printByInOrderTraversal();
  return 0;
}
