#include <iostream>
#include <set>

class LinkedListNode {
public:
  int data;
  LinkedListNode *next;
  LinkedListNode(int d){
    data = d;
    next = NULL;
  }
};

void DeleteDuplicate(LinkedListNode *head){
  std::set<int > table;
  LinkedListNode *node = head;
  if (node==NULL) return;
  table.insert(head->data); // use insert for setting value for set object
  while(node->next!=NULL){
    if (table.find(node->next->data)!=table.end()){
      // Find value in table. Skip node->next from node list
      printf("skip %d\n", node->next->data);
      node->next = node->next->next; // In this case, we don't have to move next node and keep the same node
    } else {
      table.insert(node->next->data);
      node=node->next;
    }
  }
  return;
}

void PrintLinkedList(LinkedListNode* head){
  LinkedListNode* node = head;
  while(node!=NULL){
    std::cout << node->data << std::endl;
    node = node->next;
  }
  return;
}

int main(){
  LinkedListNode *node = new LinkedListNode(3);
  LinkedListNode* head = node;
  LinkedListNode* add1 = new LinkedListNode(4); node->next = add1; node = node->next;
  LinkedListNode* add2 = new LinkedListNode(5); node->next = add2; node = node->next;
  LinkedListNode* add3 = new LinkedListNode(6); node->next = add3; node = node->next;
  LinkedListNode* add4 = new LinkedListNode(3); node->next = add4; node = node->next;
  LinkedListNode* add5 = new LinkedListNode(4); node->next = add5; node = node->next;
  LinkedListNode* add6 = new LinkedListNode(7); node->next = add6; node = node->next;
  std::cout << "===============" << std::endl;
  PrintLinkedList(head);
  DeleteDuplicate(head);  
  std::cout << "===============" << std::endl;
  PrintLinkedList(head);
  
  return 0;
}
