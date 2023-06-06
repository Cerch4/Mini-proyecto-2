// C++ Implementation of Quad Tree
#include "QuadTree.h"
#include <cmath>
#include <iostream>
using namespace std;

// Used to hold details of a point

// The main quadtree class
QuadTree::QuadTree(Point a, Point b){
	// Hold details of the boundary of this node
	UpperLim= a;
	LowerLim = b;

}

QuadTree::~QuadTree(){
	 delete topRight;
	 delete topLeft;
	 delete botRight;
	 delete botLeft;
}

void QuadTree::insert(Node* n){
	if(inBoundary(n->point)){
			if(UpperLim.x == LowerLim.x && UpperLim.y==LowerLim.y && this->dat==nullptr){
				cout << "succes"<< endl;
				this->isPoint = 1;
				this->dat = n;
				
			}
			if(hasSons==false){
				cout <<"succ" << endl;
				int cuad1y= (LowerLim.y+UpperLim.y)/2;
				int cuad1x = (LowerLim.x+UpperLim.x)/2;
				Point cuad1b(cuad1x,cuad1y);
				int cuad2xA=(UpperLim.x+LowerLim.x)/2+1;
				int cuad2yA=UpperLim.y;
				Point cuad2A(cuad2xA,cuad2yA);
				int cuad2xB=LowerLim.x;
				int cuad2yB=(UpperLim.y+LowerLim.y)/2;
				Point cuad2B(cuad2xB,cuad2yB);
				Point cuad3A(UpperLim.x,cuad1y+1);
				Point cuad3B(cuad1x,LowerLim.y);
				Point cuad4A(cuad2xA,cuad2yB+1);
				this->topRight>= new QuadTree(this->UpperLim,cuad1b);
				this->topLeft = new QuadTree(cuad2A,cuad2B);
				topRight->next= topLeft;
				this->botRight =new QuadTree(cuad3A,cuad3B);
				topLeft->next = botRight;
				this->botLeft = new QuadTree(cuad4A,this->LowerLim);
				botRight->next = botLeft;
				hasSons = true;
				if(topRight->inBoundary(n->point)){
					topRight->insert(n);
				}
				if(topLeft->inBoundary(n->point)){
					topLeft->insert(n);
				}
				if(botLeft->inBoundary(n->point)){
					botLeft->insert(n);
				}
				if(botRight->inBoundary(n->point)){
					botRight->insert(n);
				}
			}
			else if(hasSons==true){
				cout <<"succ2" << endl;
				if(topRight->inBoundary(n->point)){
					topRight->insert(n);
				}
				if(topLeft->inBoundary(n->point)){
					topLeft->insert(n);
				}
				if(botLeft->inBoundary(n->point)){
					botLeft->insert(n);
				}
				if(botRight->inBoundary(n->point)){
					botRight->insert(n);
				}
		}

		}
	}


// Find a node in a quadtree
bool QuadTree::search(Point p){
try{
	if(inBoundary(p)== false) throw " Nuh uh fuera de limites";
	if(this->isPoint==1 && this->UpperLim.x==p.x && this->UpperLim.y==p.y){
			return true;
	}
	else if (isPoint!=1 || this==nullptr){
		
		if(topRight->inBoundary(p)){
			topRight->search(p);
			}
		else if(this->topLeft->inBoundary(p)){
			topLeft->search(p);;
			}
		else if(this->botRight->inBoundary(p)){
			botRight->search(p);;
			}
		else if(this->botLeft->inBoundary(p)){
			botLeft->search(p);;
			}
	}
return false;
}
catch(const char* message){
        std::cerr << message << std::endl;
        exit(EXIT_FAILURE);
}
	
}

// Check if current quadtree contains the point
int QuadTree::inBoundary(Point p)
{
	return (p.x >= UpperLim.x && p.x <= LowerLim.x && p.y >= UpperLim.y && p.y <= LowerLim.y);
}


void QuadTree::List(){
    if (this == nullptr) {
    }
	else if(isPoint == 1){
		cout << dat->data << " ";	
	}
	else{
	topRight->List();
	topLeft->List();
	botRight->List();
	botLeft->List();

	}
}

// Driver program

