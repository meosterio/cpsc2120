#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

int A, B, X;
bool visited[1001][1001];
string steps[1001][1001];
int ap[1001][1001];
int bp[1001][1001];

void search (int a, int b, int oa, int ob, string s) {
  if (visited[a][b]) {
    return;
  }
  else {
    visited[a][b] = true;
  }
  ap[a][b] = oa;
  bp[a][b] = ob;
  steps[a][b] = s;
  //fillA
  search(A, b, a, b, "Fill A");
  //fillB
  search(a, B, a, b, "Fill B");
  //EmptyA
  search(0, b, a, b, "Empty A");
  //EmptyB
  search(a, 0, a, b, "Empty B");
  //Pour(a->b)
  oa = a;
  ob = b;
  b += a;
  a = 0;
  while (b > B) {
    b-=1;
    a+=1;
  }
  search(a, b, oa, ob, "Pour A->B");
  //Pour(b->a)
  oa = a;
  ob = b;
  a += b;
  b = 0;
  while (a > A) {
    a-=1;
    b+=1;
  }
  search(a, b, oa, ob, "Pour B->A");
}

void printSteps (int a, int b) {
  if (steps[a][b] != "HOLD") {
    printSteps(ap[a][b], bp[a][b]);
    cout << setw(10) << steps[a][b] << " " << "[a = " << a << ", b = " << b << "]" << endl;
  }
}

int main (void) {

  cout << "Enter A: ";
  cin >> A;
  cout << "Enter B: ";
  cin >> B;
  cout << "Enter X: ";
  cin >> X;

  search (0, 0, 0, 0, "HOLD");

  bool works = false;
  for (int i = 0; i < 1001; i++) {
    if (!works) {
      for (int j = 0; j < 1001; j++) {
        if (!works) {
          if (i + j == X && visited[i][j] == true) {
            printSteps(i, j);
            works = true;
          }
        }
      }
    }
  }
  if (!works) {
    cout << "Impossible!" << endl;
  }

  return 0;
}
