#include <iostream>
#include <algorithm>
using namespace std;

const int max_size = 1000000;
int A[max_size], N = 0;

int parent(int i) { return (i-1)/2; }
int lchild(int i) { return 2*i+1; }
int rchild(int i) { return 2*i+2; }

void sift_up(int i) {
  while (i>0 && A[i] < A[parent(i)]) {
    swap(A[i], A[parent(i)]);
    i = parent(i);
  }
}

void sift_down(int i) {
  int smallest_child = i;
  if (lchild(i) < N && A[lchild(i)] < A[i])
    smallest_child = lchild(i);
  if (rchild(i) < N && A[rchild(i)] < A[smallest_child])
    smallest_child = rchild(i);
  if (smallest_child != i) {
    swap (A[i], A[smallest_child]);
    sift_down(smallest_child);
  }
}

void insert(int key) {
  A[N] = key;
  sift_up(N);
  N++;
}

int remove_min(void) {
  swap(A[0], A[N-1]);
  N--;
  sift_down(0);
  return A[N];
}

int main (void) {
  for (int i = 0; i < 1000000; i++) {
    insert(rand());
  }
  for (int i = 0; i < 1000000; i++) {
    cout << remove_min() << endl;
  }

  return 0;
}
