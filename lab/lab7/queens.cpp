#include <cstdlib>
#include <iostream>

using namespace std;
int board[40] = {0};
int cr[79] = {0};
int cl[79] = {0};

int totalqueens (int i, int j, int queens) {
  //base case
  if (queens == 0) return 1;
  //count number of solutions
  int count = 0;
  for (int k = 0; k < j; k++) {
    if (!board[k] && !cr[k-i+j-1] && !cl[i+k]) {
      //set queen
      board[k] = cr[k-i+j-1] = cl[i+k] = 1;
      count += totalqueens(i+1, j, queens - 1);
      //remove queen and check next
      board[k] = cr[k-i+j-1] = cl[i+k] = 0;
    }
  }
  return count;
}

int main (int argc, char **argv) {
  int N = atoi(argv[1]);
  if (N == 0) {
    cout << 0 << endl;
    return 0;
  }
  int queens;
  queens = totalqueens(0, N, N);
  cout << queens << endl;
  return 0;
}
