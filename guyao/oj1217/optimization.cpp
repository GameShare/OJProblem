#include<iostream>

using namespace std;

void QuickSort(int *data,int low, int high)
{
  int key=data[low];
  if(high<=low) return;
  int first=low;
  int last=high;
  while(first<last)
  {
    while(first<last&&data[last]>=key) last--;
    data[first]=data[last];
    while(first<last&&data[first]<key) first++;
    data[last]=data[first];
  }
  data[first]=key;
  QuickSort(data,low,first-1);
  QuickSort(data,first+1,high);
}

bool BinarySearch(int *data,int d,int low,int high)
{
  if(high<low) return false;
  int mid=(low+high)/2;
  if(data[mid]>d) return BinarySearch(data,d,low,mid-1);
  else if(data[mid]<d) return BinarySearch(data,d,mid+1,high);
  else return true;
}




int main()
{
  int n;
  cin>>n;
  int *data=new int[n];
  for(int i=0;i<n;i++) cin>>data[i];
  QuickSort(data,0,n-1);
  int m;
  int temp;
  cin>>m;
  for(int i=0;i<m;i++)
  {
    cin>>temp;
    if(BinarySearch(data,temp,0,n-1)) cout<<'Y'<<endl;
    else cout<<'N'<<endl;
  }




  return 0;
}
