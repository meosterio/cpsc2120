#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>
using namespace std;

struct Point {
  double x, y;
};


bool operator< (Point p, Point q)
{
  return p.x < q.x;
}


// Usually pass vectors and other large objects
// as references or pointers instead of by value,
// to avoid copying them all over the place
void print_vector(vector<int> &V)
{
  for (auto val : V) {
    cout << val << "\n";
  }
}

int main(void)
{
  // PAIRS
  pair<string,int> z = make_pair("string", 17);
  cout << z.first << " " << z.second << "\n";

  // STACKS
  stack<int> S;
  for (int i=1; i<=10; i++)
    S.push(i);
  while (!S.empty()) {
    cout << S.top() << "\n";
    S.pop();
  }

  cout << "\n";

  // QUEUES
  queue<int> Q;
  for (int i=1; i<=10; i++)
    Q.push(i);
  while (!Q.empty()) {
    cout << Q.front() << "\n";
    Q.pop();
  }

  cout << "\n";

  // PRIORITY QUEUES
  priority_queue<int> PQ;
  for (int i=1; i<=10; i++)
    PQ.push(-(rand() % 1000000));
  while (!PQ.empty()) {
    cout << -PQ.top() << "\n";
    PQ.pop();
  }

  cout << "\n";

  // VECTORS
  //  vector<vector<int>> V(10, vector<int>(10));
  vector<int> V;
  for (int i=20; i>=11; i--)
    V.push_back(i);

  for (int i=0; i<V.size(); i++)
    cout << V[i] << "\n";

  cout << "\n";

  sort (V.begin(), V.end());

  // Can sort regular arrays too!...
  int A[] = {3,5,1,5,1,2,6,3};
  sort (A, A+8);

  for (vector<int>::iterator it = V.begin(); it != V.end(); it++)
    cout << *it << "\n";

  cout << "\n";

  // Or, for simplicity... (c++11 only)
  for (auto it = V.begin(); it != V.end(); it++)
    cout << *it << "\n";

  cout << "\n";

  // Or, for even more simplicity... (c++11 only)

  // Compare to  for (auto val : V) {
  for (auto &val : V) {
    cout << val << "\n";
    val = 7;
  }

  cout << "\n";

  // Or, for even more simplicity... (c++11 only)
  for (auto val : V) {
    cout << val << "\n";
  }

  cout << "\n";

  print_vector(V);

  // SETS
  set<int> BST;
  for (int i=1; i<=10; i++)
    BST.insert(rand() % 1000000);
  BST.insert(17);
  cout << "There are " << BST.count(17) << " 17s in the structure\n";
  if (BST.find(17) != BST.end())  {
    // BST.erase(17);
    BST.erase(BST.find(17));
    cout << "17 present, but don't worry, I killed it\n";
  }
  else
    cout << "17 not present!\n";

  // Be sure to define <
  set<Point> does_it_work;
  Point p = {1,2};
  does_it_work.insert(p);

  cout << "\n";

  for (set<int>::iterator it = BST.begin(); it != BST.end(); it++)
    cout << *it << "\n";

  cout << "\n";

  for (set<int>::iterator it = BST.begin(); it != BST.end(); it++)
    cout << *it << "\n";

  set<int>::iterator it = BST.end();
  it--;

  for (; it != BST.begin(); it--)
    cout << *it << "\n";

  // MAPS
  map<string,int> grade;
  grade["Brian"] = 100;
  grade["Andre"] = 99;
  grade["James"] = 0x101;
  ifstream fin("students.txt");
  string fname, lname;
  map<string,int> counts;
  while (fin >> fname >> lname) {
    counts[fname]++;
  }

  cout << "\n";

  for (map<string,int>::iterator x = grade.begin(); x != grade.end(); x++)
    cout << x->first << ": " << x->second << "\n";

  cout << "\n";

  for (auto x = grade.begin(); x != grade.end(); x++)
    cout << x->first << ": " << x->second << "\n";

  cout << "\n";

  for (const auto &x: grade) {
    cout << x.first << ": " << x.second << "\n";
    //    x.second = 2;
  }

  cout << "\n";

  for (auto x : grade)
    cout << x.first << ": " << x.second << "\n";

  return 0;
}
