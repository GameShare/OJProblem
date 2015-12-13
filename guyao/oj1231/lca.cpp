#include <iostream>

using namespace std;

class mySet
{

  private:
    int *nodes;
    int maxSize;

  public:
    mySet(int N)
    {
      maxSize=N;
      nodes =new int [N];
      for(int i=0;i<N;i++) nodes[i]=-1;
    };

    void addNum(int posi,int lc,int rc)
    {
        if(lc!=-1) nodes[lc]=posi;
        if(rc!=-1) nodes[rc]=posi;
    };

    int findCommon(int x,int y)
    {
      while(x!=y)
      {
        if(x>y)
        {
          if(nodes[x]!=-1) x=nodes[x];
          else return -1;
        }
        else
        {
          if(nodes[y]!=-1) y=nodes[y];
          else return -1;
        }
      }
      return x;
    };

    ~mySet()
    {
      delete [] nodes;
    };

};




int main()
{
  int N,X,Y;
  int templ,tempc;
  cin>>N>>X>>Y;
  mySet s(N);
  for(int i=0;i<N;i++)
  {
    cin>>templ>>tempc;
    s.addNum(i,templ-1,tempc-1);
  }
  cout<<s.findCommon(X-1,Y-1)+1<<endl;
  return 0;
}
