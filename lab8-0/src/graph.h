#include <stdlib.h>
#include <stdio.h>

typedef enum TState { BAD_NUM_OF_LINES, BAD_LENGTH,
						 BAD_VERTEX, SUCCESS, NO_SPANNING_TREE} TState;

typedef struct TEdge{
	int x;
	int y;
	int length;
}TEdge;

typedef struct TGraph{
	int numberOfVerticies;
	int numberOfEdges;
	TEdge *edges;
}TGraph;

TGraph *createGraph(int numberOfEdges, int numberOfVerticies);
TState initializeGraph(TGraph **graph, FILE *input);
void destroyGraph(TGraph **graph);
