#include<iostream>
#include<fstream>
#include<cstdio>

using namespace std;


class myNode
{

  friend class myListL;
  friend class myStackL;
  private:
    int data;
    myNode *next;
    myNode *lchild;
    myNode *rchild;

  public:
    myNode()
    {
      next=NULL;
      lchild=NULL;
      rchild=NULL;
    };

    myNode(int newdata)
    {
      data=newdata;
      next=NULL;
    };

    myNode(int newdata,int newnext)
    {
      data=newdata;
      next=newnext;
    };
};

class myListA
{
  private:
    int *data;
    int maxSize;
    int rear;
  public:
    myListA(int n)
    {
      rear=-1;
      maxSize=n;
      data=new int [n];
    };

    void addNum(int posi,int num)
    {
      rear++;
      for(int i=rear;i>posi;i--)
      {
        data[i]=data[i-1];
      }
      data[posi]=num;
    };

    int getNum(int posi)
    {
      return data[posi];
    };

    void deletion(int posi)
    {
      for(int i=posi;i<rear;i++)
      {
        data[i]=data[i+1];
      }
      rear--;
    };

    ~myListA()
    {
      delete [] data;
    };
};



class myListL
{
  private:
    myNode *head;
    myNode *rear;
    myNode *fence;

  public:
    myListL()
    {
      rear=fence=head=new myNode;
    };

    void addNum(int posi,int n)
    {
      fence=head;
      for(int i=0;i<posi;i++) fence=fence->next;
      fence->next=new myNode(n,fence->next);
      if(fence==rear) rear=fence->next;
    };

    int getNum(int posi)
    {
      fence=head;
      for(int i=0;i<posi;i++) fence=fence->next;
      return fence->next->data;
    };

    void deletion(int posi)
    {
      fence=head;
      for(int i=0;i<posi;i++) fence=fence->next;
      myNode* temp=fence->next;
      fence->next=temp->next;
      if(temp==rear) rear=fence;
      delete temp;
    };

    ///更常用的是append 或 插入头部，为O(1) 操作
    ///关键是在各个操作后更新rear

    ~myListL()
    {
      myNode* temp;
      while(head)
      {
        temp=head;
        head=head->next;
        delete temp;
      }
    };
};

class myStackA
{
  private:
    int *data;
    int top;
    int maxSize;

  public:
    myStackA(int n)
    {
      maxSize=n;
      top=-1;
      data=new int [n];
    };

    void push(int n)
    {
      top++;
      data[top]=n;
    };

    int pop()
    {
      return data[top--];
    };

    bool isEmpty()
    {
      return top==-1;
    };

    int getTop()
    {
      return data[top];
    };


    ~myStackA()
    {
      delete [] data;
    };

};

class myStackL
{
  private:
    myNode *top;


  public:
    myStackL()
    {
      top=NULL;
    };

    void push(int n)
    {
      top=new myNode(n,top);
    };

    int pop()
    {
      myNode *temp=top;
      top=top->next;
      int tempdata=temp->data;
      delete temp;
      return tempdata;
    };

    int getTop()
    {
      return top->data;
    };

    bool isEmpty()
    {
      return top==NULL;
    };

    ~myStackL()
    {
      myNode *temp;
      while(head)
      {
        temp=head;
        head=head->next;
        delete temp;
      }
    };
};

template<class T>
class myQueue
{
  private:
    T *data;
    int head;
    int rear;
    int maxSize;

  public:
    myQueue(int n)
    {
      maxSize=n;
      data=new T [n+1];
      head=1;
      rear=0;
    };

    void enQueue(T n)
    {
      if((rear+2)%maxSize==head) return;
      rear=(rear+1)%maxSize;
      data[rear]=n;
    };

    T deQueue()
    {
      ///if((rear+1)%maxSize==head) return;
      T temp=data[head];
      head=(head+1)%maxSize;
      return temp;
    };

    bool isEmpty()
    {
      return (rear+1)%maxSize==head;
    };

    T getTop()
    {
      return data[head];
    };

    ~myQueue()
    {
      delete [] data;
    };
};

class myTree
{
  private:
    myNode *root;

    void clearHelp(myNode *nowposi)
    {
      if(nowposi->lchild) clearHelp(nowposi->lchild);
      if(nowposi->rchild) clearHelp(nowposi->rchild);
      delete nowposi;

    };

    void POTHelp(myNode *posi)
    {
      cout<<posi->data<<endl;
      if(posi->lchild) POTHelp(posi->lchild);
      if(posi->rchild) POTHelp(posi->rchild);
    };

    void IOTHelp(myNode *posi)
    {
      if(posi->lchild) IOTHelp(posi->lchild);
      cout<<posi->data<<endl;
      if(posi->rchild) IOTHelp(posi->rchild);
    };

  public:
    myTree()
    {
      root=NULL;
    };

    myTree(myNode *rt)
    {
      root=rt;
    };

    void PreOrderTraversal()
    {
      if(root) POTHelp(root);
    };

    void InOrderTraversal()
    {
      if(root) IOTHelp(root);
    };

    ///void PostOrderTraversal();

    void LevelOrderTraversal()
    {
      myQueue<myNode *> data(10000);
      data.enQueue(root);
      myNode *temp;
      while(!data.isEmpty())
      {
        temp=data.deQueue();
        cout<<temp->data;
        if(temp->lchild) data.enQueue(temp->lchild);
        if(temp->rchild) data.enQueue(temp->rchild);
      }
    };


    ~myTree()
    {
      if(root) clearHelp(root);
    };
};

class myHeap
{
  private:
    int *data;
    int maxSize;

    void mySwap(int &a.int &b)
    {
      int temp;
      temp=a;
      a=b;
      b=temp;
    };
    void siftdown(int posi)
    {
      int lchild;
      int rchild;
      while(true)
      {
        lchild=posi*2+1;
        rchild=posi*2+2;
        if(rchild<maxSize)
        {
          if(data[lchild]<data[rchild])
          {
            if(data[posi]>data[lchild])
            {
              mySwap(data[posi],data[lchild]);
              posi=lchild;
            }
            else return;
          }
          else
          {
            if(data[posi]>data[rchild])
            {
              mySwap(data[posi],data[rchild]);
              posi=rchild;
            }
            else return;
          }
        }
        else if(lchild>=maxSize) return;
        else
        {
          if(data[posi]>data[lchild])
          {
            mySwap(data[posi,data[lchild]);
            posi=lchild;
          }
          else return;
        }
      }
    };

    void siftup(int posi)
    {
      int parent;
      while(true)
      {
        if(posi==0) return;
        parent=(posi-1)/2;
        if(data[parent]>data[posi])
        {
          mySwap(data[parent],data[posi]);
          posi=parent;
        }
        else return;
      }
    };

  public:
    myHeap(int n,int *newdata)
    {
      maxSize=n;
      data=newdata;
      for(int i=n/2-1;i>=0;i--)
      {
        siftdown(i);
      }
    };

    ~myHeap()
    {
      delete [] data;
    };
};

void qsort(int *data,int low,int high)
{
  if(low>=high) return;
  int first=low;
  int last=high;
  int mid=data[low];
  while(first<last)
  {
    while(first<last&&data[last]>=mid) last--;
    data[first]=data[last];
    while(first<last&&data[last]<mid) first++;
    data[last]=data[first];
  }
  data[first]=mid;
  qsort(data,low,first-1);
  qsort(data,first+1,high);
}

class myHash
{
  private:
    int *data;
    int maxSize;
    int *status;

    int h(int value)
    {
      return value%maxSize;
    };


    int findPrime(int n)
    {
      for(int i=n;n>=3;n--)
      {
        bool flag=true;
        for(int j=2;j<n/2;j++)
        {
          if(i%j==0)
          {
            flag=false;
            break;
          }
        }
        if(flag)
        {
          return i;
        }
      }
    };

  public:
    myHash(int n)
    {
      maxSize=findPrime(n);
      data=new int [maxSize];
      status=new int [maxSize];
      for(int i=0;i<maxSize;i++)
      {
        ///0=empty 1=full 2=tombstone
        status[i]=0;
      }
    };



    void addNum(int n)
    {
      int initposi=h(n);
      int posi=initposi;
      while(status[posi]!=0)
      {
        posi=(posi+1)%maxSize;
        if(initposi==posi) return;
      }
      data[posi]=n;
      status[posi]=1;
    };

    bool searchNum(int n)
    {
      int initposi=h(n);
      int posi=initposi;
      while(status[posi]>=1)
      {
        if(data[posi]==n&&status[posi]==1) return true;
        posi=(posi+1)%maxSize;
        if(posi==initposi) return false;
      }
      return false;
    };

    void deleteNum(int n)
    {
      int initposi=h(n);
      int posi=initposi;
      while(status[posi]>=1)
      {
        if(data[posi]==n&&status[posi]==1)
        {
          status[posi]=2;
          return;
        }
        posi=(posi+1)%maxSize;
        if(posi==initposi) return;
      }
    };


    ~myHash()
    {
      delete [] data;
    };

};

class mySet
{
  private:
    int *data;
    int maxSize;

  public:
    mySet(int n)
    {
      maxSize=n;
      data=new int [n];
      for(int i=0;i<n;i++)
      {
        data[i]=-1;
      }
    };

    int findRoot(int posi)
    {
      if(data[posi]<0) return posi;
      else
      {
        return data[posi]=findRoot(data[posi]);
      }
    };

    void unionSet(int a,int b)
    {
      int roota=findRoot(a);
      int rootb=findRoot(b);
      if(roota!=rootb)
      {
        if(data[roota]<data[rootb])
        {
          data[roota]+=data[rootb];
          data[rootb]=roota;
        }
        else
        {
          data[rootb]+=data[roota];
          data[roota]=rootb;
        }
      }
    };

    ~mySet()
    {
      delete [] data;
    };
};

class myGraph
{
  private:
    myNode **vertex;
    int *marks;
    int vnum;

  public:
    myGraph(int n)
    {
      vnum=n;
      vertex=new myNode *[n];
      marks =new int [n];
      for(int i=0;i<n;i++)
      {
        vertex[i]=NULL;
        marks[i]=0;
      }
    };

    void addEdge(int a,int b)
    {
      myNode *nowposi=vertex[a];
      if(!nowposi) vertex[a]=new myNode(b);
      while(nowposi->next) nowposi=nowposi->next;
      nowposi->next=new myNode(b);
    };





    ~myGraph()
    {
      myNode *nowposi;
      myNode *temp;
      for(int i=0;i<vnum;i++)
      {
        nowposi=vertex[i];
        while(nowposi)
        {
          temp=nowposi;
          nowposi=nowposi->next;
          delete temp;
        }
      }
      delete [] marks;
      delete [] vertex;
    };
};


class myBST
{
  private:
    myNode *root;
    void addNumHelp(int n,myNode *nowposi)
    {
      if(!nowposi)
      {
        nowposi=new myNode(n);
      }
      else if(nowposi->data>n) addNumHelp(n,nowposi->lchild);
      else addNumHelp(n,nowposi->rchild);
    };

    void searchNumHelp(int n,myNode *nowposi)
    {

    };


  public:
    myBST()
    {
      root=NULL;
    };

    void addNum(int n)
    {
      addNumHelp(n,root);
    };

    void searchNum(int n)
    {

    };
};





int main()
{
  ifstream fin("data.in");
  ofstream fout("data.out");



  fin.close();
  fout.close();
  return 0;
}
