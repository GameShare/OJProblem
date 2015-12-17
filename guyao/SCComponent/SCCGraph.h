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
      if(!temp) vertex[a]=new myNode(b);
      while(temp->next) temp=temp->next;
      temp->next=new myNode(b);
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
