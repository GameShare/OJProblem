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

        void



        void dijkstra(int start,int ed)
        {
          int *distance=new int [vnum];
          int temp;
          for(int i=0;i<vnum;i++)
          {
            distance[i]=2147483647;
          }
          distance[start]=0;
          myQueue q(vnum+100);
          q.enQueue(start);
          myNode *nowPosi;
          while(!q.isEmpty())
          {
            temp=q.deQueue();
            nowPosi=vertex[temp];
            while(nowPosi)
            {
              if(distance[temp]!=2147483647)
              {
                if(distance[nowPosi->data]>distance[temp]+nowPosi->weight)
                {
                  q.enQueue(nowPosi->data);
                  distance[nowPosi->data]=distance[temp]+nowPosi->weight;
                }
              }
              nowPosi=nowPosi->next;
            }
          }
          cout<<distance[ed]<<endl;
          delete [] distance;
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

  return 0;
}
