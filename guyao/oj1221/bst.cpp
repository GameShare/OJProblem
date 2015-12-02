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

    void clearNode(myNode *rt)
    {
      if(rt->lchild) clearNode(rt->lchild);
      if(rt->rchild) clearNode(rt->rchild);
      delete rt;
    };

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

    void printHelp(myNode *nowNode)
    {
      if(nowNode->lchild) printHelp(nowNode->lchild);
      cout<<nowNode->data<<' ';
      if(nowNode->rchild) printHelp(nowNode->rchild);
    };

    bool findIthHelp(int rk, myNode *nowNode, int &level, int &result)
    {
      if(nowNode->lchild) if(findIthHelp(rk,nowNode->lchild,level,result)) return true;
      level++;
      if(rk==level) {result=nowNode->data;return true;}
      if(nowNode->rchild) if(findIthHelp(rk,nowNode->rchild,level,result)) return true;
      return false;
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
      if(!root) return;
      while(root->data>K1)
      {
        if(root->rchild) clearNode(root->rchild);
        myNode *temp=root;
        root=root->lchild;
        delete temp;
        if(root) root->parent=NULL;
        else return;
      }
      myNode *pointer=root->rchild;
      while(pointer)
      {
        if(pointer->data<=K1) pointer=pointer->rchild;
        else
        {
          if(pointer->rchild) clearNode(pointer->rchild);
          pointer->rchild=NULL;
          myNode *temp=pointer;
          pointer=pointer->parent;
          if(pointer->lchild==temp)
          {
            deletion(temp);
            pointer=pointer->lchild;
          }
          else
          {
            deletion(temp);
            pointer=pointer->rchild;
          }
        }
      }
    };

    void deletionRangeDown(int K2)
    {
      if(!root) return;
      while(root->data<K2)
      {
        if(root->lchild) clearNode(root->lchild);
        myNode *temp=root;
        root=root->rchild;
        delete temp;
        if(root) root->parent=NULL;
        else return;
      }
      myNode *pointer=root->lchild;
      while(pointer)
      {
        if(pointer->data>=K2) pointer=pointer->lchild;
        else
        {
          if(pointer->lchild) clearNode(pointer->lchild);
          pointer->lchild=NULL;
          myNode *temp=pointer;
          pointer=pointer->parent;
          if(pointer->lchild==temp)
          {
            deletion(temp);
            pointer=pointer->lchild;
          }
          else
          {
            deletion(temp);
            pointer=pointer->rchild;
          }
        }
      }
    };

    void deletionRange(int K1,int K2)
    {
      if(!root) return;
      if(K1>=K2) return;
      myNode *Mpointer=root;
      while(Mpointer->data<=K1||Mpointer->data>=K2)
      {
        if(Mpointer->data<=K1)
        {
          Mpointer=Mpointer->rchild;
          if(!Mpointer) return;
          continue;
        }
        if(Mpointer->data>=K2)
        {
          Mpointer=Mpointer->lchild;
          if(!Mpointer) return;
          continue;
        }
      }
      myNode *pointer=Mpointer->rchild;
      while(pointer)
      {
        if(pointer->data>=K2) pointer=pointer->lchild;
        else
        {
          if(pointer->lchild) clearNode(pointer->lchild);
          pointer->lchild=NULL;
          myNode *temp=pointer;
          pointer=pointer->parent;
          if(pointer->lchild==temp)
          {
            deletion(temp);
            pointer=pointer->lchild;
          }
          else
          {
            deletion(temp);
            pointer=pointer->rchild;
          }
        }
      }
      pointer=Mpointer->lchild;
      while(pointer)
      {
        if(pointer->data<=K1) pointer=pointer->rchild;
        else
        {
          if(pointer->rchild) clearNode(pointer->rchild);
          pointer->rchild=NULL;
          myNode *temp=pointer;
          pointer=pointer->parent;
          if(pointer->lchild==temp)
          {
            deletion(temp);
            pointer=pointer->lchild;
          }
          else
          {
            deletion(temp);
            pointer=pointer->rchild;
          }
        }
      }
      deletion(Mpointer);
    };

    void findIth(int rankith)
    {
      int level=0;
      int result=0;
      if(findIthHelp(rankith,root,level,result)) cout<<result<<endl;
      else cout<<'N'<<endl;
    };


};




int main()
{
  int N=0;
  cin>>N;
  char ins[20];
  int a,b;
  BSTree tree;
  for(int i=0;i<N;i++)
  {
    cin>>ins;
    if(ins[0]=='i')
    {
      cin>>a;
      tree.insertData(a);
      //tree.printByInOrderTraversal();
    }
    if(ins[0]=='d')
    {
      if(ins[6]=='\0')
      {
        cin>>a;
        tree.deletion(a);
        //tree.printByInOrderTraversal();
      }
      else
      {
        if(ins[7]=='l')
        {
          cin>>a;
          tree.deletionRangeDown(a);
          //tree.printByInOrderTraversal();
        }
        if(ins[7]=='g')
        {
          cin>>a;
          tree.deletionRangeUp(a);
          //tree.printByInOrderTraversal();
        }
        if(ins[7]=='i')
        {
          cin>>a>>b;
          tree.deletionRange(a,b);
          //tree.printByInOrderTraversal();
        }
      }
    }
    if(ins[0]=='f')
    {
      if(ins[4]=='\0')
      {
        cin>>a;
        if(tree.searchData(a)) cout<<'Y'<<endl;
        else cout<<'N'<<endl;
        //tree.printByInOrderTraversal();
      }
      else
      {
        if(ins[5]=='i')
        {
          cin>>a;
          tree.findIth(a);
          //tree.printByInOrderTraversal();
        }
      }
    }
  }
  return 0;
}
