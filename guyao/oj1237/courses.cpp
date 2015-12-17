#include<iostream>

using namespace std;

class myQueue
{
  private:
    int *data;
    int head;
    int rear;
    int maxSize;

  public:
    myQueue(int n)
    {
      data=new int [n];
      maxSize=n;
      head=1;
      rear=0;
    };

    bool enQueue(int newdata)
    {
      if((rear+2)%maxSize==head) return false;
      rear=(rear+1)%maxSize;
      data[rear]=newdata;
      return true;
    };

    int deQueue()
    {
      if((rear+1)%maxSize==head) return -1;
      int temp=data[head];
      head=(head+1)%maxSize;
      return temp;
    };

    bool isEmpty()
    {
      return (rear+1)%maxSize==head;
    };

};

class myNode
{
  friend class myGraph;
  private:
    myNode *next;
    int data;

  public:
    myNode(int newdata)
    {
      data=newdata;
      next=NULL;
    };

};

class myGraph
{
  private:
    myNode **vertex;
    int vnum;
    int *marks;
    int *indegree;

  public:
    myGraph(int n)
    {
      vnum=n;
      vertex=new myNode *[n];
      marks=new int [n];
      indegree =new int [n];
      for(int i=0;i<n;i++)
      {
        vertex[i]=NULL;
        marks[i]=0;
        indegree[i]=0;
      }
    };

    void addEdge(int a,int b)
    {
      if(!vertex[a]) vertex[a]=new myNode(b);
      else
      {
        myNode* temp=vertex[a];
        while(temp->next) temp=temp->next;
        temp->next=new myNode(b);
      }

    };

    int topoSort()
    {
      myQueue data(vnum+100);
      myNode *temp;
      int ct=0;
      int nowCt=0;
      int tempCt=0;
      int nowPosi=0;
      for(int i=0;i<vnum;i++)
      {
        temp=vertex[i];
        while(temp)
        {
          indegree[temp->data]++;
          temp=temp->next;
        }
      }
      for(int i=0;i<vnum;i++)
      {
        if(indegree[i]==0) {data.enQueue(i);nowCt++;}
      }
      while(!data.isEmpty())
      {
        tempCt=0;
        for(int i=0;i<nowCt;i++)
        {
          nowPosi=data.deQueue();
          marks[nowPosi]=1;
          temp=vertex[nowPosi];
          while(temp)
          {
            if(marks[temp->data]==0)
            {
              indegree[temp->data]--;
              if(indegree[temp->data]==0)
              {
                data.enQueue(temp->data);
                tempCt++;
              }
            }
            temp=temp->next;
          }
        }
        nowCt=tempCt;
        ct++;

      }
      return ct;

    };

    ~myGraph()
    {
      myNode* now;
      myNode*temp;
      for(int i=0;i<vnum;i++)
      {
        now=vertex[i];
        while(now)
        {
          temp=now;
          now=now->next;
          delete temp;
        }
      }
      delete [] vertex;
      delete [] marks;
      delete [] indegree;
    };

};



int main()
{
  int n,m;
  int a,b;
  cin>>n>>m;
  myGraph g(n);
  for(int i=0;i<m;i++)
  {
    cin>>a>>b;
    g.addEdge(b-1,a-1);
  }
  cout<<g.topoSort()<<endl;



  return 0;
}
