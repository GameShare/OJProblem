#ifndef KTHFINDER_H_INCLUDED
#define KTHFINDER_H_INCLUDED

#include<iostream>

using namespace std;

class myHeapMax
{
  private:
    int *data;
    int maxSize;
    int rear;
    void swap(int &a,int &b)
    {
      int temp;
      temp=a;
      a=b;
      b=temp;
    };

    void downHeap(int posi)
    {
      int lchild,rchild;
      while(true)
      {
        lchild=posi*2+1;
        rchild=2*posi+2;
        if(lchild<=rear&&rchild<=rear)
        {
          if(data[lchild]>data[rchild])
          {
            if(data[lchild]>data[posi]) {swap(data[lchild],data[posi]);posi=lchild;}
            else break;
          }
          else
          {
            if(data[rchild]>data[posi]) {swap(data[rchild],data[posi]);posi=rchild;}
            else break;
          }
        }
        else if(lchild>rear&&rchild>rear) break;
        else
        {
          if(data[lchild]>data[posi]) {swap(data[lchild],data[posi]);posi=lchild;}
          else break;
        }
      }
    };

    void upHeap(int posi)
    {
      int parent;
      while(true)
      {
        parent=(posi-1)/2;
        if(parent>=0)
        {
          if(data[parent]<data[posi])
          {
            swap(data[parent],data[posi]);
            posi=parent;
          }
          else break;
        }
        else break;
      }
    };


  public:
    myHeapMax(int N,int *allData)
    {
      maxSize=N;
      rear=maxSize-1;
      data=new int [N];
      for(int i=0;i<N;i++)
      {
        data[i]=allData[i];
      }
      for(int i=N/2-1;i>=0;i--)
      {
        downHeap(i);
      }
    };

    int deQueue()
    {
      int temp=data[0];
      data[0]=data[rear];
      rear--;
      downHeap(0);
      return temp;
    };

    void enQueue(int num)
    {
      data[++rear]=num;
      upHeap(rear);
    };

    int getTop()
    {
      if(rear>=0) return data[0];
      else return -1;
    };

    int KthNumber(int k)
    {
      if(k<=rear+1)
      {
        for(int i=0;i<k-1;i++)
        {
          deQueue();
        }
        return deQueue();
      }
      else return -1;
    };

    ~myHeapMax()
    {
      delete [] data;
    };
};

class myHeapMin
{
  private:
    int *data;
    int maxSize;
    int rear;
    void swap(int &a,int &b)
    {
      int temp;
      temp=a;
      a=b;
      b=temp;
    };

    void downHeap(int posi)
    {
      int lchild,rchild;
      while(true)
      {
        lchild=posi*2+1;
        rchild=2*posi+2;
        if(lchild<=rear&&rchild<=rear)
        {
          if(data[lchild]<data[rchild])
          {
            if(data[lchild]<data[posi]) {swap(data[lchild],data[posi]);posi=lchild;}
            else break;
          }
          else
          {
            if(data[rchild]<data[posi]) {swap(data[rchild],data[posi]);posi=rchild;}
            else break;
          }
        }
        else if(lchild>rear&&rchild>rear) break;
        else
        {
          if(data[lchild]<data[posi]) {swap(data[lchild],data[posi]);posi=lchild;}
          else break;
        }
      }
    };

    void upHeap(int posi)
    {
      int parent;
      while(true)
      {
        parent=(posi-1)/2;
        if(parent>=0)
        {
          if(data[parent]>data[posi])
          {
            swap(data[parent],data[posi]);
            posi=parent;
          }
          else break;
        }
        else break;
      }
    };


  public:
    myHeapMin(int N,int *allData)
    {
      maxSize=N;
      rear=maxSize-1;
      data=new int [N];
      for(int i=0;i<N;i++)
      {
        data[i]=allData[i];
      }
      for(int i=N/2-1;i>=0;i--)
      {
        downHeap(i);
      }
    };

    int deQueue()
    {
      int temp=data[0];
      data[0]=data[rear];
      rear--;
      downHeap(0);
      return temp;
    };

    void enQueue(int num)
    {
      data[++rear]=num;
      upHeap(rear);
    };

    int getTop()
    {
      if(rear>=0) return data[0];
      else return -1;
    };

    int KthNumber(int k)
    {
      if(k<=rear+1)
      {
        for(int i=0;i<k-1;i++)
        {
          deQueue();
        }
        return deQueue();
      }
      else return -1;
    };

    ~myHeapMin()
    {
      delete [] data;
    };
};




#endif // KTHFINDER_H_INCLUDED
