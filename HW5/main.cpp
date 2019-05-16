#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct Place {
  double x, y;
  string name;
  Place (double _x, double _y, string _name) {
    x = _x;
    y = _y;
    name = _name;
  }
  Place () {};
};

vector<Place> lm;
vector<Place> rt;
int x[100][100];
int y[100][100];

double dist(Place *p, Place *q) {
  double dx = p->x - q->x;
  double dy = p->y - q->y;
  return sqrt(dx*dx + dy*dy);
}

void minD(double **t) {
  for (int row = 1; row < lm.size(); row++) {
    for (int col = 1; (col <= row) && (col < rt.size()); col++) {
      double d1 = t[row-1][col] + dist(&lm[row], &lm[row-1]);
      double d2 = t[row-1][col-1] + dist(&lm[row-1], &rt[col - 1]) + dist(&lm[row], &rt[col-1]);
      if (d1 < d2) {
        t[row][col] = d1;
        x[row][col] = row-1;
        y[row][col] = col;
      }
      else {
        t[row][col] = d2;
        x[row][col] = row-1;
        y[row][col] = col-1;
      }
    }
  }
}

void printpath(int gc, int gr) {
  if (gc > 0 || gr > 0) {
    printpath(x[gc][gr], y[gc][gr]);
    cout<<lm[x[gc][gr]].name<<" "<<lm[x[gc][gr]].x<<" "<<lm[x[gc][gr]].y<<endl;
    if (y[gc][gr] != gr) {
      cout<<rt[y[gc][gr]].name<<" "<<rt[y[gc][gr]].x<< " " << rt[y[gc][gr]].y << endl;
    }
  }
}

int main (void) {

  ifstream locations("landmarks.txt");
  string s;
  double x1, y1;
  while (locations >> s >> x1 >> y1) {
    lm.push_back({x1, y1, s});
  }
  locations.close();

  ifstream rest("restaurants.txt");
  while (rest >> s >> x1 >> y1) {
    rt.push_back({x1, y1, s});
  }
  rest.close();

  sort(lm.begin(), lm.end(), [](const Place& a, const Place& b) {
    return a.name < b.name;
  });

  sort(rt.begin(), rt.end(), [](const Place& a, const Place& b) {
    return a.name < b.name;
  });
  //dummy first restaurant
  rt.push_back({rt[0].x, rt[0].y, rt[0].name});

  //array of distances for each location in graph
  double **t;
  t = new double *[lm.size()];
  for (int i = 0; i < lm.size(); i++) {
    t[i] = new double[rt.size()];
  }

  double INF = 367536753;
  for (int i = 0; i < lm.size(); i++) {
    for (int j = 0; j < rt.size(); j++) {
      t[i][j] = INF;
    }
  }
  t[0][0] = 0;

  //initialize the distances for the first column
  double dd = 0;
  for (int i = 1; i < lm.size(); i++) {
    dd += dist(&lm[i], &lm[i-1]);
    t[i][0] = dd;
  }

  minD(t);

  int gc = (lm.size()-1);
  int gr = (rt.size()-1);
  printpath(gc, gr);

  //print the last element in the path
  cout << lm[gc].name << " " << lm[gc].x << " " << lm[gc].y << endl;

  cout << "Total tour distance: " << t[gc][gr] << endl;

  return 0;
}
