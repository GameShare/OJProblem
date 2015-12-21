#include<iostream>
#include"SCCGraph.h"


using namespace std;





int main()
{
  myGraph g(10);
  g.addEdge(0,1);
  g.addEdge(0,3);
  g.addEdge(1,2);
  g.addEdge(1,5);
  g.addEdge(2,0);
  g.addEdge(2,3);
  g.addEdge(2,4);
  g.addEdge(3,4);
  g.addEdge(5,2);
  g.addEdge(6,5);
  g.addEdge(6,7);
  g.addEdge(7,5);
  g.addEdge(7,9);
  g.addEdge(8,7);
  g.addEdge(9,8);
  g.findSCC();
  return 0;
}
