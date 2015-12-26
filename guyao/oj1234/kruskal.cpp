#include<iostream>

using namespace std;



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

class edge
{
    friend class myGraph;
    public:
        int weight;
        int head;
        int rear;

    public:
        edge()
        {
          weight=0;
          head=0;
          rear=0;
        };
        void setEdge(int h,int r,int w)
        {
            weight=w;
            head=h;
            rear=r;
        }
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

        int findRoot(int a)
        {
            if(data[a]>=0) return data[a]=findRoot(data[a]);
            else return a;
        };

        bool unionSet(int a,int b)
        {
            int root1=findRoot(a);
            int root2=findRoot(b);
            if(root1!=root2)
            {
              if(data[root1]<data[root2])
              {
                  data[root1]+=data[root2];
                  data[root2]=root1;
              }
              else
              {
                  data[root2]+=data[root1];
                  data[root1]=root2;
              }
              return true;
            }
            else return false;
        };



        ~mySet()
        {
          delete [] data;
        };
};

void qsort(edge *eList,int low,int high);

class myGraph
{
    private:
        myNode **vertex;
        int vnum;
        int edgeNum;
        int *marks;
        edge *allEdge;

    public:
        myGraph(int n,int m)
        {
          vertex= new myNode *[n];
          allEdge=new edge[m];
          vnum=n;
          edgeNum=m;
          marks=new int [n];
          for(int i=0;i<n;i++)
          {
              vertex[i]=NULL;
              marks[i]=0;
          }
        };

        void addEdge(int a,int b,int weight,int m)
        {
          allEdge[m].setEdge(a,b,weight);
          myNode *temp=vertex[a];
          if(!temp) vertex[a]=new myNode(b);
          else
          {
              while(temp->next) temp=temp->next;
              temp->next=new myNode(b);
          }

        };

        int kruskal()
        {
            qsort(allEdge,0,edgeNum-1);
            mySet data(vnum);
            int ct=vnum;
            int result=0;
            for(int i=0;i<edgeNum;i++)
            {
                if(data.findRoot(allEdge[i].head)!=data.findRoot(allEdge[i].rear))
                {
                    data.unionSet(allEdge[i].head,allEdge[i].rear);
                    ct--;
                    result+=allEdge[i].weight;
                }
                if(ct==1) break;
            }
            return result;
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
          delete [] allEdge;
        };


};


void qsort(edge *eList,int low,int high)
{
    if(low>=high) return;
    int first=low;
    int last=high;
    edge mid=eList[first];
    while(first<last)
    {
        while(eList[last].weight>=mid.weight&&first<last) last--;
        eList[first]=eList[last];
        while(eList[first].weight<mid.weight&&first<last) first++;
        eList[last]=eList[first];
    }
    eList[first]=mid;
    qsort(eList,low,first-1);
    qsort(eList,first+1,high);
}










int main()
{
    int n,m;
    int a,b,w;
    cin>>n>>m;
    myGraph g(n,m);
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>w;
        g.addEdge(a-1,b-1,w,i);
    }
    cout<<g.kruskal()<<endl;
    return 0;
}
