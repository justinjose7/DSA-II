#include "hash.h"
#include "heap.h"
#include "graph.h"
#include "time.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int main() {
	string startVertex, inFilename, outFilename, line, v1, v2;
	int weight;
	graph mygraph(10000000);


	cout << "Enter name of graph file: ";
	getline(cin, inFilename);
	ifstream inFile;
	inFile.open(inFilename.c_str());

	while(std::getline(inFile, line)){
		stringstream eachLine(line);
		eachLine >> v1 >> v2 >> weight;
		mygraph.addEdge(v1, v2, weight);
	}

	cout << "Enter a valid vertex id for the staring vertex: ";
	getline(cin, startVertex);

	clock_t t;
	t = clock();
	while (!mygraph.shortestPath(startVertex)){
		cout << "Invalid vertex. Try again: ";
		getline(cin, startVertex);
	}
	t = clock() - t;
	cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << ((float)t)/CLOCKS_PER_SEC << endl;

	cout << "Enter name of output file: ";
	getline(cin, outFilename);
	ofstream outputFile;
	outputFile.open(outFilename.c_str());
	mygraph.output(outputFile);

}
	