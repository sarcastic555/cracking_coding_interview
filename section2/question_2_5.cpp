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
  LinkedListNode(){
    next = NULL;
  }
  void SetNext(int d){
    LinkedListNode *next_node = new LinkedListNode(d);
    next = next_node;
    return;
  }
};

void PrintLinkNodeList(LinkedListNode* head){
  LinkedListNode* node = head;
  while(node!=NULL){
    std::cout << node->data << std::endl;
    node = node->next;
  }
  return;
}

// Treat 7->1->6 as 617, and 5->9->2->1 as 1295
// while loop version
LinkedListNode* CalculateSum1(LinkedListNode* head1, LinkedListNode* head2){
  // ==== move initial execution outside of while loop for constructor definition ==== //
  LinkedListNode *node = new LinkedListNode((head1->data + head2->data)%10);
  LinkedListNode *head = node;
  int carry = (head1->data + head2->data) / 10;
  head1 = head1->next;
  head2 = head2->next;
  // ============== //
  while(head1!=NULL || head2!=NULL){
    int sum = carry;
    if (head1!=NULL) {
      sum += head1->data;
      head1 = head1->next; // set head1 moving inside if loop to avoid null pointer accessing
    }
    if (head2!=NULL) {
      sum += head2->data;
      head2 = head2->next;
    }
    carry = sum / 10;
    node->SetNext(sum % 10);
    node = node->next;
  }
  return head;
}

// Treat 7->1->6 as 617, and 5->9->2->1 as 1295
// Recursive version
LinkedListNode* CalculateSum2(LinkedListNode* node1, LinkedListNode* node2, int carry){
  if (node1==NULL && node2==NULL){
    return NULL;
  }
  int value = carry;
  if (node1 != NULL) { 
    value += node1->data;
    node1 = node1->next;
  }
  if (node2 != NULL) { 
    value += node2->data;
    node2 = node2->next;
  }
  carry = value / 10;
  LinkedListNode *sum = new LinkedListNode(value % 10);
  LinkedListNode *more = CalculateSum2(node1, node2, carry);
  sum->next = more;
  return sum;
}

LinkedListNode* InsertBefore(LinkedListNode* node, int value){
  LinkedListNode *out = new LinkedListNode(value);
  if (node==NULL) { return out; }
  else {
    out->next = node;
    return out;
  }
}

// Treat 7->1->6 as 716, and 5->9->2->1 as 5921
// Recursive version
struct SumSet {
  LinkedListNode* out_pointer; // This parameter is expressed as "sum" in the textbook
  int carry;
};

int GetLinkedNodeLength(LinkedListNode* head){
  int counter = 0;
  while(head!=NULL){
    head = head->next;
    counter++;
  }
  return counter;
}

// Make return value as pointer to return head node
LinkedListNode* AlignLinkedNodeLength(LinkedListNode* head, int size){
  int lsize = GetLinkedNodeLength(head);
  if (lsize >=size){
    return head;
  } else {
    LinkedListNode* node = head;
    for (int i=0; i<size-lsize; i++){
      LinkedListNode* zero = new LinkedListNode(0);
      zero->next = node; // Update pointer to one step back
      node = zero;
    }
    return node;
  }
}

SumSet CalculateSum3(LinkedListNode* node1, LinkedListNode* node2){
  if (node1==NULL && node2==NULL){
    SumSet ret;
    ret.out_pointer = NULL;
    ret.carry = 0;
    return ret;
  }
  SumSet result = CalculateSum3(node1->next, node2->next);
  int total = node1->data + node2->data + result.carry;
  SumSet result_up;
  result_up.out_pointer = InsertBefore(result.out_pointer, total % 10);
  result_up.carry = total / 10;

  return result_up;
}

int main(){
  LinkedListNode *node = new LinkedListNode(7);
  LinkedListNode* head = node;
  LinkedListNode* add1 = new LinkedListNode(1); node->next = add1; node = node->next;
  LinkedListNode* add2 = new LinkedListNode(6); node->next = add2; node = node->next;
 
  LinkedListNode *node2 = new LinkedListNode(5);
  LinkedListNode* head2 = node2;
  LinkedListNode* add3 = new LinkedListNode(9); node2->next = add3; node2 = node2->next;
  LinkedListNode* add4 = new LinkedListNode(2); node2->next = add4; node2 = node2->next;
  LinkedListNode* add5 = new LinkedListNode(9); node2->next = add5; node2 = node2->next;
  
  // Case1: While loop
  //  LinkedListNode *sum = CalculateSum(head, head2);

  // Case2: Utilize recursive function
  //LinkedListNode *sum = CalculateSum2(head, head2, 0);
  
  // Case3: Reverse case (advanced problem)
  head = AlignLinkedNodeLength(head, std::max(GetLinkedNodeLength(head), GetLinkedNodeLength(head2)));
  head2 = AlignLinkedNodeLength(head2, std::max(GetLinkedNodeLength(head), GetLinkedNodeLength(head2)));
  SumSet ret = CalculateSum3(head, head2);
  LinkedListNode *sum = ret.out_pointer;
  if (ret.carry==1){
    sum = InsertBefore(sum, 1);
  }
  // This is the carry flag manipulation. Do not put this statement inside CalculateSum3 because this should be executed only once.

  // Case1~3: Output result
  PrintLinkNodeList(sum);

  return 0;
}
