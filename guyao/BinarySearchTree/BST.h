#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include<iostream>
using namespace std;

class myNode
{
  friend class BSTree;
  private:
    myNode *lchild;
    myNode *rchild;
    myNode *parent;
    int data;

  public:
    myNode()
    {
      lchild=rchild=parent=NULL;
    };

    myNode(int newdata)
    {
      lchild=rchild=parent=NULL;
      data=newdata;
    };


};

class BSTree
{
  private:
    myNode *root;

    myNode *searchHelp(int DData,myNode* nowNode)
    {
      if(nowNode->data==DData) return nowNode;
      else
      {
        if(nowNode->data>DData)
        {
          if(nowNode->lchild) return searchHelp(DData,nowNode->lchild);
          else return NULL;
        }
        else
        {
          if(nowNode->rchild) return searchHelp(DData,nowNode->rchild);
          else return NULL;
        }
      }
    };

    void deletionHelp(int K1,int K2)
    {
      myNode *pointer=root;
      while(pointer)
      {
        if(pointer->data>K2) pointer=pointer->lchild;
        else if(pointer->data<K1) pointer=pointer->rchild;
        else
        {
          if(pointer==root)
          {
            deletion(pointer);
            pointer=root;
          }
          else
          {
            myNode *temp=pointer->parent;
            deletion(pointer);
            pointer=temp;
          }
        }
      }
    };

    void printHelp(myNode *nowNode)
    {
      if(nowNode->lchild) printHelp(nowNode->lchild);
      cout<<nowNode->data<<' ';
      if(nowNode->rchild) printHelp(nowNode->rchild);
    };

  public:
    BSTree()
    {
      root=NULL;
    };

    void insertData(int newdata)
    {
      myNode *pointer=root;
      if(!pointer)
      {
        root=new myNode(newdata);
        return;
      }
      while(true)
      {
        if(newdata<pointer->data)
        {
          if(pointer->lchild) pointer=pointer->lchild;
          else
          {
            pointer->lchild=new myNode(newdata);
            pointer->lchild->parent=pointer;
            break;
          }
        }
        else
        {
          if(pointer->rchild) pointer=pointer->rchild;
          else
          {
            pointer->rchild=new myNode(newdata);
            pointer->rchild->parent=pointer;
            break;
          }
        }
      }
    };

    myNode * searchData(int DData)
    {
      return searchHelp(DData,root);
    };

    myNode *findMax(myNode *nowNode)
    {
      while(nowNode->rchild) nowNode=nowNode->rchild;
      return nowNode;
    };

    myNode *findMin(myNode *nowNode)
    {
      while(nowNode->lchild) nowNode=nowNode->lchild;
      return nowNode;
    };

    void deletion(int DData)
    {
      myNode *DNode=searchData(DData);
      if(DNode)
      {
        if(DNode->lchild&&DNode->rchild)
        {
          myNode *temp=findMin(DNode->rchild);
          DNode->data=temp->data;
          if(temp->parent->lchild==temp)
          {
            temp->parent->lchild=temp->rchild;
            if(temp->rchild) temp->rchild->parent=temp->parent;
          }
          else
          {
            temp->parent->rchild=temp->rchild;
            if(temp->rchild) temp->rchild->parent=temp->parent;
          }
          delete temp;
        }
        else
        {
          if(DNode==root)
          {
            if(root->lchild||root->rchild)
            {
              if(root->lchild) root=root->lchild;
              else root=root->rchild;
              root->parent=NULL;
            }
            else root=NULL;
          }
          else
          {
            if(DNode->parent->lchild==DNode)
            {
              if(DNode->lchild) {DNode->parent->lchild=DNode->lchild;DNode->lchild->parent=DNode->parent;}
              else if(DNode->rchild) {DNode->parent->lchild=DNode->rchild;DNode->rchild->parent=DNode->parent;}
              else DNode->parent->lchild=NULL;
            }
            else
            {
              if(DNode->lchild) {DNode->parent->rchild=DNode->lchild;DNode->lchild->parent=DNode->parent;}
              else if(DNode->rchild) {DNode->parent->rchild=DNode->rchild;DNode->rchild->parent=DNode->parent;}
              else DNode->parent->rchild=NULL;
            }
          }
          delete DNode;
        }
      }
    };

    void deletion(myNode *DNode)
    {
      if(DNode)
      {
        if(DNode->lchild&&DNode->rchild)
        {
          myNode *temp=findMin(DNode->rchild);
          DNode->data=temp->data;
          if(temp->parent->lchild==temp)
          {
            temp->parent->lchild=temp->rchild;
            if(temp->rchild) temp->rchild->parent=temp->parent;
          }
          else
          {
            temp->parent->rchild=temp->rchild;
            if(temp->rchild) temp->rchild->parent=temp->parent;
          }
          delete temp;
        }
        else
        {
          if(DNode==root)
          {
            if(root->lchild||root->rchild)
            {
              if(root->lchild) root=root->lchild;
              else root=root->rchild;
              root->parent=NULL;
            }
            else root=NULL;
          }
          else
          {
            if(DNode->parent->lchild==DNode)
            {
              if(DNode->lchild) {DNode->parent->lchild=DNode->lchild;DNode->lchild->parent=DNode->parent;}
              else if(DNode->rchild) {DNode->parent->lchild=DNode->rchild;DNode->rchild->parent=DNode->parent;}
              else DNode->parent->lchild=NULL;
            }
            else
            {
              if(DNode->lchild) {DNode->parent->rchild=DNode->lchild;DNode->lchild->parent=DNode->parent;}
              else if(DNode->rchild) {DNode->parent->rchild=DNode->rchild;DNode->rchild->parent=DNode->parent;}
              else DNode->parent->rchild=NULL;
            }
          }
          delete DNode;
        }
      }
    };

    void printByInOrderTraversal()
    {
      if(root) printHelp(root);
      cout<<endl;
    };

    void deletionRangeUp(int K1)
    {
      deletionHelp(K1+1,2147483646);
    };

    void deletionRangeDown(int K2)
    {
      deletionHelp(-2147483647,K2-1);
    };

    void deletionRange(int K1,int K2)
    {
      deletionHelp(K1,K2);
    };


};



#endif // BST_H_INCLUDED
