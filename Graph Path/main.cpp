#include "graph.h"
#include <fstream>
#include <iostream>
using namespace std;

int main() {
	const char* filename = "g8.txt";
	ifstream inFile(filename);
	int vertices = 0;
	inFile >> vertices;
	int edges = 0;
	inFile >> edges;
	
	Graph g(vertices + 1);
	int u = 0;
	int v = 0;
	while(!inFile.eof()) {
		inFile >> u;
		inFile >> v;
		g.addEdge(u, v);
		g.addListEdge(u,v);
	}
	
	cout << "Matrix: " << endl;
    g.out();
	cout << endl << "List: " << endl;
	g.Listout();
	cout << endl;
	
	bool possible = g.strokeBool();
	
	if (possible == false) {
		cout << "The graph is not possible to be drawn in one stroke." << endl;
	} else {
		cout << "The graph is possible to be drawn in one stroke." << endl;
		
		int travStart = g.getStart();
		cout << "We should start at vertex " << travStart << "." << endl;
		
		g.printPath(travStart);
	}
}