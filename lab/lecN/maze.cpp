#include <iostream>
#include <string>
using namespace std;

const int N = 50;
string maze[N];
bool beenthere[N][N];
int start_i, start_j;
int goal_i, goal_j;

bool visit(int i, int j)
{
  int di[] = {-1, +1,  0,  0};
  int dj[] = { 0,  0, -1, +1};
  if (i == goal_i && j == goal_j) return true;
  beenthere[i][j] = true;
  for (int dir=0; dir<4; dir++) {
    int new_i = i + di[dir];
    int new_j = j + dj[dir];
    if (new_i>=0 && new_i<N && new_j>=0 && new_j<N &&
	maze[new_i][new_j] != '#' && !beenthere[new_i][new_j])
      if (visit(new_i,new_j)) {
	maze[i][j] = '*';
	return true;
      }
  }
  return false;
}

int main(void)
{
  for (int i=0; i<N; i++)
    getline(cin, maze[i]);
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++) {
      if (maze[i][j] == 'A') { start_i = i; start_j = j; }
      if (maze[i][j] == 'B') { goal_i = i; goal_j = j; }
    }
  if (visit(start_i, start_j)) {    
    for (int i=0; i<N; i++) {
      for (int j=0; j<N; j++) {
	if (maze[i][j] == '#') cout << "\e[34;44m";
	if (maze[i][j] == '*') cout << "\e[37;42m";
	if (maze[i][j] == ' ') cout << "\e[30;40m";
	cout << maze[i][j];
      }
      cout << "\e[37;40m\n";
    } 
  } 
  return 0;
}
