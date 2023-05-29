#ifndef QUEADTREE_H_
#define QUEADTREE_H_

#include <iostream>
using namespace std;

class QuadTree{
private:
    struct Point {
	int x;
	int y;
	Point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	Point()
	{
		x = 0;
		y = 0;
	}
 };

 struct Node {
	Point pos;
	int data;
	Node(Point _pos, int _data)
	{
		pos = _pos;
		data = _data;
	}
	Node() { data = 0; }
};
 struct Quad{
    
 }


 Point topLeft;
 Point botRight;
 Node* n;

	Quad* topLeftTree;
	Quad* topRightTree;
	Quad* botLeftTree;
	Quad* botRightTree;
public:
	virtual int totalPoints() = 0;
    virtual int totalNodes() = 0;
    virtual void insert(Point p, int data) = 0;
    virtual void list() = 0;
	virtual int countRegion(Point p, int d) = 0;
    virtual int AggregateRegion(Point p, int d):  = 0;

};
#endif
