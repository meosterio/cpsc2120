#include <iostream>
#include <map>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cmath>
using namespace std;

//                0   1    2   3    4   5   6    7   8    9   10   11
string note[] = {"C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"};

struct Chord {
  string longName;
  string shortName;
  int notes[4];
  int dom7Sib; // if not dominant 7th chord, which dominant 7th chord is this chord's "sibling"?...
};
vector<Chord> C;

/* Check for valid chord types... */
int dom7diffs[] = {4,7,10}, min7diffs[] = {3,7,10}, maj7diffs[] = {4,7,11}, dim7diffs[] = {3,6,9};
int diffCheck(int *notes, int *diffs)
{
  int a[4] = {notes[0], notes[1], notes[2], notes[3]}, x=1;
  do {
    if (diffs[0]==(a[1]-a[0]+12*8)%12 && diffs[1]==(a[2]-a[0]+12*8)%12 && diffs[2]==(a[3]-a[0]+12*8)%12) 
      return a[0]+12;
  } while (next_permutation(a,a+4));
  return 0;
}
int isDom7(int *notes) { return diffCheck(notes, dom7diffs); }
int isMaj7(int *notes) { return diffCheck(notes, maj7diffs); }
int isMin7(int *notes) { return diffCheck(notes, min7diffs); }
int isDim7(int *notes) { return diffCheck(notes, dim7diffs); }
bool isValidChord(int *notes) { return isDom7(notes) || isMin7(notes) || isMaj7(notes) || isDim7(notes); }

/* Chord management... */
bool sameChord(int *n1, int *n2)
{ 
  int a[4] = {n1[0], n1[1], n1[2], n1[3]};
  int b[4] = {n2[0], n2[1], n2[2], n2[3]};
  sort(a,a+4); sort(b,b+4);
  for (int i=0; i<4; i++) if (a[i]!=b[i]) return false;
  return true;
}
int findChord(int *notes)
{ 
  for (int i=0; i<C.size(); i++) if (sameChord(notes, C[i].notes)) return i;
  return -1;
}
int inversion(int *notes)
{
  int a[4] = {notes[0], notes[1], notes[2], notes[3]};
  sort(a,a+4);
  int root;
  if (isDom7(notes)>0) root = isDom7(notes)-12;
  if (isMaj7(notes)>0) root = isMaj7(notes)-12;
  if (isMin7(notes)>0) root = isMin7(notes)-12;
  if (a[0] == root) return 0;
  if ((a[0] - root + 12*8) % 12 <= 4) return 1;
  return 2;
}
string chordNotes(Chord c)
{
  string octave[] = {"3","4","5","6"}, result = "";
  Chord temp = c;
  sort(temp.notes, temp.notes+4);
  for (int i=0; i<4; i++) result += (i?" ":"") + note[temp.notes[i]%12] + octave[temp.notes[i]/12];
  return result;
}
string chordName(Chord c)
{
  string result = "";
  if (isMaj7(c.notes)) result = note[isMaj7(c.notes)%12] + " Maj7";
  if (isMin7(c.notes)) result = note[isMin7(c.notes)%12] + " Min7";
  if (isDom7(c.notes)) result = note[isDom7(c.notes)%12] + " Dom7";
  if (isDim7(c.notes)) result = "Dim7";
  return result;
}
int notesInKeyF(Chord c)
{
  int total = 0, keyNotes[] = {0,2,4,5,7,9,11}, base = 5;
  for (int i=0; i<4; i++)
    for (int j=0; j<7; j++)
      if ((12-base + c.notes[i])%12 == keyNotes[j]) total++;
  return total;
}
void buildChords(void)
{
  int M = 24;
  Chord c;
  for (c.notes[0]=0; c.notes[0]<M; c.notes[0]++)
    for (c.notes[1]=0; c.notes[1]<M; c.notes[1]++)
      for (c.notes[2]=0; c.notes[2]<M; c.notes[2]++)
	for (c.notes[3]=0; c.notes[3]<M; c.notes[3]++) 
	  if (isValidChord(c.notes) && findChord(c.notes)==-1 && (notesInKeyF(c)>=3 || isDim7(c.notes))) {
	    if (isDom7(c.notes) && inversion(c.notes)>1) continue;
	    c.shortName = chordName(c);
	    c.longName = chordNotes(c) + " (" + chordName(c) + ")";
	    c.dom7Sib = -1;
	    C.push_back(c);
	  }
  for (int i=0; i<C.size(); i++) {
    Chord temp; 
    for (int j=0; j<4; j++) {
      temp = C[i]; temp.notes[j]--; 
      if (isMaj7(C[i].notes) && isDom7(temp.notes) == isMaj7(C[i].notes)) C[i].dom7Sib = findChord(temp.notes);
      temp = C[i]; temp.notes[j]++; 
      if (isMin7(C[i].notes) && isDom7(temp.notes) == isMin7(C[i].notes)) C[i].dom7Sib = findChord(temp.notes);
    }
  }
}
bool hasNote(Chord c, int note)
{
  for (int i=0; i<4; i++) if (c.notes[i]%12==note%12) return true;
  return false;
}
int chordDist(int *n1, int *n2)
{
  int a[4] = {n1[0], n1[1], n1[2], n1[3]};
  int b[4] = {n2[0], n2[1], n2[2], n2[3]};
  sort(a,a+4); sort(b,b+4);
  int total = 0;
  for (int i=0; i<4; i++) total += pow((double)(a[i]-b[i]),2);
  return sqrt(total);
}
bool edgeExists(Chord c1, Chord c2, bool init)
{
  // No back-to-back chords of same type...
  if (isDom7(c1.notes)>0 && isDom7(c2.notes)>0 && init) return false;
  if (isMaj7(c1.notes)>0 && isMaj7(c2.notes)>0) return false;
  if (isMin7(c1.notes)>0 && isMin7(c2.notes)>0) return false;
  if (isDim7(c1.notes)>0 && isDim7(c2.notes)>0) return false;
  if (isMin7(c1.notes)>0 && isMaj7(c2.notes)>0) return false;
  // Special cases; ii->V/V->V...
  if (init && isDom7(c1.notes)>0 && isMin7(c2.notes)>0 && (isMin7(c2.notes)-isDom7(c1.notes)+12*8) % 12 == 2) return false;
  if (init && isMin7(c1.notes)>0 && isDom7(c2.notes)>0 && (isDom7(c2.notes)-isMin7(c1.notes)+12*8) % 12 == 11) return false; 
  if (init && isMaj7(c1.notes)>0 && isMin7(c2.notes)>0 && (isMin7(c2.notes)-isMaj7(c1.notes)+12*8) % 12 == 4 && (c1.notes[0]-c2.notes[0]+12*8) % 12 != 5) return true;
  if (init && isMaj7(c1.notes)>0 && isMin7(c2.notes)>0 && (isMin7(c2.notes)-isMaj7(c1.notes)+12*8) % 12 == 9) return true;
  if (init && isMaj7(c1.notes)>0 && isMin7(c2.notes)>0 && (isMin7(c2.notes)-isMaj7(c1.notes)+12*8) % 12 != 2) return false;
  if (init && c1.dom7Sib != -1 && edgeExists(C[c1.dom7Sib], c2, false)) return true;
  if (chordDist(c1.notes, c2.notes)==1 && isDim7(c2.notes)>0) return true;
  // tritones must resolve inward or outward...
  for (int i=0; i<4; i++)
    for (int j=0; j<4; j++) {
      if ((c1.notes[i]%12 - c1.notes[j]%12 + 12*8)%12 == 6 && hasNote(c2,c1.notes[i]+1) && hasNote(c2,c1.notes[j]-1)) return true;
      if ((c1.notes[i]%12 - c1.notes[j]%12 + 12*8)%12 == 6 && hasNote(c2,c1.notes[i]-1) && hasNote(c2,c1.notes[j]+1)) return true;
      if (init && isDom7(c1.notes)>0 && isMin7(c2.notes)>0 && (c1.notes[i]%12 - c1.notes[j]%12 + 12*8)%12 == 6 && hasNote(c2,c1.notes[i]-2) && hasNote(c2,c1.notes[j]+1) && (isDom7(c1.notes)-isMin7(c2.notes)+12*8) % 12 == 7) return true;
      if (init && isDom7(c1.notes)>0 && isMin7(c2.notes)>0 && (c1.notes[i]%12 - c1.notes[j]%12 + 12*8)%12 == 6 && hasNote(c2,c1.notes[i]+1) && hasNote(c2,c1.notes[j]-2) && (isDom7(c1.notes)-isMin7(c2.notes)+12*8) % 12 == 7) return true;
    }
  return false;
}

/* Code to generate visual representation of music... */
int x_scale = 400;
void xfigHeader(void)
{
  printf ("#FIG 3.2  Produced by xfig version 3.2.5\nLandscape\nCenter\nInches\nLetter\n100.00\nSingle\n-2\n1200 2\n");
}

void line(int x1, int y1, int x2, int y2, int depth, int thick) 
{
  printf ("2 1 0 %d 0 7 %d -1 -1 0.000 0 0 -1 0 0 2\n", thick, depth);
  printf ("\t%d %d %d %d\n", x1, y1, x2, y2);
}

void circle(int x, int y, int radius, int depth, int fill)
{
  printf ("1 3 0 1 0 7 %d -1 %d 0.000 1 0.0000 %d %d %d %d %d %d %d %d\n", depth, fill, x, y, radius, radius, x+radius, y, x, y);
}

void drawStaff(int width)
{
  for (int i=0; i<17; i++) 
    if ((i>=2 && i<=6) || (i>=10 && i<=14))
      line (0,i*x_scale,width*x_scale*5,i*x_scale,50,2);
}

void drawText(int x, int y, string text)
{
  cout << "4 1 0 100 0 0 18 0.0000 4 135 720 " << x << " " << y << " " << text << "\\001\n";
}

void drawChord(int col, Chord c, int mel)
{
  int row[] =     {0,  1,   1,  2,   2,  3,  4,   4,  5,   5,   6,   6};
  int flat[] =    {0,  1,   0,  1,   0,  0,  1,   0,  1,   0,   1,   0};
  int x = 5 * col * x_scale;
  x += 2.5 * x_scale;
  for (int i=0; i<5; i++) {
    int n = i==4 ? mel : c.notes[i], w = i==4 ? 5 : 0;
    int f = flat[n%12];
    n = row[n%12] + 7*(n/12);
    int y;
    if (n < 7) y = 12.5*x_scale - n*0.5*x_scale, x_scale*0.5;
    else if (n == 7) { 
      line (x-x_scale*1.5, 8*x_scale, x+x_scale*1.5, 8*x_scale, 50, 2);
      y = 8*x_scale;
    }
    else y = 7*x_scale - (n-7)*0.5*x_scale, x_scale*0.5;
    circle (x, y, x_scale*0.5, 49, 10-w);
    if (f) {
      line (x - x_scale, y, x - x_scale, y - x_scale * 1.5, 50, 2);
      line (x - x_scale, y, x - x_scale * 0.7, y + x_scale * 0.3, 50, 2);
      line (x - x_scale * 0.7, y + x_scale * 0.3, x - x_scale * 0.7, y, 50, 2);
      line (x - x_scale, y - x_scale * 0.3, x - x_scale * 0.7, y, 50, 2);
    }
  }
  drawText (x, 17*x_scale, c.shortName);
}

// ------------------------------------------------------------

// Main code beyond this point; these are the functions we can use...

bool doesEdgeExist(Chord c1, Chord c2) { return edgeExists(c1,c2,true); }
bool doesChordHaveNote(Chord c, int note) { return hasNote(c, note); }
double chordEuclideanDist(Chord c1, Chord c2) { return chordDist(c1.notes, c2.notes); }

#define CHORD_FMAJ7 171   // let's start and end on this chord

#define NOTE_D4 14
#define NOTE_F4 17
#define NOTE_G4 19
#define NOTE_A4 21
#define NOTE_Bb4 22
#define NOTE_C5 24

void compose(vector<int> &melody)
{
  int M = melody.size();    // length of melody
  int N = C.size();         // number of chords
  double INF = 2342323;
  // hard part...

  // dist[row][col] is shortest path distance to goal from chord "row" to melody note "col"
  double **dist; 
  dist = new double *[N];
  for (int r=0; r<N; r++) {
    dist[r] = new double[M];
    for (int c=0; c<M; c++) 
      dist[r][c] = INF;
  }

  int **next;
  next = new int *[N];
  for (int r=0; r<N; r++) 
    next[r] = new int[M];

  // Base case
  dist[CHORD_FMAJ7][M-1] = 0;

  // Solve everything!!!!!!!
  for (int col=M-2; col>=0; col--)
    for (int row=0; row<N; row++)
      if (doesChordHaveNote(C[row], melody[col])) 
	for (int nextChord=0; nextChord<N; nextChord++)
	  if (doesEdgeExist(C[row], C[nextChord])) 
	    if (chordEuclideanDist(C[row], C[nextChord]) + dist[nextChord][col+1] < dist[row][col]) {
	      dist[row][col] = chordEuclideanDist(C[row], C[nextChord]) + dist[nextChord][col+1];
	      next[row][col] = nextChord;
	    }
  
  //  cout << "Answer: " << dist[CHORD_FMAJ7][0] << "\n";
  int row = CHORD_FMAJ7;
  //  xfigHeader();
  //  drawStaff(M);
  for (int col=0; col<M; col++) {
    cout << C[row].longName << "\n";
    //    drawChord(col, C[row], melody[col]);
    row = next[row][col];
  }
}

int main(int argc, char *argv[])
{
  // Populates a global vector C[...] of valid chords
  // C[i].notes[] -- array of the 4 notes in chord i
  // C[i].shortName, C[i].longName --- string name of chord i
  buildChords();
  /*
  cout << "Chords:\n";
  for (int i=0; i<C.size(); i++)
    cout << i << ": " << C[i].longName << "\n";

  cout << "Edges:\n";
  for (int i=0; i<C.size(); i++)
    for (int j=0; j<C.size(); j++)
      if (doesEdgeExist(C[i], C[j]))
	cout << C[i].longName << " ---> " << C[j].longName << "\n";
  */
  vector<int> melody;          // chords:
  melody.push_back(NOTE_F4);   
  melody.push_back(NOTE_G4);   
  melody.push_back(NOTE_A4);   
  melody.push_back(NOTE_C5);   
  melody.push_back(NOTE_Bb4);   
  melody.push_back(NOTE_G4);   
  melody.push_back(NOTE_F4);  

  compose(melody);

  return 0;
}
