#ifndef POINT_H
#define POINT_H

using namespace std;

struct Node {
	float x;
	float y;
	Node *next;
	Node ()
};

class Pointset {

	private:
		Node ***table;
		int size;
		int num_elems;

	public:
		Point();
		~Point();
		void insert (float x, float y);
		void print (void);
};

#endif
