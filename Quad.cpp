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


// Metodo de insercion 
void Quad::insert(Node* node)
{
    if (node == NULL)
        return;
 
    // Revisa que el nodo a insertar tenga coordenadas que caben dentro de la cuadricula
    if (!inBoundary(node->pos))
        return;
 
    //QuadTree de tamaño 1 o "punto"
    if (abs(topLeft.x - botRight.x) <= 1
        && abs(topLeft.y - botRight.y) <= 1) {
        //si el QuadTree en que se quiere insertar no esta ocupado incerta el nodo en esa posicion
        if (n == NULL){
            n = node;
        return;
        }
        //else{
          //cout << "Error. Ingrese otro valor: " << n->pos.x <<" "  << n ->pos.y << endl;

       // }
    }
    //Señala la mitad izquierda del Quadtree
    if ((topLeft.x + botRight.x) / 2 > node->pos.x) {
        //Verifica si el punto pertenece al Quadtree superior izquierdo
        if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
            if (topLeftTree == NULL){
                //Si no existe un hijo en ese cuadrante le asigna nuevos hijos al QuadTree y despues ejecuta insert() en el 
                //hijo correspontiente (funciona de forma recursiva) 
                topLeftTree = new Quad(Point(topLeft.x, topLeft.y),Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2));
                botLeftTree = new Quad(Point(topLeft.x,(topLeft.y + botRight.y) / 2),Point((topLeft.x + botRight.x) / 2,botRight.y));
                topRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,topLeft.y),Point(botRight.x,(topLeft.y + botRight.y) / 2));
                botRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),Point(botRight.x, botRight.y));
            }
            topLeftTree->insert(node);
        }
 
        //Verifica si el punto pertenece al Quadtree inferior izquierdo
        else {
            if (botLeftTree == NULL){
                //Si no existe un hijo en ese cuadrante le asigna nuevos hijos al QuadTree y despues ejecuta insert() en el 
                //hijo correspontiente (funciona de forma recursiva) 
               topLeftTree = new Quad(Point(topLeft.x, topLeft.y),Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2));
                botLeftTree = new Quad(Point(topLeft.x,(topLeft.y + botRight.y) / 2),Point((topLeft.x + botRight.x) / 2,botRight.y));
                topRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,topLeft.y),Point(botRight.x,(topLeft.y + botRight.y) / 2));
                botRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),Point(botRight.x, botRight.y));
            }
            botLeftTree->insert(node);
        }
    }
    //Señala la mitad derecha del Quadtree
    else {
        //Verifica si el punto pertenece al Quadtree superior derecho
        if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
            if (topRightTree == NULL){
                //Si no existe un hijo en ese cuadrante le asigna nuevos hijos al QuadTree y despues ejecuta insert() en el 
                //hijo correspontiente (funciona de forma recursiva) 
                topLeftTree = new Quad(Point(topLeft.x, topLeft.y),Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2));
                botLeftTree = new Quad(Point(topLeft.x,(topLeft.y + botRight.y) / 2),Point((topLeft.x + botRight.x) / 2,botRight.y));
                topRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,topLeft.y),Point(botRight.x,(topLeft.y + botRight.y) / 2));
                botRightTree = new Quad(Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),Point(botRight.x, botRight.y));
            }
            topRightTree->insert(node);
        }
 
        //Verifica si el punto pertenece al Quadtree inferior derecho
        else {
            if (botRightTree == NULL){
                //Si no existe un hijo en ese cuadrante le asigna nuevos hijos al QuadTree y despues ejecuta insert() en el 
                //hijo correspontiente (funciona de forma recursiva) 
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
	//El QuadTree no puede contener ese punto
	if (!inBoundary(p))
		return NULL;

	//Estamos en un "Punto" o QuadTree de tamaño 1
	if (n != NULL){
		return n;
    }

	if ((topLeft.x + botRight.x) / 2 > p.x) {
		//Verifica si el punto que se busca pertenece al Quadtree superior izquierdo
		if ((topLeft.y + botRight.y) / 2 > p.y) {
			if (topLeftTree == NULL){
                //si el punto deberia de estar en este cuadrante pero este hijo no existe retorna nulo, ya que significa que no existe un 
                // elemento dentro del QuadTree que se encuentre cordenadas
				return NULL;
            }
			return topLeftTree->search(p);
		}

		//Verifica si el punto que se busca pertenece al Quadtree inferior izquierdo
		else {
			if (botLeftTree == NULL){
				return NULL;
            }
			return botLeftTree->search(p);
		}
	}
	else {
		//Verifica si el punto que se busca pertenece al Quadtree superior derecho
		if ((topLeft.y + botRight.y) / 2 > p.y) {
			if (topRightTree == NULL){
				return NULL;
                }
			return topRightTree->search(p);
		}

		//Verifica si el punto que se busca pertenece al Quadtree inferior derecho
		else {
			if (botRightTree == NULL){
				return NULL;
                }
			return botRightTree->search(p);
		}
	}
};

// Verifica si el QuadTree contiene el punto indicado
bool Quad::inBoundary(Point p)
{
    //verifica que las coordenadas en x e y del punto sean mayores o iguales que las del limite superior izquierdo
    // y menores o iguales que el limite inferior derecho
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
        //convierte el string del geopoint en doubles y los multiplica por 1.000.000 para
        // eliminar decimales
        double lat = stod(geopointA)*1000000;
        double lon = stod(geopointB)*1000000;
        //despues convierte los doubles en enteros, asi pueden crearse puntos que reprecenten estas coordenadas
        int pop = stoi(Population);
        int latR = (int)lat;
        int lonR = (int)lon;
        //si alguna de las coordenadas es negativa le suma 360 millones ya que estamos convirtiendo las
        //coordenadas de longitud y latitud de -180 a 180° a 360 grados, entonces si alguna coordenada
        //es negativa le suma el 360(por el factor de 1 millon que usamos para que quepan todos los puntos)
        //ej: -1° pasa a ser 359°
        if(latR<0){
            latR = 360000000+latR;
        }
        if(lonR<0){
            lonR = 360000000+lonR;
        }
        
        
        /*cout << "Latitude: " << latR << endl;
        cout << "Longitude: " << lonR << endl;
        */

       //crea un nodo que tenga la longitud y latitud como coordenadas x e y, y que almacena como un entero
       //la poblacion de la ciudad que se esta insertando
        Node* aux = new Node(Point(latR,lonR),pop);
        this->insert(aux);
        counter= counter+1;
        getline(archivo, linea);
    }

    archivo.close();
    //cierra el archivo de texto
}


int Quad::totalPoints() {
    //inicia el contador
    int count = 0;

    // Si el nodo actual contiene un punto suma 1 al conteo
    if (this->n != nullptr) {
        count = count + 1;
    }

    // recorre los subTrees y suma su numero de puntos al conteo
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
    //retorna el conteo total
    return count;
}

int Quad::totalNodes() {
    //inicia el conteo en 1 para tomar en cuenta el QuadTree raiz
    int count = 1;

    // recorre los subTrees y suma su numero de nodos al conteo
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

   //retorna el conteo total
    return count;
}

//imprime todos los puntos contenidos en el QuadTree, dando sus coordenadas y el valor que almacenan
vector<pair<Point, int>> Quad::list() {
    //crea un vector que almacene un par punto,entero
    vector<pair<Point, int>> result;

    // Recorre los subArboles en un recorrido inOrder
    if (topLeftTree != NULL) {
        //Si el hijo superior izquierdo no es nulo aplica el metodo de manera recursiva sobre este
        //y despues añade los puntos encontrados al Vector
        vector<pair<Point, int>> subList = topLeftTree->list();
        result.insert(result.end(), subList.begin(), subList.end());

    }

    if (n != NULL) {
        //Si el QuadTree actual es un punto retorna sus coordenadas y el valor almacenado
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
    //retorna el vector
    return result;
}

//retorna la cantidad de puntos en un area especificada
int Quad::countRegion(Point p, int u){
    //verifica si el punto central sobre el que se va a buscar esta dentro de los limites del QuadTree
    //en caso de que no sea asi retorna 0
    if( inBoundary(p)== false){
        return(0);
    }
    
    
    //Toma el punto y perimetro dado y crea un limite superior izquierdo
    //E inferior derecho que serian el area sobre la que se esta haciendo el conteo
    Point a(p.x-u,p.y-u);
    Point b(p.x+u,p.y+u);
    int count=0;
    //si alguna de las coordenadas de los puntos se sale de los limites del Quadtree
    //los transforma en los limites correspondientes de la cuadricula
    if(a.x<0){
        a.x=0;
    }
     if(a.y<0){
        a.y=0;
    }
    if(b.x > this->botRight.x){
        b.x=this->botRight.x;
    }
     if(b.y > this->botRight.y){
        b.y=this->botRight.y;
    }
    //ejecuta el metodo search() sobre todas las coordenadas posibles del perimetro especificado
    for(int i = a.x; i<=b.x;i++){
        for(int k = a.y; k<=b.y;k++){
            //si encuentra un punto lo añade al conteo
            if(this->search(Point(i,k)) != NULL){
                count++;
            }
        }
    }
    //retorna el conteo final
    return(count);
}
//retorna la suma de los valores almacenados en cada punto en un area especificada
//este metodo funciona de manera analoga al anterior pero en vez de sumar los puntos
//suma el valor almacenado en esas coordenadas y las suma a un contador
//despues retorna el valor final del contador
int Quad::AggregateRegion(Point p, int u){
    if( inBoundary(p)== false){
        return(0);
    }
    Point a(p.x-u,p.y-u);
    Point b(p.x+u,p.y+u);
    int count=0;
    if(a.x<0){
        a.x=0;
    }
     if(a.y<0){
        a.y=0;
    }
    if(b.x > this->botRight.x){
        b.x=this->botRight.x;
    }
     if(b.y > this->botRight.y){
        b.y=this->botRight.y;
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

