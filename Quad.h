#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>
#include "Node.h"
#include "Point.h"
using namespace std;




class Quad {
    private:
    Point topLeft;
    Point botRight;
    Node* n;
    Quad* topLeftTree;
    Quad* topRightTree;
    Quad* botLeftTree;
    Quad* botRightTree;

public:
    Quad();
    Quad(Point topL, Point botR);
    //~Quad();
    void insert(Node*);
    Node* search(Point);
    bool inBoundary(Point);
    int totalPoints();
    int totalNodes();
    vector<pair<Point, int>> list();
    int countRegion(Point p, int d);
    int AggregateRegion(Point p, int d);
    void ReadCsv(string text, int lines);
};


