/*	Alex Moore
*	alex9
*	cpsc 2121
*	lab1
*	changing from array to linked list
*/

#ifndef INTSET_H /* Prevent multiple inclusion... */
#define INTSET_H

struct node{
	int x;
	node *next;
};

class Intset {

 private:
  node *head;


 public:
  Intset();
  ~Intset();
  bool find(int key);
  void insert(int key);
  void remove(int key);
  void print(void);
};

#endif
