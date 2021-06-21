#include "graph.h"

typedef struct TVertex{
	int parent;
	int weight;
	bool visited;
}TVertex;

int findMin(TVertex *vertices, int numberOfVerticies);

void initializeVertices(TVertex* arrayPtr, int numberOfVertices);

TState PrimSpanningTree(TGraph* graphPtr, TVertex *vertices);

void PrintTree(FILE* output, TVertex *arrayPtr, int numberOfVertices);
