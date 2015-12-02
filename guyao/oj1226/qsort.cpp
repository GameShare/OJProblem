#include<iostream>

using namespace std;


void qsort(int *data,int low,int high)
{
  if(low>=high) return;
  int mid=(low+high)/2;
  int temp;
  if(data[high]>data[low])
  {
    if(data[high]<data[mid])
    {
      temp=high;
    }
    else
    {
      if(data[mid]>data[low])
      {
        temp=mid;
      }
      else temp=low;
    }
  }
  else
  {
    if(data[high]>data[mid]) temp=high;
    else
    {
      if(data[mid]>data[low]) temp=low;
      else temp=mid;
    }
  }



  int key=data[temp];
  data[temp]=data[low];
  int first=low;
  int last=high;

  while(first<last)
  {
    while(data[last]>=key&&first<last)
    {
      last--;
    }
    data[first]=data[last];
    while(data[first]<key&&first<last)
    {
      first++;
    }
    data[last]=data[first];
  }

  data[first]=key;
  qsort(data,low,first-1);
  qsort(data,first+1,high);
}





int main()
{
  int N=0;
  cin>>N;
  int *data=new int [N];
  for(int i=0;i<N;i++)
  {
    cin>>data[i];
  }
  qsort(data,0,N-1);
  for(int i=0;i<N;i++) cout<<data[i]<<' ';
  cout<<endl;
  delete [] data;
  return 0;
}
