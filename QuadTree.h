#ifndef QUEADTREE_H_
#define QUEADTREE_H_

#include <iostream>
using namespace std;
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
    int data;
	Point point;

    Node(Point k, int value) {
        data = value;
        point= k;
    }
	Node(){ data = 0; }
};

class QuadTree{
private:
public:

    

struct Container{
	Point p;
	int d;
	Container(){
		d = -1;
		p.x=0;
		p.y=0;
	}
};



 Node* dat = nullptr;
 bool hasSons = false;
 int isPoint = 0;
 Point UpperLim; 
 Point LowerLim; 
 QuadTree* next; 
 QuadTree* topRight = nullptr; 
 QuadTree* topLeft= nullptr;
 QuadTree* botRight= nullptr;
 QuadTree* botLeft= nullptr;


//public:
    QuadTree(Point a, Point b);
   ~QuadTree();
	 int totalPoints() ;
     int totalNodes() ;
     void insert(Node* n) ;
     void List() ;
	 int inBoundary(Point p);
	 int countRegion(Point p, int d);
     int AggregateRegion(Point p, int d) ;
	 bool search(Point p);

};
#endif


/*struct Node {
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
    
 };
 struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

void postorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}
 
 */