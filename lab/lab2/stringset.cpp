#include <iostream>
#include <string.h>
#include <assert.h>
#include "stringset.h"

using namespace std;

/* Return a hash for the string s in the range 0..table_size-1 */
int hash(string s, int table_size)
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

Stringset::Stringset()
{
  size = 4; // initial size of table
  table = allocate_table(size);
  num_elems = 0;
}

Stringset::~Stringset()
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
bool Stringset::find(string key)
{
  int h = hash(key, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == key) return true;
    n = n->next;
  }
  return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Stringset::insert(string key)
{
  assert (!find(key));
  num_elems++;

  if (num_elems == size) {
	   int hold = size;
	   size = size * 2;
		Node **newtable = new Node *[size];
  		for (int i=0; i<size; i++) {
    		newtable[i] = NULL;
		}
		for (int i = 0; i < hold; i++) {
			for (Node *test = table[i]; test != NULL; test = test->next) {
				int hsh = hash(test->key, size);
				newtable[hsh] = new Node(test->key, newtable[hsh]);
			}
		}
	table = newtable;
	}

    // TBD: Expand table -- allocate new table of twice the size,
    // re-insert all keys into new table, and de-allocate old table.
    // (you may want to wait and add this code last, once everything
    // else is working, since the class will still function properly,
    // albeit slowly, without this part)

	int hsh = hash(key, size);
	table[hsh] = new Node(key, table[hsh]);

}

/* Removes a key.  It is an error if key isn't in the set */
void Stringset::remove(string key)
{
  assert (find(key));
  num_elems--;

	int hsh = hash(key, size);
	Node *test = table[hsh];
	if (test->key == key) {
		table[hsh] = test->next;
		return;
	}
	while (test->next->key != key) {
		test = test->next;
	}
	Node *remov = test;
	test = test->next;
	remov->next = test->next;
	return;
}

void Stringset::print(void)
{
	for (int i = 0; i < size; i++) {
		for (Node *test = table[i]; test != NULL; test = test->next) {
			cout << test->key << "\n";
		}
	}
	return;
}
