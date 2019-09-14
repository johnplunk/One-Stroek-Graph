#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;

class Graph {
	private:
	int numVertices;
    int** adjacencyMat;
	int** adjacencyList;
	bool traversalPicky = false;
	int traversalStart = 1;
	vector<int> stack;
	public:
    Graph(int numVertices) {
		this->numVertices = numVertices;
        adjacencyMat = new int*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjacencyMat[i] = new int[numVertices];
            for (int j = 0; j < numVertices; j++) {
                adjacencyMat[i][j] = 0;
			}
		}
		
		adjacencyList = new int*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjacencyList[i] = new int[numVertices];
            for (int j = 0; j < numVertices; j++) {
                adjacencyList[i][j] = 0;
			}
		}
	}
	
	~Graph() {
		for (int i = 0; i < numVertices; i++) {
			delete[] adjacencyMat[i];
		}
		delete[] adjacencyMat;
	}
	
    void addEdge(int i, int j) {
		adjacencyMat[i][j] = 1;
		adjacencyMat[j][i] = 1;
	}
	
	void addListEdge(int i, int j) {
		adjacencyList[i][j] = j;
		adjacencyList[j][i] = i;
	}
	
    void removeEdge(int i, int j) {
		adjacencyMat[i][j] = 0;
		adjacencyMat[j][i] = 0;
	}
	
    bool isEdge(int i, int j) {
		return adjacencyMat[i][j];
	}
	
	void printPath(int u) {
		for(int i = 1; i < numVertices; i++) {
			if (adjacencyMat[i][u] != 0 && isValidNextEdge(u,i)) {
				cout << u << "-" << i << " ";
				removeEdge(u,i);
				printPath(i);
			}
		}
	}
	
	bool isValidNextEdge(int u, int v) {
		int count = 0;
		for (int i = 1; i < numVertices; i++) {
			if (adjacencyMat[i][u] != 0) {
				count++;
			}
		}
		if (count = 1) {
			return true;
		}
		
		bool visited[numVertices];
		memset(visited, false, numVertices);
		int count1 = DFSCount(u, visited);
		
		removeEdge(u,v);
		memset(visited, false, numVertices);
		int count2 = DFSCount(u, visited);
		
		addEdge(u,v);
		
		return (count1 > count2)? false: true;
	}
	
	int DFSCount(int u, bool visited[]) {
		visited[u] = true;
		int count = 1;
		
		for (int i = 1; i < numVertices; i++) {
			if (adjacencyMat[i][u] != 0 && !visited[i]) {
				count += DFSCount(i, visited);
			}
		}
		
		return count;
	}
	
	
	bool strokeBool() {
		bool possible = false;
		int oddDegrees = 0;
		int evenDegrees = 0;
		for (int j = 1; j < numVertices; j++) {
			int count = 0;
			for (int i = 0; i < numVertices; i++) {
				count = count + adjacencyMat[i][j];
			}
			if (count % 2 == 0) {
				evenDegrees++;
			} else {
				oddDegrees++;
				traversalStart = j;
			}
		}
		if (oddDegrees == 0) {
			possible = true;
		} else if (oddDegrees == 2) {
			possible = true;
			traversalPicky = true;
		}
		return possible;
	}
	
	int getStart() {
		return traversalStart;
	}
	
    void out() {
		for (int i = 1; i < numVertices; i++) {
			cout << i << " ";
			for (int j = 1; j < numVertices; j++) {
					cout << adjacencyMat[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	void Listout() {
		for (int i = 1; i < numVertices; i++) {
			cout << i;
			for (int j = 1; j < numVertices; j++) {
				if (adjacencyList[i][j] != 0) {
					cout << "->" << adjacencyList[i][j];
				}
			}
			cout << endl;
		}
	}
};




