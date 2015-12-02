#include<iostream>

using namespace std;

class myNode
{

  friend class myList;
  private:
    int data;
    myNode *next;

  public:
    myNode()
    {
      next=NULL;
    };

    myNode(int newData)
    {
      next=NULL;
      data=newData;
    };
};

class myList
{
  private:
    myNode *head;
    myNode *rear;

  public:
    myList()
    {
      head=new myNode;
      rear=head;
    };

    void insertNum(int num)
    {
      myNode *temp=head;
      while(temp->next) temp=temp->next;
      temp->next=new myNode(num);
      rear=temp->next;
    };

    void selectSort()
    {
      myNode *nowPosi=head;
      myNode *temp;
      myNode *cache;
      myNode *temp2;
      while(nowPosi->next)
      {
        temp=nowPosi;
        cache=temp;
        while(temp->next)
        {
          if(temp->next->data<cache->next->data) cache=temp;
          temp=temp->next;
        }
        temp2=cache->next;
        cache->next=cache->next->next;
        temp2->next=nowPosi->next;
        nowPosi->next=temp2;
        nowPosi=nowPosi->next;
      }
    };

    void print()
    {
      myNode *temp=head;
      while(temp->next)
      {
        temp=temp->next;
        cout<<temp->data<<' ';
      }
      cout<<endl;
    };

    ~myList()
    {
      myNode *temp;
      while(head)
      {
        temp=head;
        head=head->next;
        delete temp;
      }
    };

};


int main()
{
  int N;
  myList data;
  int temp;
  cin>>N;
  for(int i=0;i<N;i++)
  {
    cin>>temp;
    data.insertNum(temp);
  }
  data.selectSort();
  data.print();
  return 0;
}
