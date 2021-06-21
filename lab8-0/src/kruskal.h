#include "graph.h"

typedef struct TSubSet{
	int rank;
	int origin;
}TSubSet;

TState KruskalSpanningTree(TGraph **graph, TEdge *spannigTpee);
void printSpanningTree(FILE* output, TEdge *spanningTree, int numberOfEdges);
