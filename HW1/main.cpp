/*
*Everything works properly except for my weight function. I believe I am doing
*something backwards during this part, which is resulting in the numbers being
*off. I tried a few different implementations for this part, but none of them
*ended up working both efficiently and correctly. The code I left in as a
*comment is one solution I came up with that I believe works, but has an
*extremely long running time.
*/

#include <fstream>
#include <iostream>
#include <assert.h>
#include <string.h>
#include "google.h"

using namespace std;

int hash(string s, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++) {
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  }
  return h;
}

int main (void) {

    ifstream pages("webpages.txt");
    string s;
    string URL;
    int h;
    int pgCount = 0;
    while (pages >> s) {
      if (s == "NEWPAGE") {
        pgCount++;
      }
    }
    pages.close();

    ifstream pages2("webpages.txt");
    Node *PAGE = new Node [pgCount];
    for (int ii = 0; ii < pgCount; ii++) {
      PAGE[ii].key = "BAD";
    }
    int wrCount = 200000;
    WrdInvert *wrd = new WrdInvert [wrCount];
    for (int ii = 0; ii < wrCount; ii++) {
      wrd[ii].key = "BAD";
    }
    while (pages2 >> s) {
      if (s == "NEWPAGE") {
        pages2 >> s;
        URL = s;
        h = hash(URL, pgCount);
        while (PAGE[h].key != "BAD") {
          h++;
          if (h == pgCount) {
            h=0;
          }
        }
        PAGE[h].key = URL;
        PAGE[h].word = NULL;
        PAGE[h].link = NULL;
      }
      else if ((s[0]=='h')&&(s[1]=='t')&&(s[2]=='t')&&(s[3]=='p')) {
        PAGE[h].link = new Linkstable(s, PAGE[h].link, 0, 0, 0);
      }
      else {
        PAGE[h].word = new Wordstable(s, PAGE[h].word);
        int wh = hash(s, wrCount);
        if (wrd[wh].key == s) {
          wrd[wh].link = new Linkstable(PAGE[h].key, wrd[wh].link, 0, 0, 0);
        }
        while (wrd[wh].key != s) {
          if (wrd[wh].key == "BAD"){
            wrd[wh].key = s;
            wrd[wh].link = new Linkstable(PAGE[h].key, wrd[wh].link, 0, 0, 0);
          }
          else {
            wh++;
            if (wh == wrCount) {
              wh = 0;
            }
            if (wrd[wh].key == s) {
              wrd[wh].link = new Linkstable(PAGE[h].key, wrd[wh].link, 0, 0, 0);
            }
          }
        }
      }
    }
    pages2.close();

    for (int i = 0; i < pgCount; i++) {
      Node test = PAGE[i];
      if (test.key != "BAD") {
        double lc = 0;
        while (test.link != NULL) {
          lc++;
          test.link = test.link->next;
        }
        PAGE[i].linkCount = lc;
      }
    }

    double dawet = .00001435461644;
    double danewet = .000001435461644;

    for (int i = 0; i < wrCount; i++) {
      WrdInvert test = wrd[i];
      while (test.link != NULL) {
        test.link->weight1 = dawet;
        test.link = test.link->next;
      }
    }
      /*for (int i = 0; i < pgCount; i++) {
        Node test = PAGE[i];
        if (test.key != "BAD") {
          //while(test.link != NULL) {
          PAGE[i].weight = dawet;
          //test.link = test.link->next;
          }
        }
      for (int f = 0; f<50; f++) {
      for (int i = 0; i < pgCount; i++) {
        Node test = PAGE[i];
        if (test.key != "BAD") {
          while(test.link != NULL) {
          test.link->new_weight1 = danewet;
          test.link = test.link->next;
          }
        }
      }
      for (int i = 0; i < pgCount; i++) {
        Node test = PAGE[i];
        if (test.key != "BAD") {
          while (test.link != NULL) {
            h = hash(test.link->key, pgCount);
            int k = 0;
            while (k < pgCount) {
              if (PAGE[h].key == test.link->key) {
                double wh8;
                wh8 = (((.9*test.link->weight1)/test.linkCount) + PAGE[h].new_weight);
                PAGE[h].new_weight = wh8;
                break;
                }
                k++;
                h++;
                if (h == pgCount) {
                  h = 0;
                }
              }
            }
            test.link = test.link->next;
          }
        }
      }
          double wh8;
            if (test.link->isPres == 0) {
            wh8 = (((.9*test.link->weight)/test.linkCount) + test.new_weight);
            test.new_weight = wh8;
            }
            test.link = test.link->next;
          }
        }
      }

      for (int i = 0; i < pgCount; i++) {
        Node test = PAGE[i];
        if (test.key != "BAD") {
          while(test.link != NULL) {
          test.link->weight1 = test.link->new_weight1;
          test.link = test.link->next;
          }
        }
      }
    }*/
    string userInput;
    while(userInput != "quitquit") {
    cout << "Enter a word (Enter quitquit to exit):" << "  ";
    cin >> userInput;
    if (userInput == "quitquit") {
      return 0;
    }
    cout << endl;

    for (int i = 0; i < wrCount; i++) {
      WrdInvert test = wrd[i];
      if (test.key == userInput) {
        for (int f = 0; f<50; f++) {
          while(test.link != NULL) {
            test.link->new_weight1 = danewet;
            test.link = test.link->next;
          }
          WrdInvert test2 = wrd[i];
          while(test2.link != NULL) {
            int k = 0;
            while (k < pgCount) {
              if (PAGE[k].key == test2.link->key) {
                double wh8;
                wh8 = (((.9*test2.link->weight1)/PAGE[k].linkCount) + test2.link->new_weight1);
                test2.link->new_weight1 = wh8;
                break;
              }
              k++;
            }
            test2.link = test2.link->next;
          }
          WrdInvert test3 = wrd[i];
          while(test3.link != NULL) {
            test3.link->weight1 = test3.link->new_weight1;
            test3.link = test3.link->next;
          }
        }
      }
    }

    for (int i = 0; i < wrCount; i++) {
      WrdInvert test = wrd[i];
      if (test.key == userInput) {
        cout << userInput << endl;
        while (test.link != NULL) {
          cout << (int)(test.link->weight1*(100*pgCount)) << "  ";
          cout << test.link->key << endl;
          test.link = test.link->next;
        }
      }
    }
  }

    return 0;
}
