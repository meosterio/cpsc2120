// This is a sketch you can use for your "bad1" .. "bad3" programs...

#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;

struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = NULL; }
};

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert value v at rank r
Node *insert(Node *T, int v, int r)
{
  if (T==NULL) return new Node(v);
  int ror = T->left ? T->left->size : 0;
  if (r <= ror) T->left = insert(T->left, v, r);
  else T->right = insert (T->right, v, r-ror-1);
  fix_size(T);
  return T;
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=NULL && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    cout << "Usage: bad1 <input size>\n";
    return 0;
  }

  int N = atoi(argv[1]);  // get first command-line argument
  if (N<1 || N>100000) {
    cout << "Invalid input size!\n";
    return 0;
  }

  // Generate and print bad input of size N for prog1
  cout << N << "\n";
  int j = N;
  int hold;
  Node *T = NULL;
  for (int i=1; i<=N; i++) {
	 hold = 123456789 % i;
    T = insert(T, j, hold);
    j--;
  }
  for (int i = 0; i < N; i++) {
    cout << select(T, i)->key << endl;
  }
  return 0;
}
