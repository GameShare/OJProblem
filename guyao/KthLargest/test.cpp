#include<iostream>
#include"kThFinder.h"

using namespace std;

///the function findKthByQuicksort is an idea of find the Kth largest number by using QuickSort but the complexity is wrong maybe?
bool FKBQ(int *data,int k,int low,int high)
{
  if(low>=high) return true;
  int first=low;
  int last=high;
  int key=data[low];
  while(first<last)
  {
    while(first<last&&data[last]<key) last--;
    data[first]=data[last];
    while(first<last&&data[first]>=key) first++;
    data[last]=data[first];
  }
  data[first]=key;
  if(k==first) return true;
  else if(first>k) return FKBQ(data,k,low,first-1);
  else return FKBQ(data,k,first+1,high);
}

int findKthByQuicksort(int *data,int k,int N)
{
  if(FKBQ(data,k-1,0,N-1)) return data[k-1];
  else return -1;
}


int findKthByHeapsort(int *data,myHeapMin &hpMin,int k,int N)
{
  int temp;
  for(int i=k;i<N;i++)
  {
    temp=hpMin.deQueue();
    if(data[i]>temp)
    {
      hpMin.enQueue(data[i]);
    }
    else hpMin.enQueue(temp);
  }
 return hpMin.deQueue();
}



int main()
{
  int N;
  int *data;
  int temp;
  cin>>N;
  data=new int [N];
  for(int i=0;i<N;i++)
  {
    cin>>temp;
    data[i]=temp;
  }
  myHeapMax hpMax(N,data);
  int k;
  cin>>k;
  myHeapMin hpMin(k,data);
  ///the first algorithms
  cout<<"O(N+K*log N): "<<hpMax.KthNumber(k)<<endl;
  cout<<"O(N*log K): "<<findKthByHeapsort(data,hpMin,k,N)<<endl;
  delete [] data;
  return 0;
}
