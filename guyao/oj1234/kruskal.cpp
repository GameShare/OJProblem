#include<iostream>

using namespace std;

class myNode
{
    friend class myGraph;
    private:
        myNode *next;
        int data;
    public:
        myNode(int newdata)
        {
          data=newdata;
          next=NULL;
        };

};



class myGraph
{
    private:
        myNode **data;
        int vnum;
        int *marks;

    public:


};






int main()
{
    return 0;
}
