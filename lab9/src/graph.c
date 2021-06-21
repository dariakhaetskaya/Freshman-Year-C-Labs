#include "graph.h"

TGraph *createGraph(int numberOfVertices){
	numberOfVertices++;
	TGraph* newGraph = (TGraph* )calloc(1, sizeof(TGraph));
	newGraph->adjMatrix = (unsigned int**)calloc(numberOfVertices, sizeof(unsigned int*));
	for (int i = 0; i < numberOfVertices; i++){
		newGraph->adjMatrix[i] = (unsigned int*)calloc(numberOfVertices, sizeof(unsigned int));
	}
	newGraph->numberOfVertices = numberOfVertices;
	return newGraph;
}

TState InitializeGraph(TGraph *graph, FILE *input, int numberOfEdges){

	int x = 0, y = 0, length = 0;

	for (int i = 0; i < numberOfEdges; ++i){
		if (fscanf(input, "%d %d %d", &x, &y, &length) != 3){
			return BAD_NUM_OF_LINES;
		}

		if(x > graph->numberOfVertices || x < 1 || y > graph->numberOfVertices || y < 1){
			return BAD_VERTEX;
		}

		if(length < 0 || length > INT_MAX){
			return BAD_LENGTH;
		}

		graph->adjMatrix[x][y] = length;
		graph->adjMatrix[y][x] = length;

	}
	return SUCCESS;
}

void destroyGraph(TGraph *graph){
	for (int i = 0; i < graph->numberOfVertices; i++){
		free(graph->adjMatrix[i]);
	}
	free(graph->adjMatrix);
	free(graph);
}
