#include<iostream>

using namespace std;

void QuickSort(int *data, int low, int high)
{
  if(high<=low) return;
  int key=data[low];
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

int Bsearch(int *data,int d,int low,int high)
{
  if(high<low) return -1;
  int mid=(low+high)/2;
  if(data[mid]>d) return Bsearch(data,d,low,mid-1);
  else if(data[mid]<d) return Bsearch(data,d,mid+1,high);
  else return mid;
}


class Set
{
  private:
    int *data;
    int n;

  public:
    Set(){n=0;data=new int[10000];};

    void init() {n=0;};
    void insertSet(int newdata)
    {
      //看来还是要处理重复数据orz。。。
      if(Bsearch(data,newdata,0,n-1)==-1)
      {
        data[n]=newdata;
        n++;
        QuickSort(data,0,n-1);
      }
    };

    void SortSet() {QuickSort(data,0,n-1);};

    void setAnd(Set &other)
    {
      int add=0;
      for(int i=0;i<other.n;i++)
      {
        if(Bsearch(data,other.data[i],0,n-1)==-1)
        {
          data[n+add]=other.data[i];
          add++;
        }
      }
      n+=add;
      QuickSort(data,0,n-1);
    };

    void setSub(Set &other)
    {
      int posi=-1;
      for(int i=0;i<other.n;i++)
      {
        if((posi=Bsearch(data,other.data[i],0,n-1))!=-1)
        {
          for(int j=posi+1;j<n;j++) data[j-1]=data[j];
          n--;
        }
      }
    };

    void setMul(Set &other)
    {
      int *temp=new int[10000];
      int newN=0;
      int posi=-1;
      for(int i=0;i<n;i++)
      {
        if((posi=Bsearch(other.data,data[i],0,other.n-1))!=-1)
        {
          temp[newN]=other.data[posi];
          newN++;
        }
      }
      delete [] data;
      data=temp;
      n=newN;
    };

    void printSet()
    {
      for(int i=0;i<n;i++)
      {
        cout<<data[i]<<' ';
      }
      cout<<endl;
    }
};

int main()
{
  int n;
  Set s0;
  Set s1;
  cin>>n;
  for(int i=0;i<n;i++)
  {
    char op;
    int m;
    int temp;
    cin>>op;
    cin>>m;
    if(op=='+')
    {
      s1.init();
      for(int j=0;j<m;j++)
      {
        cin>>temp;
        s1.insertSet(temp);
      }
      s0.setAnd(s1);
      s0.SortSet();
      s0.printSet();
    }
    if(op=='-')
    {
      s1.init();
      for(int j=0;j<m;j++)
      {
        cin>>temp;
        s1.insertSet(temp);
      }
      s0.setSub(s1);
      s0.SortSet();
      s0.printSet();
    }
    if(op=='*')
    {
      s1.init();
      for(int j=0;j<m;j++)
      {
        cin>>temp;
        s1.insertSet(temp);
      }
      s0.setMul(s1);
      s0.SortSet();
      s0.printSet();
    }
  }




  return 0;
}
