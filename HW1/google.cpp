#include <iostream>
#include <string.h>
#include <assert.h>
#include "google.h"

using namespace std;
/*
int hash(string s, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  return h;
}
*/

/*
Linkstable *insert_at_endL(Linkstable *head, string new_key) {
  if (head == NULL) return new Linkstable(new_key, NULL, 0, 0);
  head->next = insert_at_endL(head->next, new_key);
  return head;
}
*/
/* Allocate a table of pointers to nodes, all initialized to NULL */
Node **allocate_table(int size)
{
  Node **table = new Node *[size];
  for (int i=0; i<size; i++)
    table[i] = NULL;
  return table;
}

PageSet::PageSet()
{
  size = 4; // initial size of table
  table = allocate_table(size);
  num_elems = 0;
}

PageSet::~PageSet()
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

// Return count associated with a string
int &PageSet::operator[] (string key) {
  int h = hash(key, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == key) return n->count;
    n=n->next;
  }
  insert(key);
  h = hash(key, size);
  return table[h]->count;
}

void PageSet::insert(string key)
{
  assert (!find(key));
  num_elems++;

  if (num_elems == size) {
	   Node **old_table = table;
	   size = size * 2;
     table = allocate_table(size);

     //transfer all elements from old_table into table
     for (int i = 0; i<size/2; i++) {
       Node *n = old_table[i];
       while (n!=NULL) {
         int h = hash(n->key, size);
         table[h] = new Node(n->key, table[h], n->count);
         Node *to_delete = n;
         n = n->next;
         delete to_delete;
       }
     }

     //de-allocate old_table
     delete [] old_table;
   }

   int h = hash(key, size);
   table[h] = new Node(key, table[h], 0);
 }
