#ifndef Point_H
#define Point_H
#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>
using namespace std;



    class Point {
    public:
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

#endif