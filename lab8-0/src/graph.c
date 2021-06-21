#include "graph.h"
#include <limits.h>

TGraph *createGraph(int numberOfEdges, int numberOfVerticies){
	TGraph* graph = calloc(1, sizeof(TGraph));
	graph->numberOfVerticies = numberOfVerticies;
	graph->numberOfEdges = numberOfEdges;
	graph->edges = calloc(numberOfEdges, sizeof(TEdge));
	return graph;
}

TState initializeGraph(TGraph **root, FILE *input){
	TGraph *graph = *root;
	int x = 0, y = 0, length = 0;

	for (int i = 0; i < graph->numberOfEdges; ++i){
		if (fscanf(input, "%d %d %d", &x, &y, &length) != 3){
			return BAD_NUM_OF_LINES;
		}

		if(x > graph->numberOfVerticies || x < 0 || y > graph->numberOfVerticies || y < 0){
			return BAD_VERTEX;
		}

		if(length < 0 || length > INT_MAX){
			return BAD_LENGTH;
		}

		//add edge
		graph->edges[i].x = x;
		graph->edges[i].y = y;
		graph->edges[i].length = length;

	}
	return SUCCESS;
}

void destroyGraph(TGraph **root){
	TGraph *graph = *root;
	free(graph->edges);
	free(graph);
	return;
}
