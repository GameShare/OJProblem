#include <iostream>

using namespace std;

class binomialTree
{
  friend binomialTree *mergeBTree(binomialTree *Tree1,binomialTree *Tree2);
  private:
    binomialTree **Treelist;
    int data;
    int level;

  public:
    binomialTree(int newdata)
    {
      Treelist=NULL;
      data=newdata;
      level=0;
    };

    int getLevel() {return level;};
    void setLevel(int newLevel) {level=newLevel;};
    int getRoot() {return data;};
    void addTree(binomialTree *other)
    {
      level++;
      binomialTree **temp=new binomialTree *[level];
      for(int i=0;i<level-1;i++)
      {
        temp[i]=Treelist[i];
      }
      if(Treelist) delete [] Treelist;
      Treelist=temp;
      Treelist[level-1]=other;
    };

    binomialTree **getList()
    {
      return Treelist;
    };


    ~binomialTree() {delete [] Treelist;};


};

binomialTree *mergeBTree(binomialTree *Tree1,binomialTree *Tree2)
{
  if(Tree1->getRoot()>Tree2->getRoot())
  {
    Tree2->addTree(Tree1);
    return Tree2;
  }
  else
  {
    Tree1->addTree(Tree2);
    return Tree1;
  }
}

class binomialHeap
{
  private:
    binomialTree **Treelist;

  public:
    binomialHeap()
    {
      Treelist=new binomialTree*[30];
      for(int i=0;i<30;i++) Treelist[i]=NULL;
    };

    binomialHeap(binomialTree *Tree)
    {
      Treelist=new binomialTree*[30];
      for(int i=0;i<30;i++) Treelist[i]=NULL;
      for(int i=0;i<Tree->getLevel();i++)
      {
        Treelist[i]=(Tree->getList())[i];
      }
    };


    void heapMerge(binomialHeap *other)
    {
      binomialTree **temp=other->getList();
      for(int i=0;i<30;i++)
      {
        if(temp[i]&&Treelist[i])
        {
          int j=i+1;
          binomialTree *tempTree=mergeBTree(temp[i],Treelist[i]);
          Treelist[i]=NULL;
          for(;j<30;j++)
          {
            if(Treelist[j])
            {
              tempTree=mergeBTree(Treelist[j],tempTree);
              Treelist[j]=NULL;
            }
            else
            {
              Treelist[j]=tempTree;
              break;
            }
          }
        }
        else
        {
          if(temp[i]&&!Treelist[i])
          {
            Treelist[i]=temp[i];
          }
        }
      }
    };

    binomialHeap(int num)
    {
      Treelist=new binomialTree*[1];
      Treelist[0]=new binomialTree(num);
    };

    void heapMergeSingle(binomialHeap *singleHeap)
    {
      binomialTree **temp=singleHeap->getList();
      if(temp[0]&&Treelist[0])
      {
        binomialTree *tempTree=mergeBTree(temp[0],Treelist[0]);
        Treelist[0]=NULL;
        for(int j=1;j<30;j++)
        {
          if(Treelist[j])
          {
            tempTree=mergeBTree(Treelist[j],tempTree);
            Treelist[j]=NULL;
          }
          else
          {
            Treelist[j]=tempTree;
            break;
          }
        }
      }
      else
      {
        if(temp[0]&&!Treelist[0])
        {
          Treelist[0]=temp[0];
        }
      }
    };

    void insertNum(int num)
    {
      binomialHeap *temp=new binomialHeap(num);
      heapMergeSingle(temp);
      delete temp;
    };

    int deleteMin()
    {
      int level=0;
      int minNum;
      int tempCount=0;
      for(int i=0;i<30;i++)
      {
        if(Treelist[i])
        {
          if(tempCount==0)
          {
            minNum=Treelist[i]->getRoot();
            tempCount++;
            level=i;
          }
          else
          {
            if(Treelist[i]->getRoot()<minNum)
            {
              minNum=Treelist[i]->getRoot();
              level=i;
            }
          }
        }
      }
      binomialHeap *temp=new binomialHeap(Treelist[level]);
      delete Treelist[level];
      Treelist[level]=NULL;
      heapMerge(temp);
      delete temp;
      return minNum;
    };

    int getMin()
    {
      int minNum;
      int tempCount=0;
      for(int i=0;i<30;i++)
      {
        if(Treelist[i])
        {
          if(tempCount==0)
          {
            minNum=Treelist[i]->getRoot();
            tempCount++;
          }
          else
          {
            if(Treelist[i]->getRoot()<minNum)
            {
              minNum=Treelist[i]->getRoot();
            }
          }
        }
      }
      return minNum;
    };




    binomialTree **getList()
    {
      return Treelist;
    };

    ~binomialHeap() {delete [] Treelist;};

};





int main()
{
  int totalIns=0;
  char ins[10];
  int operand=0;
  binomialHeap BHeap;
  cin>>totalIns;
  for(int i=0;i<totalIns;i++)
  {
    cin>>ins;
    if(ins[0]=='i')
    {
      cin>>operand;
      BHeap.insertNum(operand);
      continue;
    }
    if(ins[0]=='d')
    {
      BHeap.deleteMin();
      continue;
    }
    if(ins[0]=='m')
    {
      cout<<BHeap.getMin()<<endl;
      continue;
    }
  }




  return 0;
}
