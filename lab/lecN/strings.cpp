#include <iostream>
using namespace std;

long long table[15][26];

int main(void)
{
  for (int x=0; x<=14; x++) table[x][25] = 1;
  for (int y=0; y<=25; y++) table[14][y] = 1;
  for (int y=24; y>=0; y--)
    for (int x=13; x>=0; x--)
      table[x][y] = table[x+1][y] + table[x][y+1]; 
  cout << table[0][0] << "\n";
  // Generate kth ascending string...
  long long k = table[0][0] / 2;
  int x=0, y=0;
  while (!(x==14 && y==25)) {
    // move right?
    if (y==25 || k < table[x+1][y]) {
      cout << (char)('A' + y);
      x++;
    } else {
      // move up
      k -= table[x+1][y];
      y++;
    }
  }
  cout << "\n";
  return 0;
}
