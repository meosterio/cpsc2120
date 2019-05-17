#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct Point {
  double x, y;
  int val;
  Point () {x = 0; y = 0; val = 0;}
};

int N = 50;
double best_len = 28379367839;
double len;

void copyArray (Point b[], Point a[]) {
  for (int i = 0; i < N; i++) {
    b[i] = a[i];
  }
}

void reverse (Point p[], int i, int j) {
  while (i<j) {
    swap(p[i], p[j]);
    i++, j--;
  }
}

double dist(Point *p, Point *q) {
  double dx = p->x - q->x;
  double dy = p->y - q->y;
  return sqrt(dx*dx + dy*dy);
}

double total_dist(Point a[]) {
  double lenn = 0;
  int j;
  for (int i = 0; i < N; i++) {
    if (i == N-1) {
      j = 0;
    }
    else {
      j = i+1;
    }
    lenn += dist(&a[i], &a[j]);
  }
  return lenn;
}

int main (void) {
  Point arr[N]; Point Best[N];
  //read in all the points
  for (int i = 0; i < N; i++) {
    cin >> arr[i].x >> arr[i].y;
  }
  //set the index of the point
  for (int i = 0; i < N; i++) {
    arr[i].val = i;
  }

  for (int t = 0; t < 100; t++) {
    //randomize the list
    for (int i = 1; i < N; i++) {
      int s = rand() % i;
      swap(arr[i], arr[s]);
    }
    //iterate through looking for better options that
    //result in a shorter total distance
    bool change = true;
    while(change) {
    change = false;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        len = total_dist(arr);
        reverse(arr, i, j);
        double test_len = total_dist(arr);
        if (test_len < len) {
          change = true;
        }
        else {
          reverse(arr, i, j);
        }
      }
    }
    }
    len = total_dist(arr);
    if (len < best_len) {
      best_len = len;
      copyArray(Best, arr);
    }
  }
  //print
  cout << "Cities:" << endl;
  for (int i = 0; i < N; i++) {
    cout << Best[i].val << endl;
  }
  cout << "Tour length: " << best_len << endl;

  return 0;

}
