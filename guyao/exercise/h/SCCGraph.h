#ifndef SCCGRAPH_H_INCLUDED
#define SCCGRAPH_H_INCLUDED
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
      myNode *temp=vertex[a];
      if(!temp) {vertex[a]=new myNode(b);return;}
      while(temp->next) temp=temp->next;
      temp->next=new myNode(b);
    };

    void findSeqNoHelp(int start,int &nowSeqNum)
    {
      myNode *temp=vertex[start];
      marks[start]=-1;
      while(temp)
      {
        if(marks[temp->data]==0)
        {
          findSeqNoHelp(temp->data,nowSeqNum);
        }
        temp=temp->next;
      }
      marks[start]=nowSeqNum;
      nowSeqNum++;
    };

    void findSeqNo()
    {
      for(int i=0;i<vnum;i++) marks[i]=0;
      int ct=vnum;
      int start=0;
      int nowSeqNum=1;
      int flag=false;
      while(ct!=0)
      {
        ct=vnum;
        flag=false;
        findSeqNoHelp(start,nowSeqNum);
        for(int i=0;i<vnum;i++)
        {
          if(marks[i]!=0)
          {
            ct--;
          }
          else
          {
            if(!flag) start=i;
            flag=true;
          }
        }
      }
    };

    void dfsByMap(int start,myNode **Map)
    {
      myNode *temp=Map[start];
      marks[start]=-marks[start];
      cout<<start<<' ';
      while(temp)
      {
        if(marks[temp->data]>0) dfsByMap(temp->data,Map);
        temp=temp->next;
      }
    };

    void findSCC()
    {
      myNode **antiMap=new myNode *[vnum];
      for(int i=0;i<vnum;i++)
      {
        antiMap[i]=NULL;
      }
      myNode *temp;
      for(int i=0;i<vnum;i++)
      {
        myNode *nowPosi=vertex[i];
        while(nowPosi)
        {
          temp=antiMap[nowPosi->data];
          if(!temp) antiMap[nowPosi->data]=new myNode(i);
          else
          {
            while(temp->next) temp=temp->next;
            temp->next=new myNode(i);
          }
          nowPosi=nowPosi->next;
        }
      }

      findSeqNo();

      for(int i=vnum;i>0;i--)
      {
        int j;
        for(j=0;j<vnum;j++)
        {
          if(marks[j]==i||marks[j]==-i) break;
        }
        if(marks[j]>0)
        {
          dfsByMap(j,antiMap);
          cout<<endl;
        }
      }

      myNode *now;
      for(int i=0;i<vnum;i++)
      {
        now=antiMap[i];
        while(now)
        {
          temp=now;
          now=now->next;
          delete temp;
        }
      }
      delete [] antiMap;
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




#endif // SCCGRAPH_H_INCLUDED
