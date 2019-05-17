#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
using namespace std;

struct Node {
  string key;
  int size;
  map<string, Node *> kids;
  Node () { key = ""; size = 1; }
  Node (string _key) { key = _key; size = 1; }
};

Node root, *T = &root;

// Given a queue of words, predict the next word

string predict(Node *T, queue<string> &Q)
{
  while (!Q.empty()) {
    string first_word = Q.front();
    Q.pop();
    if (T->kids.count(first_word) == 0)
      return "---";
    T = T->kids[first_word];
  }
  int largest = 0;
  string largest_s = "---";
  for (auto x : T->kids) {
    if (x.second->size > largest) {
      largest = x.second->size;
      largest_s = x.second->key;
    }
  }
  return largest_s;
}

// Read characters in real time; turn string being typed into a queue
// of individual words and call "classify" to predict the next word

int get_character(void) 
{
  struct termios oldt, newt;
  int ch;
  tcgetattr (STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON|ECHO);
  tcsetattr (STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

void process_keystrokes(void)
{
  int ch = 0, last_len=0;
  char s[1024] = "", *tok;
  queue<string> tokens;

  printf ("\e[?25l");
  while (ch != '\n') {
    for (int i=0; i<last_len+1; i++) printf ("\b");
    printf ("\e[0;37;40m%s\e[0;33;40m", s);
    int len = strlen(s);
    char temp[1024];
    strcpy(temp, s);
    tok = strtok(temp, " ");
    while (!tokens.empty()) tokens.pop();
    while (tok) {
      tokens.push(tok);
      tok = strtok(NULL, " ");
    }
    string result = predict(T, tokens);
    printf (" %s", result.c_str());
    len += result.length();
    printf ("\e[0;37;40m");
    for (int j=0; j<last_len-len; j++) printf (" ");
    for (int j=0; j<last_len-len; j++) printf ("\b");
    last_len = len;
    fflush(stdout);
    ch = get_character();
    if ((ch == 8 || ch == 127) && s[0]) s[strlen(s)-1] = 0;
    else if (ch >= ' ') {
      s[strlen(s)+1] = 0;
      s[strlen(s)] = ch;
    } 
  }
  printf ("\e[0;37;40m\e[?25h\n");
}

void insert(Node *T, queue<string> &Q)
{
  if (Q.empty()) return;
  string first_word = Q.front();
  Q.pop();
  if (T->kids.count(first_word) == 0)
    T->kids[first_word] = new Node(first_word);
  T->size++;
  insert (T->kids[first_word], Q);
}

int main(void)
{
  ifstream fin ("social_text");
  queue <string> Q;
  string s;
  while (fin >> s) {
    if (s == "EOL") insert (T, Q);
    else Q.push(s);		     
  }
  cout << "Yay built trie!\n";
  process_keystrokes();
  return 0;
}
