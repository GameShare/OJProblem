#include<iostream>

using namespace std;



class myStack
{
  private:
    int *data;
    int rear;
    int maxSize;
  public:
    myStack(int n)
    {
      maxSize=n;
      data=new int [maxSize];
      rear=-1;
    };

    void push(int num)
    {
      data[++rear]=num;
    };

    int pop()
    {
      if(rear==-1) return -1;
      return data[rear--];
    };

    int getTop()
    {
      if(rear==-1) return -1;
      return data[rear];
    };
    int getSecond()
    {
      if(rear==-1||rear==0) return -1;
      return data[rear-1];
    };

    ~myStack()
    {
      delete [] data;
    };

};

class mySet
{
  private:
    int *data;
    int **noWall;
    int level;
    int findSib(int posi,int op)
    {
      int n=0;
      int temp;
      for(n=0;!(n*(n-1)/2<posi&&posi<=n*(n+1)/2);n++);
      if(op==0)
      {
        temp=(n-1)*(n-2)/2+posi-n*(n-1)/2-1;
        if((n-1)*(n-2)/2<temp&&temp<=n*(n-1)/2) return temp;
        else return -1;
      }
      if(op==1)
      {
        temp=(n-1)*(n-2)/2+posi-n*(n-1)/2;
        if((n-1)*(n-2)/2<temp&&temp<=n*(n-1)/2) return temp;
        else return -1;
      }

      if(op==2)
      {
        if(n==level) return -1;
        temp=n*(n+1)/2+posi-n*(n-1)/2;
        if(n*(n+1)/2<temp&&temp<=(n+2)*(n+1)/2) return temp;
        else return -1;
      }
      if(op==3)
      {
        if(n==level) return -1;
        temp=n*(n+1)/2+posi-n*(n-1)/2+1;
        if(n*(n+1)/2<temp&&temp<=(n+2)*(n+1)/2) return temp;
        else return -1;
      }
      return -1;
    };

    int findRoot(int posi)
    {
      posi--;
      myStack st((level*level+level)/2);
      while(data[posi]>=0)
      {
        st.push(posi);
        posi=data[posi];
      }
      int temp;
      temp=st.pop();
      while(temp!=-1)
      {
        data[temp]=posi;
        temp=st.pop();
      }
      return posi;
    };

  public:
    mySet(int n)
    {
      data=new int [n*(n+1)/2];
      noWall=new int *[n*(n+1)/2];
      for(int i=0;i<n*(n+1)/2;i++)
      {
        noWall[i]=new int [4];
        for(int j=0;j<4;j++) noWall[i][j]=0;
      }
      level=n;
      for(int i=0;i<n*(n+1)/2;i++)
      {
        data[i]=-1;
      }
    };

   bool zaqiang(int posi,int op,int start,int ed)
   {
     noWall[posi-1][op]=1;
     int other=findSib(posi,op);
     noWall[other-1][3-op]=1;
     if(other!=-1)
     {
       int root1=findRoot(posi);
       int root2=findRoot(other);
       if(root1!=root2)
       {
         if(data[root1]<data[root2])
         {
           data[root1]+=data[root2];
           data[root2]=root1;
         }
         else
         {
           data[root2]+=data[root1];
           data[root1]=root2;
         }
       }
       else return false;
     }
     else return false;
     return findRoot(start)==findRoot(ed);
   };

   void printRoute(int start,int ed)
   {
     int nowPosi=start;
     int temp;
     bool flag=true;
     myStack st(level*(level+1)/2);
     int *ct=new int [level*(level+1)/2];
     for(int i=0;i<level*(level+1)/2;i++)
     {
       ct[i]=0;
     }
     st.push(start);
     ct[start]=1;
     int last=0;
     while(nowPosi!=ed)
     {
       flag=true;
       for(int i=last;i<4;i++)
       {
         if(noWall[nowPosi-1][i])
         {
           temp=findSib(nowPosi,i);
           if(temp!=-1&&findRoot(temp)==findRoot(ed)&&ct[temp]==0)
           {
             st.push(temp);
             nowPosi=temp;
             ct[temp]=1;
             flag=false;
             last=0;
             break;
           }
         }
       }
      if(flag)
      {
        temp=st.pop();
        ct[temp]=0;
        nowPosi=st.getTop();
        for(int i=0;i<4;i++)
        {
          if(findSib(nowPosi,i)==temp) last=i+1;
        }
      }

     }
     temp=st.pop();
     myStack st2(level*(level+1)/2);

     while(temp!=-1)
     {
       st2.push(temp);
       temp=st.pop();
     }
     temp=st2.pop();
     while(temp!=-1)
     {
       cout<<temp<<' ';
       temp=st2.pop();
     }
     delete [] ct;
  };


    ~mySet()
    {
      delete [] data;
    };


};




int main()
{
  int N,A,B;
  int posi,op;
  cin>>N>>A>>B;
  mySet maze(N);
  do{
    cin>>posi>>op;
  }while(!maze.zaqiang(posi,op,A,B));
  maze.printRoute(A,B);

  return 0;
}
