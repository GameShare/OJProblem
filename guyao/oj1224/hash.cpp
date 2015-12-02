#include<iostream>

using namespace std;

class myNode
{
  friend class myHash;
  private:
    int data;

    ///0=empty 1=full 2=deleted
    int status;
  public:
    myNode()
    {
      status=0;
    };
};


class myHash
{
  private:
    ///cannot be running in the computer but can AC
    ///as I think the OJ allow up to 800000 array.
    myNode data[799999];
    int maxSize;
    int h(int value)
    {
      if(value<0) value=2000000+value;
      return value%799999;
    };

  public:
    myHash()
    {
      maxSize=799999;
    };

    void insertNum(int num)
    {
      int initposi,posi;
      initposi=posi=h(num);
      while(data[posi].status>=1)
      {
        if(data[posi].data==num)
        {
          data[posi].status++;
          return;
        }
        posi=(posi+1)%maxSize;
        if(posi==initposi) return;
      }
      data[posi].data=num;
      data[posi].status=1;
    };

    int searchNum(int num)
    {
      int initposi,posi;
      initposi=posi=h(num);
      while(data[posi].status>=1)
      {
        if(data[posi].data==num) return data[posi].status;
        posi=(posi+1)%maxSize;
        if(posi==initposi) return 0;
      }
      return 0;
    };
};

int main()
{
  int N;
  int temp;
  int *a;
  int *b;
  int *c;
  int *d;
  cin>>N;
  a=new int [N];
  b=new int [N];
  c=new int [N];
  d=new int [N];
  myHash ht;

  for(int i=0;i<N;i++)
  {
    cin>>temp;
    a[i]=temp;
    cin>>temp;
    b[i]=temp;
    cin>>temp;
    c[i]=temp;
    cin>>temp;
    d[i]=temp;
  }
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++)
    {
      ht.insertNum(a[i]+b[j]);
    }
  }
  int result=0;
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++)
    {
      result+=ht.searchNum(-(c[i]+d[j]));
    }
  }
  cout<<result;


  delete [] a;
  delete [] b;
  delete [] c;
  delete [] d;



  return 0;
}
