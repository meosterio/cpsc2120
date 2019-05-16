#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const int N = 16, M = 3;

struct Candy { int size, value; };
Candy candies[N];
int capacity[M+1] = {999999999};
int multiplier[M+1] = {0};

struct Assignment {

  int which_bag[N];
  int fullness[M+1];
  int total_value;

  Assignment() {
    for (int i=0; i<=M; i++) fullness[i] = 0;
    for (int i=0; i<N; i++) {
      which_bag[i] = 0;
      fullness[0] += candies[i].size;
    }
    total_value = 0;
  }

  // Move candy i into bag b
  bool add_candy_to_bag(int i, int b)
  {
    total_value -= multiplier[which_bag[i]] * candies[i].value;
    fullness[which_bag[i]] -= candies[i].size;
    which_bag[i] = b;
    fullness[which_bag[i]] += candies[i].size;
    total_value += multiplier[which_bag[i]] * candies[i].value;
    return fullness[b] <= capacity[b];
  }
};

// Greedily fill bag b with currently-unused items
void greedy_fill(Assignment *A, int b)
{
  for (int i=0; i<N; i++)
    if (A->which_bag[i] == 0) // unused?
      if (!A->add_candy_to_bag(i, b))
	A->add_candy_to_bag(i, 0);
}

// Greedily remove from bag b until b is within capacity
void greedy_unfill(Assignment *A, int b)
{
  for (int i=N-1; i>=0; i--)
    if (A->fullness[b] > capacity[b] && A->which_bag[i] == b)
      A->add_candy_to_bag(i, 0);
}

int greedy(void)
{
  Assignment A;
  for (int b=1; b<=M; b++) greedy_fill(&A, b);
  return A.total_value;
}

// Randomize assignment...
void randomize(Assignment *A)
{
  for (int i=0; i<N; i++) 
    if (!A->add_candy_to_bag(i, rand()%M+1))
      A->add_candy_to_bag(i, 0);      
}

// Tries to refine A by moving to neighboring solutions
// If successful, returns true
bool refine(Assignment *A)
{
  Assignment old_A = *A;
  
  // Look at all neighbors reached by moving candy i into bag b
  for (int i=0; i<N; i++)
    for (int b=0; b<=M; b++) {
      int old_bag = A->which_bag[i];
      A->add_candy_to_bag(i, b);   // move from old_bag to b
      // greedily add to fill empty space created in old bag
      greedy_fill(A, old_bag); 
      // repair solution by greedily removing from b
      greedy_unfill(A, b);
      if (A->total_value > old_A.total_value) return true;
      else *A = old_A; // revert back to old solution
    }

  return false;
}

int iterative_refinement(void)
{
  int best = 0;
  for (int iter=0; iter<1000; iter++) {
    Assignment A;
    randomize(&A);
    while (refine(&A));
    if (A.total_value > best) best = A.total_value;
  }
  return best;
}

// Try to place candy i in all possible ways, recursing to 
// complete solution.  
int exhaustive(Assignment *A, int i)
{
  if (i == N) return A->total_value;

  int best = 0;
  for (int b=0; b<=M; b++) {

    // First item to be added, without loss of generality, can be
    // assumed to be added to bags 0 or 1 (symmetry)
    if (A->total_value == 0 && b>1) continue;

    // tentatively add candy i to bag b, pruning if overfull
    if (A->add_candy_to_bag(i, b)) {
      int answer = exhaustive(A, i+1);
      if (answer > best) best = answer;
    }
    A->add_candy_to_bag(i, 0);  // un-add candy i from bag b
  }
  return best;
}

int main(void)
{
  // Read input file
  ifstream fin("candy.txt");
  for (int i=0; i<N; i++)
    fin >> candies[i].size >> candies[i].value;
  fin.close();
  
  // Bubble sort candies so val1/size1 > val2/size2 > ...
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (int i=0; i<N-1; i++)
      if ((double)candies[i].value / candies[i].size < 
	  (double)candies[i+1].value / candies[i+1].size) {
	swap (candies[i], candies[i+1]);
	sorted = false;
      }
  }

  for (int i=1; i<=M; i++) {
    capacity[i] = 2000;
    multiplier[i] = 1;
  }

  cout << "Greedy: " << greedy() << "\n";
  cout << "Iterative: " << iterative_refinement() << "\n";

  Assignment A;
  cout << "Exhaustive: " << exhaustive(&A, 0) << "\n";

  return 0;
}
