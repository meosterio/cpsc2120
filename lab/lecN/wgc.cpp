/*
  Initial state: ME, WOLF, GOAT, CABBAGE || nothing
  | 
  +--> WOLF CABBAGE || ME GOAT

  Goal state: nothing || ME, WOLF, GOAT, CABBAGE

  16 "states" (i.e., nodes)
  
  state = 4-bit binary #

  MWGC
  1111
 */
#include <iostream>
#include <string>
using namespace std;

// Retrieves value of the positionth bit in x
bool bit(int x, int position)
{
  return (x>>position) & 1;
}

// Returns x with the positionth bit set to value
int set_bit(int x, int position, int value)
{
  // zero out positionth bit in x:
  x = x & ~(1<<position);
  // set it to value:
  x = x | (value<<position);
  return x;
}

string state_name(int x)
{ 
  string result = "", objs[] = {"ME", "WOLF", "GOAT", "CABBAGE"};
  for (int i=0; i<4; i++)
    if (bit(x, i) == 0) result += objs[i] + " ";
  result += " || ";
  for (int i=0; i<4; i++)
    if (bit(x, i) == 1) result += objs[i] + " ";
  return result;
}

bool beenthere[16];
int where_came_from[16];

bool edge_exists(int from, int to)
{
  int ME = 0, WOLF = 1, GOAT = 2, CABBAGE = 3;

  // I have to cross the river...
  if (bit(from,ME) == bit(to,ME)) return false;
  
  // Can only take one extra object with me...
  int num_carry = 0;
  if (bit(from,WOLF) != bit(to,WOLF)) num_carry++;
  if (bit(from,GOAT) != bit(to,GOAT)) num_carry++;
  if (bit(from,CABBAGE) != bit(to,CABBAGE)) num_carry++;
  if (num_carry > 1) return false;
  
  // Wolf and goat not on same side in "to" state, and unsupervised
  if (bit(to,WOLF) == bit(to,GOAT) &&
      bit(to,WOLF) != bit(to,ME)) return false;

  // Cabbage and goat not on same side in "to" state, and unsupervised
  if (bit(to,CABBAGE) == bit(to,GOAT) &&
      bit(to,CABBAGE) != bit(to,ME)) return false;

  return true;
}

bool can_find_dest(int current_state)
{
  if (current_state == 15) return true;
  beenthere[current_state] = true;
  for (int next_state=0; next_state<16; next_state++) 
    if (edge_exists(current_state, next_state) && !beenthere[next_state]) {
      where_came_from[next_state] = current_state;
      if (can_find_dest(next_state)) return true;
    }
  return false;
}

void print_path(int state)
{
  if (state != 0)
    print_path(where_came_from[state]);
  cout << state_name(state) << "\n";  // last thing I print
}

int main(void)
{
  if (can_find_dest(0)) 
    print_path(15);
  return 0;
}
