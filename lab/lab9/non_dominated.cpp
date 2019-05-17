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

typedef pair<double,double> Point;

Point flip(Point p)
{
  return make_pair(p.second, p.first);
}

int main(void)
{
  ifstream fin("points.txt");
  double x, y;
  vector<Point> V;
  set<Point> S;
  while (fin >> x >> y) V.push_back(make_pair(x,y));
  sort(V.begin(), V.end());
  for (Point p : V) {
    S.insert(flip(p));
    while (S.begin()->first < p.second)
      S.erase(S.begin());
  }
  cout << S.size() << "\n";
  return 0;
}
