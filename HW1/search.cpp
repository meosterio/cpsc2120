#include <iostream>
#include <fstream>
#include "stringintmap.h"
using namespace std;

struct Elem {
  int val;
  Elem *next;
  Elem (int v, Elem *n) { val = v; next = n; }
};

struct Page {
  string url;
  int num_links;
  double weight, new_weight;
  Elem *first_link;
  Page() { num_links = 0; first_link = NULL; }
};

struct Word {
  string name;
  Elem *first_page;
  Word() { first_page = NULL; }
};

StringIntMap Phash, Whash;
Page *P;
Word *W;
int num_pages, num_words;

void read_input(void)
{
  ifstream fin;
  string s;
  fin.open ("webpages.txt");
  while (fin >> s) {
    if (s == "NEWPAGE") {
      fin >> s;
      Phash[s] = num_pages++;
    }
    else
      if (!Whash.find(s)) Whash[s] = num_words++;
  }
  fin.close();

  P = new Page[num_pages];
  W = new Word[num_words];

  fin.open ("webpages.txt");
  int current_page = -1;
  while (fin >> s) {
    if (s == "NEWPAGE") fin >> P[++current_page].url;
    else {
      if (Phash.find(s)) {
	P[current_page].first_link = new Elem(Phash[s], P[current_page].first_link);
	P[current_page].num_links++;
      }
      else {
	int index = Whash[s];
	W[index].name = s;
	W[index].first_page = new Elem(current_page, W[index].first_page);
      }
    }
  }
  fin.close();
}

void run_pagerank(void)
{
  for (int i=0; i<num_pages; i++) P[i].weight = 1.0 / num_pages;
  for (int iter=0; iter<50; iter++) {
    cout << "Iteration " << iter << "\n";
    for (int i=0; i<num_pages; i++) P[i].new_weight = 0.1 / num_pages;
    for (int i=0; i<num_pages; i++)
      for (Elem *nbr = P[i].first_link; nbr != NULL; nbr = nbr->next)
	P[nbr->val].new_weight += 0.9 * P[i].weight / P[i].num_links;
    for (int i=0; i<num_pages; i++) P[i].weight = P[i].new_weight;
  }
}

void process_queries(void)
{
  string s;
  cout << "Please enter your queries...\n";
  while (cin >> s) {
    if (!Whash.find(s))  cout << "Not found!\n";
    else
      for (Elem *temp = W[Whash[s]].first_page; temp != NULL; temp = temp->next)
	cout << (int)(P[temp->val].weight * num_pages * 100) << " " << P[temp->val].url << "\n";
  }
}

int main(void)
{
  read_input();
  run_pagerank();
  process_queries();
  return 0;
}
