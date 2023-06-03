#ifndef QUEADTREE_H_
#define QUEADTREE_H_

#include <iostream>
using namespace std;

class QuadTree{
private:
public:
    
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
    int data = 0;
	int hasSons = 0;
	int isPoint = 0;
    Point Upper; 
    Point Lower; 
    Node* next; 
    Node* topRight = nullptr; 
    Node* topLeft= nullptr;
	Node* botRight= nullptr;
	Node* botLeft= nullptr;

    Node(Point a, Point b){
	  this->Upper = a;
      this->Lower = b; 
    }


	bool isInRange(Point targetPos){
			if(targetPos.x >= this->Upper.x  && targetPos.x<=this->Lower.x && targetPos.y >= Upper.y && targetPos.y <= Lower.y){
				return true;
			}
			else{
				cout << "Fuera de rango bitch" << endl;
				return false;
			}
            return false;
    }
    
	void insert(Point p, int data){
		if(isInRange(p)){
			if(Upper.x == Lower.x && Upper.y==Lower.y){
				this->isPoint = 1;
				this->data = data;
			}
			else if(hasSons==0){
				int cuad1y= (Lower.y+Upper.y)/2;
				int cuad1x = (Lower.x+Upper.x)/2;
				Point cuad1b(cuad1x,cuad1y);
				int cuad2xA=(Upper.x+Lower.x)/2+1;
				int cuad2yA=Upper.y;
				Point cuad2A(cuad2xA,cuad2yA);
				int cuad2xB=Lower.x;
				int cuad2yB=(Upper.y+Lower.y)/2;
				Point cuad2B(cuad2xB,cuad2yB);
				Point cuad3A(Upper.x,cuad1y+1);
				Point cuad3B(cuad1x,Lower.y);
				Point cuad4A(cuad2xA,cuad2yB+1);
				this->topRight= new Node(this->Upper,cuad1b);
				this->topLeft = new Node(cuad2A,cuad2B);
				topRight->next= topLeft;
				this->botRight =new Node(cuad3A,cuad3B);
				topLeft->next = botRight;
				this->botLeft = new Node(cuad4A,Lower);
				botRight->next = botLeft;
				hasSons = 1;
				if(topRight->isInRange(p)){
					topRight->insert(p,data);
				}
				else if(topLeft->isInRange(p)){
					topLeft->insert(p,data);
				}
				else if(botLeft->isInRange(p)){
					botLeft->insert(p,data);
				}
				else if(botRight->isInRange(p)){
					botRight->insert(p,data);
				}
			}
			else if(hasSons==1){
				if(topRight->isInRange(p)){
					topRight->insert(p,data);
				}
				else if(topLeft->isInRange(p)){
					topLeft->insert(p,data);
				}
				else if(botLeft->isInRange(p)){
					botLeft->insert(p,data);
				}
				else if(botRight->isInRange(p)){
					botRight->insert(p,data);
				}
		}

		}
	 else{
		cout << "nO esta en rango kkkk" << endl;
	 }
	}
    
    ~Node(){
      delete next;
      delete topRight;
	  delete topLeft;
	  delete botRight;
	  delete botLeft;
    }


    void link(Node* a, Node* b){
      if(a->isRes == 0){
        a->next = b;
      }
      else{
          Node* union1 = a;
          Node* union2 = b;
            while(union1->right != nullptr && union2->left !=nullptr){
            union1 = union1->right;
            union2 = union2->left;
           }
          union1->next = union2;
        }
      }

    Node* duplicate(){
        if(this->left->isRes == 0){
           Node* aux1 = new Node(this->left->tam);
           Node* aux2 = new Node(this->left->tam);
           Node* dup = new Node(aux1,aux2);
           return(dup);
        }
        else{
           Node* source_leftcopy = this->left->duplicate();
           Node* source_rightcopy = this->right->duplicate();
           Node* dup = new Node(source_leftcopy,source_rightcopy);
           dup->link(dup->left,dup->right);
          return(dup);
        } 
}

void exchange(Node*& tree, Node* newer){
   tree = newer;
}

};


 Point topLeft;
 Point botRight;
 Node* n;


//public:
    QuadTree(int size);
   ~QuadTree();
	virtual int totalPoints() ;
    virtual int totalNodes() ;
    virtual void insert(Point p, int data) ;
    virtual void list() ;
	virtual int countRegion(Point p, int d);
    virtual int AggregateRegion(Point p, int d) ;

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