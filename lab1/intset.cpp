/*	Alex Moore
*	alex9
*	cpsc 2121
*	lab1
*	changing from array to linked list
just a test
*/

#include <iostream>
#include <assert.h>
#include "intset.h"

using namespace std;

Intset::Intset() //constructor
{
  head = new node;
  head = NULL;
}

Intset::~Intset() //destructor
{
  node *test;
  test = head;
  while (test != NULL) {
		delete test;
		test = test->next;
  }
}

/* Return true if key is in the set */
bool Intset::find(int key)
{
  node *test;
  for (test = head; test!= NULL; test = test->next) { //go through list to find key
	  if (test->x == key) {
		  return true;
	  }
	}
	return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Intset::insert(int key)
{
  node *test = new node; //create new node
  test->x = key; //give it value of key
  node *test2 = head;
  node **test3 = &head;
  assert (!find(key));

	while (test2 != NULL && test2->x < test->x) { //go through the list
		test3 = &test2->next;
		test2 = test2->next;
	}
	*test3 = test; //assign new node a place in the list
	test->next = test2;
}

/* Removes a key.  It is an error if key isn't in the set */
void Intset::remove(int key)
{
	assert (find(key));
	node *test = head, *prev; //store head and prev nodes

	if (test != NULL && test->x == key) { //check if head contains key
		head = test->next;
		delete test; //free node
		return;
	}

	while (test != NULL && test->x != key) { //go through list searching
		prev = test;								  //for the key
		test = test->next;
	}

	prev->next = test->next; //link nodes
	delete test;  //remove the node with the key
}

void Intset::print(void)
{
  node *test;
  for (test = head; test!= NULL; test = test->next){ //go through to end of list
    cout << test->x << "\n"; //print each number
  }
}
