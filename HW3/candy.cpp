#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <assert.h>

using namespace std;

struct Node {
  int taste;
  int weight;
  double tastevsweight;
  int size;
  Node *left;
  Node *right;
  Node (int t, int w, double tvw) { taste = t; weight = w; tastevsweight = tvw; size = 1; left = right = NULL; }
};

struct Bag {
  int taste;
  int weight;
  double tastevsweight;
  Bag () {taste = 0; weight = 0; tastevsweight = 0; }
};

void fix_size(Node *T){
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

Node *insert(Node *T, int t, int w, double tvw){
  if (T == NULL) return new Node(t, w, tvw);
  if (tvw > T->tastevsweight) T->left = insert(T->left, t, w, tvw);
  else T->right = insert(T->right, t, w, tvw);
  fix_size(T);
  return T;
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r){
  assert(T!=NULL && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

int N;

void greedy (Node *T, int wa, int wb, int wc) {
  double tasty = 0;
  int i;
  int hold[N];
  for (int i = 0; i < N; i++) {
    hold[i] = 20;
  }
  Node *temp = NULL;
  for (int i = 0; i < N; i++) {
    temp = select(T, i);
    if (temp->weight < wa && hold[i] == 20) {
      tasty += temp->taste;
      wa -= temp->weight;
      hold[i] = i;
    }
  }
  for (int i = 0; i < N; i++) {
    temp = select(T, i);
    if (temp->weight < wb && hold[i] == 20) {
      tasty += temp->taste;
      wb -= temp->weight;
      hold[i] = i;
    }
  }
  for (int i = 0; i < N; i++) {
    temp = select(T, i);
    if (temp->weight < wc && hold[i] == 20) {
      tasty += temp->taste;
      wc -= temp->weight;
    }
  }
  cout << "Greedy: " << tasty << endl;
}

int max (int i, int j) {return (i > j)? i : j; }

void resetTest(int test[]) {
  for (int k = 0; k < N; k++) {
    test[k] = 20;
  }
}

int calcTaste(Bag p[], int test[], int w) {
  int taste = 0;
  for (int k = 0; k < N; k++) {
    int q = 0;
    int hold = 0;
    for (int y = 0; y < N; y++) {
      if (p[y].tastevsweight > hold && test[y] != 20) {
        hold = p[y].tastevsweight;
        q = y;
      }
    }
    test[q] = q;
    if (w + p[q].weight <= 2000) {
      w += p[q].weight;
      taste += p[q].taste;
    }
  }
  return taste;
}

int ut = 0;
int bt = 0;
int bst = 0;
int Wa = 0;
int Wb = 0;
int Wc = 0;
void prune (Bag *pls, int C, int l) {
  if (bt > bst) {
    bst = bt;
  }
  if (C == l) {
    return;
  }
  if (pls[C].weight + Wa <= 2000) {
    Wa += pls[C].weight;
    bt += pls[C].taste;
    prune(pls, C+1, l);
    Wa -= pls[C].weight;
    bt -= pls[C].taste;
  }
  if (pls[C].weight + Wb <= 2000) {
    Wb += pls[C].weight;
    bt += pls[C].taste;
    prune(pls, C+1, l);
    Wb -= pls[C].weight;
    bt -= pls[C].taste;
  }
  if (pls[C].weight + Wc <= 2000) {
    Wc += pls[C].weight;
    bt += pls[C].taste;
    prune(pls, C+1, l);
    Wc -= pls[C].weight;
    bt -= pls[C].taste;
  }
  ut += pls[C].taste;
  prune(pls, C+1, l);
  ut -= pls[C].taste;
}

int main (void) {
  Node *T = NULL;
  Node *temp = NULL;
  int taste, weight;
  double tvw;
  int count = 0;
  while (cin >> weight >> taste) {
    tvw = ((double)taste/(double)weight);
    T = insert(T, taste, weight, tvw);
    count +=1;
  }
  N = count;
  Bag a[N];
  Bag b[N];
  Bag c[N];

  greedy(T, 2000, 2000, 2000);

  //iterative iterative iterative iterative iterative iterative iterative
  for (int k = 0; k < N; k++) {
    temp = select(T, k);
    a[k].taste = temp->taste;
    a[k].weight = temp->weight;
    a[k].tastevsweight = temp->tastevsweight;
  }
  int best = 0;
  for (int t = 0; t < 1000; t++) {
    //random assignment of candy to bags
    for (int k = 1; k < N; k++){
      int s = rand() % k;
      swap(a[k], b[s]);
      swap(a[s], c[k]);
    }
    int tastiness = 0;
    int wa = 0;
    int wb = 0;
    int wc = 0;
    int test[N];
    int hold = 2000;
    bool change = true;
    while(change) {
    change = false;
    for (int k = 0; k < N; k++) {
        int taste = 0;
        wa = 0;
        wb = 0;
        wc = 0;
        int i = 0;
        while (b[i].weight != 0) {
          i++;
        }
        swap(a[k], b[i]);
        resetTest(test);
        taste += calcTaste(a, test, wa);
        resetTest(test);
        taste += calcTaste(b, test, wb);
        resetTest(test);
        taste += calcTaste(c, test, wc);
        if (taste > tastiness) {
          tastiness = taste;
          change = true;
        }
        else {
          swap(a[k], b[i]);
        }
    }
    if (tastiness > best) {
      best = tastiness;
    }
  }
    change = true;
    while(change) {
    change = false;
    hold = 2000;
    for (int k = 0; k < N; k++) {
        int taste = 0;
        wa = 0;
        wb = 0;
        wc = 0;
        int i = 0;
        while (c[i].weight != 0) {
          i++;
        }
        swap(a[k], c[i]);
        resetTest(test);
        taste += calcTaste(a, test, wa);
        resetTest(test);
        taste += calcTaste(b, test, wb);
        resetTest(test);
        taste += calcTaste(c, test, wc);
        if (taste > tastiness) {
          tastiness = taste;
          change = true;
        }
        else {
          swap(a[k], c[i]);
        }
    }
    if (tastiness > best) {
      best = tastiness;
    }
  }
  change = true;
  while(change) {
    change = false;
    hold = 2000;
    for (int k = 0; k < N; k++) {
        int taste = 0;
        wa = 0;
        wb = 0;
        wc = 0;
        int i = 0;
        while (c[i].weight != 0) {
          i++;
        }
        swap(b[k], c[i]);
        resetTest(test);
        taste += calcTaste(a, test, wa);
        resetTest(test);
        taste += calcTaste(b, test, wb);
        resetTest(test);
        taste += calcTaste(c, test, wc);
        if (taste > tastiness) {
          tastiness = taste;
          change = true;
        }
        else {
          swap(b[k], c[i]);
        }
    }
    if (tastiness > best) {
      best = tastiness;
    }
  }
  change = true;
  while(change) {
  change = false;
  hold = 2000;
  for (int k = 0; k < N; k++) {
      int taste = 0;
      wa = 0;
      wb = 0;
      wc = 0;
      int i = 0;
      while (a[i].weight != 0) {
        i++;
      }
      swap(b[k], a[i]);
      resetTest(test);
      taste += calcTaste(a, test, wa);
      resetTest(test);
      taste += calcTaste(b, test, wb);
      resetTest(test);
      taste += calcTaste(c, test, wc);
      if (taste > tastiness) {
        tastiness = taste;
        change = true;
      }
      else {
        swap(b[k], a[i]);
      }
  }
  if (tastiness > best) {
    best = tastiness;
  }
  }
  change = true;
  while(change) {
  change = false;
  hold = 2000;
  for (int k = 0; k < N; k++) {
      int taste = 0;
      wa = 0;
      wb = 0;
      wc = 0;
      int i = 0;
      while (a[i].weight != 0) {
        i++;
      }
      swap(c[k], a[i]);
      resetTest(test);
      taste += calcTaste(a, test, wa);
      resetTest(test);
      taste += calcTaste(b, test, wb);
      resetTest(test);
      taste += calcTaste(c, test, wc);
      if (taste > tastiness) {
        tastiness = taste;
        change = true;
      }
      else {
        swap(c[k], a[i]);
      }
  }
  if (tastiness > best) {
    best = tastiness;
  }
  }
  change = true;
  while(change) {
  change = false;
  hold = 2000;
  for (int k = 0; k < N; k++) {
      int taste = 0;
      wa = 0;
      wb = 0;
      wc = 0;
      int i = 0;
      while (b[i].weight != 0) {
        i++;
      }
      swap(c[k], b[i]);
      resetTest(test);
      taste += calcTaste(a, test, wa);
      resetTest(test);
      taste += calcTaste(b, test, wb);
      resetTest(test);
      taste += calcTaste(c, test, wc);
      if (taste > tastiness) {
        tastiness = taste;
        change = true;
      }
      else {
        swap(c[k], b[i]);
      }
  }
  if (tastiness > best) {
    best = tastiness;
  }
  }
  }
    cout << "Iterative: " << best << endl;
  //iterative iterative iterative iterative iterative iterative iterative

  //Pruned Pruned Pruned Pruned Pruned Pruned Pruned Pruned Pruned Pruned
  int C = 0;
  int l = N;
  Bag pls[N];
  for (int i = 0; i < N; i++) {
    temp = select(T, i);
    pls[i].weight = temp->weight;
    pls[i].taste = temp->taste;
  }
  prune(pls, C, l);
  cout << "Pruned: " << bst << endl;
  //Pruned Pruned Pruned Pruned Pruned Pruned Pruned Pruned Pruned Pruned
  return 0;
}
