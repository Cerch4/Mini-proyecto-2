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

 Quad::Quad(){
        topLeft = Point(0, 0);
        botRight = Point(0, 0);
        n = NULL;
        topLeftTree = NULL;
        topRightTree = NULL;
        botLeftTree = NULL;
        botRightTree = NULL;
    }

 Quad::Quad(Point topL, Point botR){
        n = NULL;
        topLeftTree = NULL;
        topRightTree = NULL;
        botLeftTree = NULL;
        botRightTree = NULL;
        topLeft = topL;
        botRight = botR;
}


// Insert a node into the quadtree
void Quad::insert(Node* node)
{
    if (node == NULL)
        return;
 
    // Current quad cannot contain it
    if (!inBoundary(node->pos))
        return;
 
    // We are at a quad of unit area
    // We cannot subdivide this quad further
    if (abs(topLeft.x - botRight.x) <= 1
        && abs(topLeft.y - botRight.y) <= 1) {
        if (n == NULL){
            n = node;
        return;
        }
        //else{
          //cout << "Error. Ingrese otro valor: " << n->pos.x <<" "  << n ->pos.y << endl;

       // }
    }
    
    if ((topLeft.x + botRight.x) / 2 > node->pos.x) {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
            if (topLeftTree == NULL){
                topLeftTree = new Quad(Point(topLeft.x, topLeft.y),Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2));
                botLeftTree = new Quad(Point(topLeft.x,(topLeft.y + botRight.y) / 2),Point((topLeft.x + botRight.x) / 2,botRight.y));
                topRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,topLeft.y),Point(botRight.x,(topLeft.y + botRight.y) / 2));
                botRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),Point(botRight.x, botRight.y));
            }
            topLeftTree->insert(node);
        }
 
        // Indicates botLeftTree
        else {
            if (botLeftTree == NULL){
               topLeftTree = new Quad(Point(topLeft.x, topLeft.y),Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2));
                botLeftTree = new Quad(Point(topLeft.x,(topLeft.y + botRight.y) / 2),Point((topLeft.x + botRight.x) / 2,botRight.y));
                topRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,topLeft.y),Point(botRight.x,(topLeft.y + botRight.y) / 2));
                botRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),Point(botRight.x, botRight.y));
            }
            botLeftTree->insert(node);
        }
    }
    else {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
            if (topRightTree == NULL){
                topLeftTree = new Quad(Point(topLeft.x, topLeft.y),Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2));
                botLeftTree = new Quad(Point(topLeft.x,(topLeft.y + botRight.y) / 2),Point((topLeft.x + botRight.x) / 2,botRight.y));
                topRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,topLeft.y),Point(botRight.x,(topLeft.y + botRight.y) / 2));
                botRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),Point(botRight.x, botRight.y));
            }
            topRightTree->insert(node);
        }
 
        // Indicates botRightTree
        else {
            if (botRightTree == NULL){
                topLeftTree = new Quad(Point(topLeft.x, topLeft.y),Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2));
                botLeftTree = new Quad(Point(topLeft.x,(topLeft.y + botRight.y) / 2),Point((topLeft.x + botRight.x) / 2,botRight.y));
                topRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,topLeft.y),Point(botRight.x,(topLeft.y + botRight.y) / 2));
                botRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),Point(botRight.x, botRight.y));
            }   
            botRightTree->insert(node);
        }
    }
}
 
 
Node* Quad::search(Point p)
{
	// Current quad cannot contain it
	if (!inBoundary(p))
		return NULL;

	// We are at a quad of unit length
	// We cannot subdivide this quad further
	if (n != NULL){
		return n;
    }

	if ((topLeft.x + botRight.x) / 2 > p.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 > p.y) {
			if (topLeftTree == NULL)
				return NULL;
			return topLeftTree->search(p);
		}

		// Indicates botLeftTree
		else {
			if (botLeftTree == NULL)
				return NULL;
			return botLeftTree->search(p);
		}
	}
	else {
		// Indicates topRightTree
		if ((topLeft.y + botRight.y) / 2 > p.y) {
			if (topRightTree == NULL)
				return NULL;
			return topRightTree->search(p);
		}

		// Indicates botRightTree
		else {
			if (botRightTree == NULL)
				return NULL;
			return botRightTree->search(p);
		}
	}
};

// Check if current quadtree contains the point
bool Quad::inBoundary(Point p)
{
    return (p.x >= topLeft.x && p.x <= botRight.x
        && p.y >= topLeft.y && p.y <= botRight.y);
}



void Quad::ReadCsv(string Arch, int lines){

    ifstream archivo(Arch);
    string linea;
    char delimitador = ';';
    char delimitador2 = ',';
    // Leemos la primer línea para descartarla, pues es el encabezado
    getline(archivo, linea);
    getline(archivo, linea);
    // Leemos todas las líneas
    int counter = 0;
    while (counter < lines){
        
        stringstream stream(linea); // Convertir la cadena a un stream
        string Country,City,AccentCity,Region,Population,Latitude,Longitude,geopointA,geopointB;
        // Extraer todos los valores de esa fila
        getline(stream, Country, delimitador);
        getline(stream, City, delimitador);
        getline(stream, AccentCity, delimitador);
        getline(stream, Region, delimitador);
        getline(stream, Population, delimitador);
        getline(stream, Latitude, delimitador);
        getline(stream, Longitude, delimitador);
        getline(stream, geopointA, delimitador2);
        getline(stream, geopointB, delimitador);
        // Imprimir

        double lat = stod(geopointA)*1000000;
        double lon = stod(geopointB)*1000000;
        int pop = stoi(Population);
        int latR = (int)lat;
        int lonR = (int)lon;
        if(latR<0){
            latR = 360000000+latR;
        }
        if(lonR<0){
            lonR = 360000000+lonR;
        }
        
        
        /*cout << "Latitude: " << latR << endl;
        cout << "Longitude: " << lonR << endl;
        */
        Node* aux = new Node(Point(latR,lonR),pop);
        this->insert(aux);
        counter= counter+1;
        getline(archivo, linea);
    }

    archivo.close();
}


int Quad::totalPoints() {
    int count = 0;

    // If the current node contains a point, increment the counter
    if (this->n != nullptr) {
        count = count + 1;
    }

    // Traverse the subtrees and sum the points in each one
    if (topLeftTree != NULL) {
        count = count + topLeftTree->totalPoints();
    }

    if (topRightTree != NULL) {
        count += topRightTree->totalPoints();
    }

    if (botLeftTree != NULL) {
        count = count + botLeftTree->totalPoints();
    }
    if (botRightTree != NULL) {
        count = count + botRightTree->totalPoints();
    }

    return count;
}

int Quad::totalNodes() {
    int count = 1;

    // Traverse the subtrees and sum the nodes in each one
    if (topLeftTree != NULL) {
        count += topLeftTree->totalNodes();
    }
    if (topRightTree != NULL) {
        count += topRightTree->totalNodes();
    }
    if (botLeftTree != NULL) {
        count += botLeftTree->totalNodes();
    }
    if (botRightTree != NULL) {
        count += botRightTree->totalNodes();
    }

    // Increment the counter for the current node
    return count;
}

vector<pair<Point, int>> Quad::list() {
    vector<pair<Point, int>> result;

    // Traverse the subtrees in in-order
    if (topLeftTree != NULL) {
        vector<pair<Point, int>> subList = topLeftTree->list();
        result.insert(result.end(), subList.begin(), subList.end());

    }

    if (n != NULL) {
        result.push_back(make_pair(n->pos, n->data));
        cout << "Point: (" << n->pos.x << ", " << n->pos.y << "), Value: " << n->data << endl;

    }

    if (topRightTree != NULL) {
        vector<pair<Point, int>> subList = topRightTree->list();
        result.insert(result.end(), subList.begin(), subList.end());

    }

    if (botLeftTree != NULL) {
        vector<pair<Point, int>> subList = botLeftTree->list();
        result.insert(result.end(), subList.begin(), subList.end());
 
    }

    if (botRightTree != NULL) {
        vector<pair<Point, int>> subList = botRightTree->list();
        result.insert(result.end(), subList.begin(), subList.end());
  
    }

    return result;
}

int Quad::countRegion(Point p, int u){
    Point a(p.x-u,p.y-u);
    Point b(p.x+u,p.y+u);
    int count=0;

    if(a.x<0){
        a.x=0;
    }
     if(a.y<0){
        a.y=0;
    }

    for(int i = a.x; i<=b.x;i++){
        for(int k = a.y; k<=b.y;k++){
            if(this->search(Point(i,k)) != NULL){
                count++;
            }
        }
    }

    return(count);
}

int Quad::AggregateRegion(Point p, int u){
    Point a(p.x-u,p.y-u);
    Point b(p.x+u,p.y+u);
    int count=0;
    if(a.x<0){
        a.x=0;
    }
     if(a.y<0){
        a.y=0;
    }

    for(int i = a.x; i<=b.x;i++){
        for(int k = a.y; k<=b.y;k++){
            if(this->search(Point(i,k)) != NULL){
                count = count + this->search(Point(i,k))->data;
            }
        }
    }

    return(count);
}

