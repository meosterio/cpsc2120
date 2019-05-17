#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

struct Node {
	double x;
	double y;
	Node *next;
	Node (double one, double two, Node *n) { x = one; y = two; next = n; }
	Node () {x=0; y=0; next = NULL; }
};

double checkdist (Node *one, Node *two) {
	double ix = one->x - two->x;
	double iy = one->y - two->y;
	double idist;

	idist = pow(ix,2)+pow(iy,2);
	idist = sqrt(idist);
	return idist;
}




int main(void) {

		ifstream pointsfile("points.txt");
		Node ***table;
		int size = 1000; //fix
		table = new Node **[size];
		for (int i = 0; i < size; i++) {
			table[i] = new Node *[size];
			for (int j = 0; j < size; j++) {
				table[i][j] = new Node;
			}
		}
		double disx;
		double disy;
		while (pointsfile >> disx >> disy) {
			table[(int)(disx*size)][(int)(disy*size)] = new Node (disx, disy, table[(int)(disx*size)][(int)(disy*size)]);
		}
		pointsfile.close();

		Node *one, *two;
		double dist = 10000;
		double hold;
		for (int i = 0; i < size-1; i++) {
			for (int j = 0; j < size-1; j++) {
				one = table[i][j];
				while(one!=NULL) {
					if (one->next!=NULL) {
						two = one->next;
						while(two != NULL) {
							hold = checkdist(one, two);
							if (hold > 0 && hold < dist) {
							dist = hold;
							}
							two = two->next;
						}
					}
					if (table[i+1][j]!=NULL) {
						two = table[i+1][j];
						while (two != NULL) {
							hold = checkdist(one, two);
							if (hold > 0 && hold < dist) {
								dist = hold;
							}
							two = two->next;
						}
					}
					if (table[i][j+1]!=NULL) {
						two = table[i][j+1];
						while (two != NULL) {
							hold = checkdist(one, two);
							if (hold > 0 && hold < dist) {
								dist = hold;
							}
							two = two->next;
						}
					}
					if (table[i+1][j+1]!=NULL) {
						two = table[i+1][j+1];
						while (two != NULL) {
							hold = checkdist(one, two);
							if (hold > 0 && hold < dist) {
								dist = hold;
							}
							two = two->next;
						}
					}
					if (j > 0) {
					if (table[i+1][j-1]!=NULL) {
						two = table[i+1][j-1];
						while (two != NULL) {
							hold = checkdist(one, two);
							if (hold > 0 && hold < dist) {
								dist = hold;
							}
							two = two->next;
						}
					}
					}
					one = one->next;
				}
			}
		}
		cout << dist << endl;

		for (int i = 0; i<size; i++)
			delete [] table[i];
		delete [] table;

	return 0;
}
