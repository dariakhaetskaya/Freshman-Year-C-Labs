#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef enum TState { BAD_NUM_OF_LINES, BAD_LENGTH, BAD_VERTEX, SUCCESS, 
		NO_SPANNING_TREE, READ_FALURE, BAD_NUM_OF_VERT, BAD_NUM_OF_EDGES} TState;

typedef struct TGraph{
	int **adjMatrix;
	int numberOfVertices;
}TGraph;

TGraph *createGraph(int numberOfVerticies);

TState initializeGraph(TGraph *graph, FILE *input, int numberOfEdges);

void destroyGraph(TGraph *graph);
