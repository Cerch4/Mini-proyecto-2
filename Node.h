#ifndef Node_H
#define Node_H
#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>
#include "Point.h"
using namespace std;



    class Node {
        public:
        Point pos;
        string Country;
        string City;
        string AcccentCity;
        int data;
        Node(Point _pos, int _data)
        {
        pos = _pos;
        data = _data;
        }
        Node() { data = 0; }
};

#endif