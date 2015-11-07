#include <iostream>

using namespace std;

void convert(int *po,int &pos,int poe,int *io, int ios, int ioe)
{
  int temp=0;
  for(int i=ios;i<=ioe;i++)
  {
    if(io[i]==po[pos])
    {
      temp=i;
      break;
    }
  }

  if(temp-1>=ios) {pos++;convert(po,pos,poe,io,ios,temp-1);}

  if(ioe>=temp+1) {pos++;convert(po,pos,poe,io,temp+1,ioe);}
  cout<<io[temp]<<' ';
}






int main()
{
  int num;
  cin>>num;
  int temp;
  int *po=new int [num];
  int *io=new int [num];
  for(int i=0;i<num;i++)
  {
    cin>>temp;
    po[i]=temp;
  }
  for(int i=0;i<num;i++)
  {
    cin>>temp;
    io[i]=temp;
  }
  int pos=0;
  convert(po,pos,num-1,io,0,num-1);




  return 0;
}
