#include <iostream>
#include <string>
#include <assert.h>
#include "stringintmap.h"

using namespace std;

/* Return a hash for the string s in the range 0..table_size-1 
   Making this function "static" makes it private to this file
*/
static int hash(string s, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  return h;
}

/* Allocate a table of pointers to nodes, all initialized to NULL */
Node **allocate_table(int size)
{
  Node **table = new Node *[size];
  for (int i=0; i<size; i++)
    table[i] = NULL;
  return table;
}

StringIntMap::StringIntMap()
{
  size = 4; // initial size of table    
  table = allocate_table(size);
  num_elems = 0; 
}

StringIntMap::~StringIntMap()
{
  for (int i=0; i<size; i++) {
    while (table[i] != NULL) {
      Node *temp = table[i];
      table[i] = table[i]->next;
      delete temp;
    }
  }
  delete[] table;
}

/* Return true if key is in the set */
bool StringIntMap::find(string key)
{
  int h = hash(key, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == key) return true;
    n = n->next;
  }
  return false;
}

int bad_result = 0;

/* Return count associated with a string */
int &StringIntMap::operator[] (string key)
{
  int h = hash(key, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == key) return n->count;
    n = n->next;
  }
  insert(key);
  h = hash(key, size);
  return table[h]->count;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void StringIntMap::insert(string key)
{
  num_elems++;

  if (num_elems == size) {
    Node **old_table = table;
    size *= 2;
    table = allocate_table(size);
    
    // Transfer all elements from old_table into table
    for (int i=0; i<size/2; i++) {
      Node *n = old_table[i];
      while (n != NULL) {
	int h = hash(n->key, size);
	table[h] = new Node(n->key, table[h], n->count);
	Node *to_delete = n;
	n = n->next;
	delete to_delete;
      }
    }

    // De-allocate old_table
    delete [] old_table;
  }

  int h = hash(key, size);
  table[h] = new Node(key, table[h], 0);
}

/* Removes a key.  It is an error if key isn't in the set */
void StringIntMap::remove(string key)
{
  num_elems--;

  int h = hash(key, size);
  if (table[h]->key == key) {
    // Delete first node
    Node *to_delete = table[h];
    table[h] = table[h]->next;
    delete to_delete;
  } else {
    // Delete from rest of list
    Node *n = table[h];
    while (n->next->key != key) n = n->next;
    Node *to_delete = n->next;
    n->next = to_delete->next;
    delete to_delete;
  }
}

void StringIntMap::print(void)
{
  for (int i=0; i<size; i++) 
    for (Node *n = table[i]; n != NULL; n=n->next)
      cout << n->key << "\n";
}
