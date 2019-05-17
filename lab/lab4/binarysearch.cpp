#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

struct Node {
	int key;
	Node *left;
  Node *right
	Node (k) { key = k; }
	Node () { key = 0; left = right = NULL; }
};

void inorder(Node *T) {
  if (T == NULL) return;
  inorder(T->left);
  cout << T->key << endl;
  inorder (T->right);
}

int main (void) {
  Node *T = NULL;
  int A[20];
  int x;
  for (x = 0; x < 20; x++) {
    A[x] = rand() % 10000;
  }
  inorder(T);
  return 0;
}
