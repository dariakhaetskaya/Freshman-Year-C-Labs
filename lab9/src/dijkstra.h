#ifndef GRAPH_H
#define GRAPH_H

#include "graph.h"

typedef struct TVertex{
	int parent;
	unsigned int path;
	bool visited;
}TVertex;

int FindMin(TVertex *vertices, int numberOfVerticies, unsigned int src);

void InitializeVertices(TVertex* arrayPtr, int numberOfVertices);

TState DijkstraAlgorithm(TGraph* graphPtr, TVertex *vertices, unsigned int src, unsigned int dest);

void PrintPath(FILE* output, TVertex *vertices, unsigned int idx);

void PrintDist(FILE* output, TVertex *vertices, int numberOfVertices);

#endif
