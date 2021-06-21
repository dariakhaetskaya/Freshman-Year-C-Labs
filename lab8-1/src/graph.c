#include "graph.h"

TGraph *createGraph(int numberOfVertices){
	numberOfVertices++;
	TGraph* newGraph = (TGraph* )calloc(1, sizeof(TGraph));
	newGraph->adjMatrix = (int**)calloc(numberOfVertices, sizeof(int*));
	for (int i = 0; i < numberOfVertices; i++){
		newGraph->adjMatrix[i] = (int*)calloc(numberOfVertices, sizeof(int));
	}
	newGraph->numberOfVertices = numberOfVertices;
	return newGraph;
}

TState initializeGraph(TGraph *graph, FILE *input, int numberOfEdges){

	int x = 0, y = 0, length = 0;

	for (int i = 0; i < numberOfEdges; ++i){
		if (fscanf(input, "%d %d %d", &x, &y, &length) != 3){
			return BAD_NUM_OF_LINES;
		}

		if(x > graph->numberOfVertices - 1 || x < 0 || y > graph->numberOfVertices - 1 || y < 0){
			return BAD_VERTEX;
		}

		if(length < 0 || length > INT_MAX){
			return BAD_LENGTH;
		}

		//add edge
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
