// p109
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <deque>

class Node {
private:
  int data;
  Node *next; // Define pointer
public:
  Node(int d){ // Set integer argument for constructor
    data=d;
    next = NULL; // Segmentation fault occurs without this initialization
  }
  int GetValue(){
    return data;
  }

  Node* GetNextNode(){
    return next;
  }

  void AppendValue(int value){
    Node *end = new Node(value);
    Node *n = this; // set "this" pointer as initial value
    while(n->next!=NULL){
      n=n->next;
    }
    n->next=end;
    delete end;
    return;
  }
};

int main(){
  Node hoge(3);
  hoge.AppendValue(4);
  std::cout << hoge.GetValue() << std::endl; // 3
  Node *next = hoge.GetNextNode();
  std::cout << next->GetValue() << std::endl; // 4
  return 0;
}
