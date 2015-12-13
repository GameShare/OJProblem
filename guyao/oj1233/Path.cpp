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
      next=NULL;
      data=newdata;
    };
};

class myStack
{
  private:
    int data[100];
    int top;

  public:
    myStack()
    {
      top=-1;
    };

    void push(int num)
    {
      top++;
      data[top]=num;
    };

    int pop()
    {
      int num;
      if(top==-1) return -1;
      else
      {
        num=data[top];
        top--;
        return num;
      }
    };

    int getTop()
    {
      if(top==-1) return -1;
      else return data[top];
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
        marks[i]=0;
        vertex[i]=NULL;
      }

    };

    void addEdge(int a,int b)
    {
      a=a-1;
      b=b-1;
      myNode *temp=vertex[a];
      if(!temp) vertex[a]=new myNode(b);
      else
      {
        while(temp->next) temp=temp->next;
        temp->next=new myNode(b);
      }
    };

    int findMPath(int M,int start)
    {
      start--;
      int ct=0;
      int len=0;
      int *nodeCount= new int [vnum];
      for(int i=0;i<vnum;i++) nodeCount[i]=0;
      myStack vs;
      vs.push(start);
      marks[start]=1;
      while(vs.getTop()!=-1)
      {
        if(len==M)
        {
          ct++;
          int temp=vs.pop();
          marks[temp]=0;
          nodeCount[temp]=0;
          if(vs.getTop()!=-1) nodeCount[vs.getTop()]++;
          len--;

        }
        else
        {
          myNode *nowPosi=vertex[vs.getTop()];
          for(int i=0;i<nodeCount[vs.getTop()];i++) if(nowPosi) nowPosi=nowPosi->next;
          while(true)
          {
            if(!nowPosi)
            {
              int temp;
              temp=vs.pop();
              marks[temp]=0;
              nodeCount[temp]=0;
              if(vs.getTop()!=-1) nodeCount[vs.getTop()]++;
              len--;
              break;
            }
            else
            {
              if(marks[nowPosi->data]==0)
              {
                vs.push(nowPosi->data);
                marks[nowPosi->data]=1;
                len++;
                break;
              }
              else
              {
                nowPosi=nowPosi->next;
                if(vs.getTop()!=-1) nodeCount[vs.getTop()]++;
              }
            }
          }
        }
      }
      return ct;
    };

    ~myGraph()
    {
      for(int i=0;i<vnum;i++)
      {
        myNode *now=vertex[i];
        myNode *temp;
        while(now)
        {
          temp=now;
          now=now->next;
          delete temp;
        }
      }
      delete [] vertex;
    };
};



int main()
{
  int n,m,start,M;
  int a,b;
  cin>>n>>m>>start>>M;
  myGraph mg(n);
  for(int i=0;i<m;i++)
  {
    cin>>a>>b;
    mg.addEdge(a,b);
  }
  cout<<mg.findMPath(M,start)<<endl;
  return 0;
}
