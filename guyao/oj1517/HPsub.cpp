#include<iostream>

using namespace std;

int main()
{
  char str1[100001]={0};
  char str2[100001]={0};
  int num1[100001]={0};
  int num2[100001]={0};
  int len1=0;
  int len2=0;
  cin.getline(str1,100001);
  cin.getline(str2,100001);
  for(int i=100000;i>=0;i--)
  {
    if(str1[i]>='0'&&str1[i]<='9')
    {
      num1[len1++]=str1[i]-'0';
    }
    if(str2[i]>='0'&&str2[i]<='9')
    {
      num2[len2++]=str2[i]-'0';
    }
  }
  int up=0;
  int bn=0;
  int res[100001]={0};
  int flag=0;
  for(int i=100000;i>=0;i--)
  {
    if(num1[i]<num2[i])
    {
      flag=-1;
      break;
    }
    else if(num1[i]>num2[i])
    {
      flag=1;
      break;
    }
  }
  if(flag>0)
  {
    for(int i=0;i<len1;i++)
    {
      bn=(num1[i]-num2[i]+up+10)%10;
      up=(num1[i]-num2[i]+up-9)/10;
      res[i]=bn;
    }
    int j=len1-1;
    while(res[j]==0) j--;
    for(;j>=0;j--)
    {
      cout<<res[j];
    }
    cout<<endl;
  }
  else
  {
    if(flag==0) cout<<0;
    else
    {
      cout<<'-';
      for(int i=0;i<len2;i++)
      {
        bn=(num2[i]-num1[i]+up+10)%10;
        up=(num2[i]-num1[i]+up-9)/10;
        res[i]=bn;
      }
      int j=len2-1;
      while(res[j]==0) j--;
      for(;j>=0;j--)
      {
        cout<<res[j];
      }
      cout<<endl;
    }

  }


  return 0;
}
