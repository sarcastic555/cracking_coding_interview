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
public:
  int data;
  Node *next; // Define pointer
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
    //delete end; // this delete should not be executed
    return;
  }

};

Node* DeleteNode(Node* head, int value){
  // Change head position when value matches at first node
  if (head==NULL){
    return head;
  } else {
    // Following is my original version. Need to define prev & node
    /*Node *node = head;
    Node *prev = head;
    if (node->data==value){
      return node->next;
    }
    while(node!=NULL){
      if (node->data==value){
        prev->next = node->next;
        break;
      }
      prev = node;
      node = node->next;
      }*/
    // This is the more simple way with only one variable defined
    Node *node = head;
    while(node->next!=NULL){
      if (node->next->data==value){
        node->next = node->next->next;
        break;
      }
      node = node->next;
    }
    return head;
  }
}

int main(){
  Node *hoge = new Node(3);
  Node *head = hoge;
  hoge->AppendValue(4);
  hoge->AppendValue(5);
  hoge->AppendValue(6);
  hoge->AppendValue(7);
  while(hoge!=NULL){
    std::cout << hoge->data << std::endl; // 3, 4, 5, 6, 7
    hoge = hoge->next;
  }

  // Delete node
  DeleteNode(head, 5);
  hoge=head;
  while(hoge!=NULL){
    std::cout << hoge->data << std::endl; // 3, 4, 6, 7
    hoge = hoge->next;
  }
  return 0;
}
