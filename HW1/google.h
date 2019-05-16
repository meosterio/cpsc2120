#ifndef GOOGLE_H /* Prevent multiple inclusion... */
#define GOOGLE_H

#include <string>
using namespace std;

struct Wordstable {
  string key;
  Wordstable *next;
  Wordstable (string k, Wordstable *n) { key = k; next = n; }
  Wordstable () {key = "BAD1"; next = NULL; }
};

struct Linkstable {
  string key;
  int isPres;
  double weight1;
  double new_weight1;
  Linkstable *next;
  Linkstable (string k, Linkstable *n, double w1, double nw1, int iP) { key = k;
    next = n; weight1 = w1; new_weight1 = nw1; isPres = iP; }
  Linkstable () {key = "BAD"; next = NULL; weight1 = 0; new_weight1 = 0; isPres = 0; }
};

struct Node {
  Wordstable *word;
  Linkstable *link;
  string key;
  double linkCount;
  double weight;
  double new_weight;
  Node(string k, double w, double nw) { key = k; weight = w; new_weight = nw; }
  Node() {key = ""; weight = 0; new_weight = 0; }
};

struct WrdInvert {
  string key;
  Linkstable *link;
  WrdInvert(string k) { key = k; }
  WrdInvert() {key = ""; }
};

class PageSet {

 private:
  Node **table;  // array of pointers to linked lists
  int size;      // size of table, as currently allocated
  int num_elems; // number of elements stored in the table

 public:
  PageSet();
  ~PageSet();
  int &operator[] (string key);
  void insert(string key);
};

#endif
