#include "dijkstra.h"

#define ROOT -1
#define UNDEFINED -2

int findMin(TVertex *vertices, int numberOfVerticies, unsigned int src){
	long long int unsigned min = (long long unsigned int) UINT_MAX;
	unsigned int minIndex = src;

	for (int i = 1; i < numberOfVerticies; i++){
		if (vertices[i].visited == false && vertices[i].path < min){
			min = vertices[i].path;
			minIndex = i;
		}
	}
	return minIndex;
}

void InitializeVertices(TVertex* vertices, int numberOfVertices){
	for (int i = 1; i < numberOfVertices; i++){
		vertices[i].path = UINT_MAX;
		vertices[i].visited = false;
		vertices[i].parent = UNDEFINED;
	}
}

TState DijkstraAlgorithm(TGraph* graph, TVertex *vertices, unsigned int src, unsigned int dest){
	vertices[src].visited = true;
	vertices[src].path = 0;
	vertices[src].parent = ROOT;

	bool isConnected = false;

	for (int i = 1; i < graph->numberOfVertices; i++){
		if(graph->adjMatrix[i][dest] != 0){
			isConnected = true;
		}
	}

	if (!isConnected && dest != src){
		return NO_PATH;
	}

	int numberOfVertices = graph->numberOfVertices;

	int currentVertexWeight = 0;
	short countOverflow = 0;

	for (int i = 1; i < numberOfVertices; i++){
		int currentVertexIdx = findMin(vertices, numberOfVertices, src);

		vertices[currentVertexIdx].visited = true;

		for (int j = 1; j < numberOfVertices; j++){

			currentVertexWeight = graph->adjMatrix[currentVertexIdx][j];

			if (currentVertexWeight != 0){
				if (!vertices[j].visited && vertices[currentVertexIdx].path != UINT_MAX
					&& (vertices[currentVertexIdx].path + graph->adjMatrix[currentVertexIdx][j]) < vertices[j].path){
					vertices[j].parent = currentVertexIdx;
					vertices[j].path = currentVertexWeight + vertices[currentVertexIdx].path;
					if(vertices[j].path >= INT_MAX){
						countOverflow++;
					}
				}
			}
		}
	}

	if (vertices[dest].visited == false){
		return NO_PATH;
	}

	if (countOverflow > 2 && vertices[dest].path > INT_MAX){
		return LARGER_INT_MAX;
	}

	return SUCCESS;
}

void PrintDist(FILE* output, TVertex *vertices, int numberOfVertices){

	for (int i = 1; i <= numberOfVertices; i++){
		fprintf(stderr, "%d: %d\n", i, vertices[i].visited);
	}

	for (int i = 1; i <= numberOfVertices; i++){
		if (vertices[i].visited){
			if (vertices[i].path > INT_MAX){
					fprintf(output, "INT_MAX+ ");
				} else {
					fprintf(output, "%u ", vertices[i].path);
			}
		} else {
			fprintf(output, "oo ");
		}
	}
	fprintf(output, "\n");
}

void PrintPath(FILE* output, TVertex *vertices, unsigned int idx){
	fprintf(output, "%u ", idx);
	if (vertices[idx].parent == ROOT){
		fprintf(output, "\n");
		return;
	}
	PrintPath(output, vertices, vertices[idx].parent);
}
