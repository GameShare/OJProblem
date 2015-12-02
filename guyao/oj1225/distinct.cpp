#include<iostream>

using namespace std;

void qsort(int *data, int low, int high)
{
  if(low>=high) return;
  int key=data[low];
  int first=low;
  int last=high;
  while(first<last)
  {
    while(key<data[last]&&first<last) last--;
    data[first]=data[last];
    while(key>=data[first]&&first<last) first++;
    data[last]=data[first];
  }
  data[first]=key;
  qsort(data,low,first-1);
  qsort(data,first+1,high);
}




int main()
{
  int N;
  int result=1;
  int temp;
  cin>>N;
  int *data=new int [N];
  for(int i=0;i<N;i++) cin>>data[i];
  qsort(data,0,N-1);
  temp=data[0];
  for(int i=1;i<N;i++)
  {
    if(data[i]!=temp)
    {
      temp=data[i];
      result++;
    }
  }
  cout<<result;
  return 0;
}
