#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

double checkdist (double ax, double ay, double bx, double by) {
	double ix = ax - bx;
	double iy = ay - by;
	double idist;

	idist = pow(ix,2)+pow(iy,2);
	idist = sqrt(idist);
	return idist;
}

int main(void) {

  typedef pair<double, double> Point;

  vector<Point> v;
  set<Point> s;
  double x, y;
  double D = 182873982;
  double xdist;
  int i = 0;

  while (cin >> x >> y) {
    v.push_back(Point(x,y));
  }
  sort(v.begin(), v.end());

  for (int j = 0; j < v.size(); j++) {
    double dist = 0;
    xdist = v[j].first - v[i].first;
    s.insert(Point(v[j].second, v[j].first));
    s.insert(Point(v[i].second, v[i].first));
    while (xdist > D) {
      s.erase(Point(v[i].second, v[i].first));
      i++;
      xdist = v[j].first - v[i].first;
    }
    set<Point>::iterator it;
    it = s.find(Point(v[j].second, v[j].first));
    it++;
    while (it != s.end() && (it->first - v[j].second) < D) {
      dist = checkdist(it->second, it->first, v[j].first, v[j].second);
      if (dist < D) {
        D = dist;
      }
      it++;
    }
    it = s.find(Point(v[j].second, v[j].first));
    it--;
    while (it != s.begin() && (v[j].second - it->first) < D) {
      dist = checkdist(it->second, it->first, v[j].first, v[j].second);
      if (dist < D) {
        D = dist;
      }
      it--;
    }
  }
  cout << D << endl;

  return 0;
}
