#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;
const double e = 2.7182818284;
const double alpha = 0.1;

struct Point {
  double quality;
  double *data;
};

int N, D, K;
Point *P;

struct kd {
  Point point;
  kd *left;
  kd *right;
  kd (double *_key, double _q) {
    point.quality = _q;
    point.data = new double[D];
    for (int i = 0; i < D; i++) {
      point.data[i] = _key[i];
    }
    left = right = NULL;
  }
};

priority_queue< pair<double, double> > PQ;

kd *insert (kd *T, double *key, double q, int dim) {
  if (T == NULL) {
    return new kd(key, q);
  }
  if (key[dim] < T->point.data[dim]) {
    T->left = insert(T->left, key, q, (dim+1)%D);
  }
  else {
    T->right = insert(T->right, key, q, (dim+1)%D);
  }
  return T;
}

double checkdist (double *ax, double *bx) {
  double ddist = 0;
  for (int i = 0; i < D; i++) {
	  double ix = ax[i] - bx[i];
	  double idist = 0;
	  idist = pow(ix,2);
    ddist+=idist;
  }
  ddist = sqrt(ddist);
	return ddist;
}

void nn_search(kd *T, Point &point, int dim) {
  if (T==NULL) return;
  double dd = (checkdist(point.data, T->point.data));
  if (dd != 0) {
    if (PQ.size() < K) {
      PQ.push(make_pair(dd, T->point.quality));
    }
    else {
      if (dd < PQ.top().first) {
        PQ.pop();
        PQ.push(make_pair(dd, T->point.quality));
      }
    }
  }
  if (point.data[dim] < T->point.data[dim]) {
    nn_search(T->left, point, (dim+1)%D);
    if ((T->point.data[dim] - point.data[dim]) < PQ.top().first) {
      nn_search(T->right, point, (dim+1)%D);
    }
  }
  else {
    nn_search(T->right, point, (dim+1)%D);
    if ((point.data[dim] - T->point.data[dim]) < PQ.top().first) {
      nn_search(T->left, point, (dim+1)%D);
    }
  }
  return;
}

int main(int argc, char *argv[])  {
  if (argc != 3) {
    cout << "Usage: wine <data file> <k>\n";
    return 0;
  }

  /* Read input data */
  ifstream fin(argv[1]);
  K = atoi(argv[2]);
  fin >> N >> D;
  P = new Point[N];
  for (int i=0; i<N; i++) {
    fin >> P[i].quality;
    P[i].data = new double[D];
    for (int j=0; j<D; j++) {
      fin >> P[i].data[j];
    }
  }
  fin.close();

  /* Normalize data in each coordinate */
  for (int j=0; j<D; j++) {
    double mean = 0.0;
    for (int i=0; i<N; i++) mean += P[i].data[j];
    mean /= N;
    for (int i=0; i<N; i++) P[i].data[j] -= mean;
    double var = 0.0;
    for (int i=0; i<N; i++) var += pow(P[i].data[j],2);
    double stddev = sqrt(var/N);
    for (int i=0; i<N; i++) P[i].data[j] /= stddev;
  }
  // Now in each coordinate, we have a mean of zero and variance/standard deviation
  // of one, so the data set is "centered" at the origin and has the same relative
  // scale along each axis (so no attribute is "more important" than any other
  // attribute when computing distances).

  kd *T = NULL;
  random_shuffle(&P[0], &P[N]);
  for (int i = 0; i < N; i++) {
    T = insert(T, P[i].data, P[i].quality, 0);
  }

  double testa = 376373;
  for (int i = 0; i < K; i++) {
    PQ.push(make_pair(testa, testa/2));
    testa+=8648;
  }

  double Serror = 0;
  for (int i = 0; i < N; i++) {
    nn_search(T, P[i], 0);
    double gq = 0;
    double sumT = 0;
    double sumB = 0;
    double weight = 0;
    while (!PQ.empty()) {
      weight = pow(e, (-alpha * PQ.top().first));
      sumB += weight;
      weight = weight * PQ.top().second;
      sumT += weight;
      PQ.pop();
    }
    if (sumB!=0) {
      gq = sumT/sumB;
      Serror += ((P[i].quality - gq) * (P[i].quality - gq));
    }
  }

  Serror = Serror/((double)N);
  cout << Serror << endl;

  return 0;
}
