#include <iostream>

using namespace std;

class Heap
{
  private:
    int data[20000];
    int rear;
    void swap(int &a,int &b)
    {
      int temp;
      temp=b;
      b=a;
      a=temp;
    };
    void upHeap(int posi)
    {
      int parent=(posi-1)/2;
      while(posi!=0)
      {
        if(data[parent]>data[posi])
        {
          swap(data[parent],data[posi]);
          posi=parent;
          parent=(posi-1)/2;
        }
        else
        {
          break;
        }
      }
    };

    void downHeap(int posi)
    {
      int lchild=posi*2+1;
      int rchild=posi*2+2;
      while(true)
      {
        lchild=posi*2+1;
        rchild=posi*2+2;
        if(lchild>rear) break;
        else if(lchild<=rear&&rchild>rear)
        {
          if(data[posi]>data[lchild])
          {
            swap(data[posi],data[lchild]);
            break;
          }
          else break;
        }
        else
        {
          if(data[lchild]>data[rchild])
          {
            if(data[posi]>data[rchild])
            {
              swap(data[posi],data[rchild]);
              posi=rchild;
            }
            else break;
          }
          else
          {
            if(data[posi]>data[lchild])
            {
              swap(data[posi],data[lchild]);
              posi=lchild;
            }
            else break;
          }
        }
      }
    }


  public:
      Heap() {rear=-1;};
      void insertData(int num)
      {
        data[++rear]=num;
        upHeap(rear);
      };
      int findX(int threshold)
      {
        int posi=0;
        int result;
        int targetNum=0;
        bool flag=true;
        while(posi<=rear)
        {

          if(threshold<data[posi])
          {
            if(flag)
            {
              result=posi;
              targetNum=data[posi];
              flag=false;
            }
            else
            {
              if(data[posi]<targetNum)
              {
                result=posi;
                targetNum=data[posi];
              }
            }
          }
          posi++;
        }
        return result;
      };

      void decreaseP(int posi,int v)
      {
        data[posi]-=v;
        upHeap(posi);
        downHeap(posi);
      };


};







int main()
{
  int n;
  cin>>n;
  char opeIns[10];
  int ope1,ope2;
  Heap h;
  for(int i=0;i<n;i++)
  {
    cin>>opeIns;
    if(opeIns[0]=='i')
    {
      cin>>ope1;
      h.insertData(ope1);
    }
    if(opeIns[0]=='f')
    {
      cin>>ope1;
      cout<<h.findX(ope1)+1<<endl;
    }
    if(opeIns[0]=='d')
    {
      cin>>ope1>>ope2;
      h.decreaseP(ope1-1,ope2);
    }

  }





  return 0;
}
