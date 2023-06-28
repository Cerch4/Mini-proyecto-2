#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>
#include "Quad.h"
#include "Point.h"
#include  "Node.h"

using namespace std;
// Driver program
int main(){
    Quad center(Point(0, 0), Point(536870912,536870912));
 
    string access = "worldcitiespop_fixed.csv";
    center.ReadCsv(access,800000);
    //vector<pair<Point, int>> pointList = center.list();
    cout <<"Nodos Totales: "<< center.totalNodes() << "\n";
    cout << "Puntos Totales: "<<center.totalPoints() << "\n";
    cout << "Reguion (4,4), 2: " << center.countRegion(Point(1,1),2);
    cout << "\nReguion count (4,4), 2: " << center.AggregateRegion(Point(1,1),2);


    return 0;
}