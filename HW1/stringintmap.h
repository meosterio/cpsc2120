#ifndef STRINGINTMAP_H /* Prevent multiple inclusion... */
#define STRINGINTMAP_H

#include <string>
using namespace std;

struct Node {
  string key;
  int count;
  Node *next;
  Node(string k, Node *n, int c) { key = k; next = n; count = c; }
  Node() { key = ""; next = NULL; count = 0; }
};

class StringIntMap {

 private: 
  Node **table;  // array of pointers to linked lists
  int size;      // size of table, as currently allocated
  int num_elems; // number of elements stored in the tabl

 public:
  StringIntMap();
  ~StringIntMap();
  int &operator[] (string key); 
  bool find(string key); 
  void insert(string key); 
  void remove(string key);
  void print(void);
};

#endif
