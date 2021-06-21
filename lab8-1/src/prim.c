#include "prim.h"

#define root -1
#define undefined -2

int findMin(TVertex *vertices, int numberOfVerticies){
	long long int min = (long long int) INT_MAX + 1;
	int minIndex = 1;

	for (int i = 1; i < numberOfVerticies; i++){
		if (vertices[i].visited == false && vertices[i].weight < min){
			min = vertices[i].weight;
			minIndex = i;
		}
	}
	return minIndex;
}

bool isConnected(TGraph* graph){
	bool emptyString = true;
	for (int i = 1; i < graph->numberOfVertices; i++){
		emptyString = true;
		for (int j = 1; j < graph->numberOfVertices; ++j){
			if (graph->adjMatrix[i][j]){
				emptyString = false;
			}
		}
	}

	return !emptyString;
}

void initializeVertices(TVertex* vertices, int numberOfVertices){
	for (int i = 1; i < numberOfVertices; i++){
		vertices[i].weight = INT_MAX;
		vertices[i].visited = 0;
		vertices[i].parent = undefined;
	}
}

TState PrimSpanningTree(TGraph* graph, TVertex *vertices){

	if(!isConnected(graph) && graph->numberOfVertices - 1 != 1){
		return NO_SPANNING_TREE;
	}
	
	int numberOfVertices = graph->numberOfVertices;

	vertices[1].weight = 0;
	vertices[1].parent = root;

	int currentVertexWeight = 0;

	for (int i = 1; i < numberOfVertices; i++){
		int currentVertexIdx = findMin(vertices, numberOfVertices);
		
		vertices[currentVertexIdx].visited = true;

		for (int j = 1; j < numberOfVertices; j++){

			currentVertexWeight = graph->adjMatrix[currentVertexIdx][j];

			if (currentVertexWeight != 0){
				if (!vertices[j].visited && currentVertexWeight <= vertices[j].weight){
				vertices[j].parent = currentVertexIdx;
				vertices[j].weight = currentVertexWeight;
				}
			}
		}

	}
	return SUCCESS;
}

void PrintTree(FILE* output, TVertex *vertices, int numberOfVertices){

	for (int i = 2; i < numberOfVertices; i++){
		fprintf(output, "%d %d\n", vertices[i].parent, i);
	}
}
