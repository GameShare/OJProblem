#ifndef AMGRAPH_H_INCLUDED
#define AMGRAPH_H_INCLUDED

#include<iostream>

using namespace std;


class myQueue
{
  private:
    int *data;
    int rear;
    int head;
    int maxSize;

  public:
    myQueue(int n)
    {
      data=new int [n+1];
      maxSize=n;
      head=1;
      rear=0;
    };

    void enQueue(int num)
    {
      if((rear+2)%maxSize==head) return;
      rear=(rear+1)%maxSize;
      data[rear]=num;
    };

    int deQueue()
    {
      int temp;
      if((rear+1)%maxSize==head) return 0;
      temp=data[head];
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

class EulerNode
{
  friend class myGraph;
  private:
    EulerNode *next;
    int data;
  public:
    EulerNode(int newdata)
    {
      data=newdata;
      next=NULL;
    };
};



class myGraph
{
  private:
    int **data;
    int vnum;
    int *marks;
    void DFSHelp(int start)
    {
      cout<<start<<' ';
      marks[start]=1;
      for(int i=0;i<vnum;i++)
      {
        if(data[start][i]==1&&marks[i]==0) DFSHelp(i);
      }
    };

  public:
    myGraph(int n)
    {
      vnum=n;
      marks=new int [n];
      data=new int *[n];
      for(int i=0;i<n;i++)
      {
        data[i]=new int [n];
        for(int j=0;j<n;j++) data[i][j]=0;
      }
    };

    void insertEdge(int a,int b)
    {
      data[a][b]=1;
      data[b][a]=1;
    };

    void DFS(int start)
    {
      for(int i=0;i<vnum;i++)
      {
        marks[i]=0;
      }
      DFSHelp(start);
      cout<<endl;
    };

    int BFS(int start,bool flag)
    {
      int ct=0;
      for(int i=0;i<vnum;i++)
      {
        marks[i]=0;
      }
      int temp;
      myQueue vertexQ(vnum);
      vertexQ.enQueue(start);
      marks[start]=1;
      ct++;
      while(!vertexQ.isEmpty())
      {
        temp=vertexQ.deQueue();
        if(flag) cout<<temp<<' ';
        for(int i=0;i<vnum;i++)
        {
          if(data[temp][i]==1&&marks[i]==0)
          {
            vertexQ.enQueue(i);
            marks[i]=1;
            ct++;
          }
        }
      }
      if(flag) cout<<endl;
      return ct;
    };

    bool EulerCycle(int start)
    {
      if(BFS(start,false)!=vnum) return false;
      for(int i=0;i<vnum;i++)
      {
        int ct=0;
        for(int j=0;j<vnum;j++)
        {
          if(data[i][j]==1) ct++;
        }
        if(ct%2!=0) return false;
      }
      int **clone=new int *[vnum];
      int edgeNum=0;
      for(int i=0;i<vnum;i++)
      {
        clone[i]=new int [vnum];
        for(int j=0;j<vnum;j++)
        {
          clone[i][j]=data[i][j];
          if(data[i][j]==1) edgeNum++;
        }
      }
      edgeNum/=2;
      EulerNode *beg=new EulerNode(0);

      beg->next=EulerCyclePart(clone,start,edgeNum);
      EulerNode *nowPosi=beg;
      EulerNode *temp;
      while(edgeNum!=0)
      {
        temp=EulerCyclePart(clone,nowPosi->next->data,edgeNum);
        if(temp)
        {
          EulerNode* ed=temp;
          while(ed->next) ed=ed->next;
          ed->next=nowPosi->next->next;
          delete nowPosi->next;
          nowPosi->next=temp;
        }
        if(nowPosi->next)nowPosi=nowPosi->next;
        else return false;
      }
      temp=beg;
      while(temp->next)
      {
        cout<<temp->next->data<<' ';
        beg=temp->next;
        delete temp;
        temp=beg;
      }
      cout<<endl;
      return true;
    };

    EulerNode* EulerCyclePart(int **data,int start,int &edgeNum)
    {
      bool flag=true;
      for(int i=0;i<vnum;i++)
      {
        if(data[start][i]==1) flag=false;
      }
      if(flag) return NULL;
      EulerNode *part=new EulerNode(start);
      EulerNode *nowPosi=part;
      while(true)
      {
        flag=true;
        for(int i=0;i<vnum;i++)
        {
          if(data[start][i]==1)
          {
            flag=false;
            nowPosi->next=new EulerNode(i);
            data[start][i]=0;
            data[i][start]=0;
            edgeNum--;
            start=i;
            nowPosi=nowPosi->next;
          }
        }
        if(flag) break;
      }
      return part;
    };




    ~myGraph()
    {
      delete [] marks;
      for(int i=0;i<vnum;i++)
      {
        delete [] data[i];
      }
      delete [] data;
    };
};





#endif // AMGRAPH_H_INCLUDED
