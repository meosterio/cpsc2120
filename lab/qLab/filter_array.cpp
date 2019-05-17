#include <iostream>
using namespace std;

struct Node {
  int val;
  Node *next;
  Node (int v, Node *n) { val = v; next = n; }
  Node () { val = 0; next = NULL; }
};

// Return a pointer to head of the resulting list, post-insert
Node *insert_at_end(Node *head, int new_key)
{
if (head == NULL) return new Node(new_key, NULL);
head->next = insert_at_end(head->next, new_key);
return head;
}
// Return a linked list containing the even elements of array[0..N-1]
// The array is not to be modified
Node *filter_evens(int *array, int N) {
  static Node *head = NULL;
  for (int i = 0; i < N; i++) {
    if (array[i] % 2 == 0) {
      head = insert_at_end(head, array[i]);
    }
  }
  return head;
}

int main(void)
{
  int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Node *head = filter_evens(A, 10);

  /*for (int i = 0; i < 10; i++) {
    for (Node *test = head; test != NULL; test = test->next) {
      cout << test->val << "\n";
    }
  }*/
  return 0;
}
