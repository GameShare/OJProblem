#include<iostream>

using namespace std;

class myNode
{
    friend class myGraph;
    private:
        int data;
        int weight;
        myNode *next;

    public:
        myNode(int n,int w)
        {
          data=n;
          weight=w;
          next=NULL;
        };
};

class myQueue
{
  private:
    int *data;
    int maxSize;
    int head;
    int rear;

  public:
    myQueue(int n)
    {
      maxSize=n;
      data=new int [n+1];
      head=1;
      rear=0;
    };

    void enQueue(int n)
    {
      if((rear+2)%maxSize==head) return;
      rear=(rear+1)%maxSize;
      data[rear]=n;
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

    ~myQueue()
    {
      delete [] data;
    };
};

class minHeap
{
  private:
    int *data;
    int *start;
    int *pointer;
    int maxSize;

    void mySwap(int &a,int &b)
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
              mySwap(start[posi],start[lchild]);
              pointer[start[posi]]=posi;
              pointer[start[lchild]]=lchild;
              posi=lchild;
            }
            else return;
          }
          else
          {
            if(data[posi]>data[rchild])
            {
              mySwap(data[posi],data[rchild]);
              mySwap(start[posi],start[rchild]);
              pointer[start[posi]]=posi;
              pointer[start[rchild]]=rchild;
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
            mySwap(data[posi],data[lchild]);
            mySwap(start[posi],start[lchild]);
            pointer[start[posi]]=posi;
            pointer[start[lchild]]=lchild;
            posi=lchild;
          }
          else return;
        }
      }
    };

    void upHeap(int posi)
    {
      int parent;
      while(true)
      {
        if(posi==0) return;
        parent=(posi-1)/2;
        if(data[posi]<data[parent])
        {
          mySwap(data[posi],data[parent]);
          mySwap(start[posi],start[parent]);
          pointer[start[posi]]=posi;
          pointer[start[parent]]=parent;
          posi=parent;
        }
        else return;
      }
    };

  public:
    minHeap(int n,int *newdata)
    {
      maxSize=n;
      pointer=new int [n];
      start=new int [n];
      data=newdata;
      for(int i=0;i<n;i++) {pointer[i]=i;start[i]=i;}
      for(int i=n/2-1;i>=0;i--)
      {
        siftdown(i);
      }
    };

    int deQueue(int &nowDis)
    {
      int temp=start[0];
      nowDis=data[0];
      mySwap(data[0],data[maxSize-1]);
      mySwap(start[0],start[maxSize-1]);
      pointer[start[0]]=0;
      pointer[start[maxSize-1]]=maxSize-1;
      maxSize--;
      siftdown(0);
      return temp;
    };

    void changeW(int posi,int newW)
    {
      int temp=pointer[posi];
      data[temp]=newW;
      upHeap(temp);
      siftdown(temp);
    };

    int getDis(int posi)
    {
      return data[pointer[posi]];
    };

    ~minHeap()
    {
      delete [] pointer;
      delete [] data;
      delete [] start;
    };

};



class myGraph
{
    private:
        myNode **vertex;
        int *marks;
        int vnum;
        void printPre(int ed,int *prev)
        {
          if(prev[ed]>=0)
          {
            printPre(prev[ed],prev);
            cout<<ed+1<<' ';
          }
          else
          {
            cout<<ed+1<<' ';
          }

        };

    public:
        myGraph(int n)
        {
          vnum=n;
          vertex=new myNode *[n];
          marks=new int [n];
          for(int i=0;i<n;i++)
          {
              vertex[i]=NULL;
              marks[i]=0;
          }

        };

        void addEdge(int a,int b,int w)
        {
          myNode *temp=vertex[a];
          if(!temp) vertex[a]=new myNode(b,w);
          else
          {
            while(temp->next) temp=temp->next;
            temp->next=new myNode(b,w);
          }
        };




        void dijkstra(int start,int ed)
        {
          int *distance=new int [vnum];
          int *known=new int [vnum];
          int *prev=new int [vnum];
          int ct=vnum;
          int temp;
          for(int i=0;i<vnum;i++)
          {
            distance[i]=2147483647;
            known[i]=-2147483647;
            prev[i]=start;
          }
          distance[start]=0;
          known[start]=-1;
          prev[start]=-1;
          minHeap h(vnum,distance);
          myNode *nowPosi;
          int nowDis;
          while(ct>=1)
          {
            temp=h.deQueue(nowDis);
            nowPosi=vertex[temp];
            known[temp]=-known[temp];
            ct--;
            while(nowPosi)
            {
              if(known[nowPosi->data]<0)
              {
                if(nowDis!=2147483647)
                {
                  if(h.getDis(nowPosi->data)>nowDis+nowPosi->weight)
                  {
                    known[nowPosi->data]=-(known[temp]+1);
                    h.changeW(nowPosi->data,nowDis+nowPosi->weight);
                    prev[nowPosi->data]=temp;
                  }
                  else if(h.getDis(nowPosi->data)==nowDis+nowPosi->weight)
                  {
                    if(known[nowPosi->data]<-(known[temp]+1))
                    {
                      known[nowPosi->data]=-(known[temp]+1);
                      h.changeW(nowPosi->data,nowDis+nowPosi->weight);
                      prev[nowPosi->data]=temp;
                    }
                  }
                }
              }
              nowPosi=nowPosi->next;
            }
          }
          cout<<h.getDis(ed)<<endl;
          printPre(ed,prev);
          cout<<endl;
          delete [] prev;
          delete [] known;
        };


        ~myGraph()
        {
          myNode *now;
          myNode *temp;
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
        };
};




int main()
{
  int n,m,start,ed;
  int a,b,w;
  cin>>n>>m>>start>>ed;
  myGraph g(n);
  for(int i=0;i<m;i++)
  {
    cin>>a>>b>>w;
    g.addEdge(a-1,b-1,w);
  }
  g.dijkstra(start-1,ed-1);

  return 0;
}
