#include "hash.h"
#include "heap.h"
#include "graph.h"
#include <iostream>
#include <fstream>

using namespace std;

graph::graph(int size){
	nodesEncountered = new hashTable(size);
	orderOfOutput = new list<node *>;
	numberOfVertices = 0;
}
	
void graph::addEdge(const std::string &vertex1, const std::string &vertex2, int weight){
	bool containsV1, containsV2;
	node *v1 = static_cast<node *> (nodesEncountered->getPointer(vertex1, &containsV1));
	node *v2 = static_cast<node *> (nodesEncountered->getPointer(vertex2, &containsV2));
	
	if (!containsV1){

		v1 = new node;
		v1->distToSource = 1000000000;
		v1->vertexId = vertex1;
		v1->parent = NULL;
		nodesEncountered->insert(vertex1, v1);
		orderOfOutput->push_back(v1);
		numberOfVertices++;

	}

	if (!containsV2){

		v2 = new node;
		v2->distToSource = 1000000000;
		v2->vertexId = vertex2;
		v2->parent = NULL;
		nodesEncountered->insert(vertex2, v2);
		orderOfOutput->push_back(v2);
		numberOfVertices++;

	}

	edge *edge_v1v2 = new edge;
	edge_v1v2->dest = static_cast<node *> (nodesEncountered->getPointer(vertex2, &containsV2));
	edge_v1v2->cost = weight;
	v1->adjList.push_back(edge_v1v2);
	
}

int graph::shortestPath(const std::string &startingVertex){
	bool validVertex;
	
	node* startNode = static_cast<node *> (nodesEncountered->getPointer(startingVertex, &validVertex));
	
	if(!validVertex)
		return 0;

	startNode->distToSource = 0;
	heap unknownVertices(numberOfVertices);
	unknownVertices.insert(startingVertex, startNode->distToSource, startNode);
	node* tmpDeletedNode;	

	while (!unknownVertices.deleteMin(NULL, NULL, &tmpDeletedNode)){

		for (list<void *>::iterator it = tmpDeletedNode->adjList.begin(); it != tmpDeletedNode->adjList.end(); it++){
			edge* adjNode = static_cast<edge *> (*it);
			if ((adjNode->dest)->distToSource > tmpDeletedNode->distToSource + adjNode->cost){
				(adjNode->dest)->distToSource = tmpDeletedNode->distToSource + adjNode->cost;
				(adjNode->dest)->parent = tmpDeletedNode;
				unknownVertices.insert((adjNode->dest)->vertexId, (adjNode->dest)->distToSource, adjNode->dest);

			}
		}	
	}

	return 1;
}

int graph::output(ofstream &outFile){
	for (list<node *>::iterator it = orderOfOutput->begin(); it != orderOfOutput->end(); it++){
		list<string> parentArray;
		node* parentNode = (*it);
		
		if ((*it)->distToSource != 1000000000){
			outFile << (*it)->vertexId << ": " << (*it)->distToSource;

			while (parentNode != NULL){
				parentArray.push_front(parentNode->vertexId);
				parentNode = parentNode->parent;
			}

			outFile << " [";

			while (!parentArray.empty()){
				outFile << parentArray.front();
				parentArray.pop_front();

				if (!parentArray.empty())
					outFile << ", ";

			}

			outFile << "]" <<  endl;

		} else {
			outFile << (*it)->vertexId << ": NO PATH" << endl;
		
		}
	}
	return 1;
}