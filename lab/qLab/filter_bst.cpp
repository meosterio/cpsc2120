#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
using namespace std;

struct Node {
  int key;
  int size;
  Node *left, *right;
  Node (int k, Node *l, Node *r) { key = k; left = l; right = r; size = 1; }
  Node (int k) { key = k; left = right = NULL; size = 1; }
  Node () { key = 0; left = right = NULL; size = 1; }
};

// Return a balanced BST containing the even elements of the input BST
// (which you can assume is balanced).  Odd elements should be de-allocated,
// so only one copy of each even element should reside in memory at the
// end of this function's execution
Node *filter_evens(Node *root)
{
  if (root == NULL) return;
  filter_evens(root->left);
  if (root->key % 2 == 1) {
    remove(&root, root->key);
  }
  filter_evens(root->right);
}

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == NULL) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}

// prints out the inorder traversal of T (i.e., the contents of T in sorted order)
void print_inorder(Node *T)
{
  if (T == NULL) return;
  print_inorder(T->left);
  cout << T->key << "\n";
  print_inorder(T->right);
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
  assert(T != NULL);
  if (k == T->key) {
    Node *to_delete = T;
    T = join(T->left, T->right);
    delete to_delete;
    return T;
  }
  if (k < T->key) T->left = remove(T->left, k);
  else T->right = remove(T->right, k);
  fix_size(T);
  return T;
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.
Node *join(Node *L, Node *R)
{
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
  if (L == NULL) return R;
  if (R == NULL) return L;
  int random = rand() % (L->size + R->size);
  if (random < L->size) {
    // L stays root
    L->right = join(L->right, R);
    fix_size(L);
    return L;
  } else {
    // R stays root
    R->left = join(L, R->left);
    fix_size(R);
    return R;
  }
}

int main(void)
{
  int A[10];

  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);

  // insert contents of A into a BST
  Node *T = NULL;
  for (int i=0; i<10; i++) T = insert(T, A[i]);

  T = filter_evens(T);

  print_inorder(T);




  return 0;
}
