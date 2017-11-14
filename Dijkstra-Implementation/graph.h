#ifndef _GRAPH_H
#define _GRAPH_H
#include "hash.h"
#include <list>
#include <fstream>

class graph {
public:
	
	graph(int size);

	void addEdge(const std::string &vertex1, const std::string &vertex2, int weight);

	int shortestPath(const std::string &startingVertex);

	int output(std::ofstream &outFile);

private:
	class node {
	public:
		std::list<void *> adjList; // for graph node
		std::string vertexId;
		int distToSource;
		bool known;
		node *parent;
	};

	class edge {
	public:
		int cost; // for adjacency list node (edge 'node')...
		node *dest;
	};
	
	std::list<node *> *orderOfOutput;

	hashTable *nodesEncountered;

	int numberOfVertices;

};

#endif