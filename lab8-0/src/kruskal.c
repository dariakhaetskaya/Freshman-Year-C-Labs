#include "kruskal.h"

static int isGreater(const void *a, const void *b){
	TEdge *aEdge = (TEdge*)a;
	TEdge *bEdge = (TEdge*)b;
	return aEdge->length > bEdge->length;
}

static int findSet(TSubSet *subsets, int e){
	if (subsets[e].origin != e){
		subsets[e].origin = findSet(subsets, subsets[e].origin);
	}
	return subsets[e].origin;
}

static void Merge(TSubSet *subsets, int x, int y){
	int originX = findSet(subsets, x);
	int originY = findSet(subsets, y);

	if(subsets[originY].rank > subsets[originX].rank){
		subsets[originX].origin = originY;
	}

	if(subsets[originY].rank < subsets[originX].rank){
		subsets[originY].origin = originX;
	}

	if(subsets[originY].rank == subsets[originX].rank){
		subsets[originX].origin = originY;
		subsets[originY].rank++;
	}
}

TState KruskalSpanningTree(TGraph **root, TEdge *spanningTree){
	TGraph *graph = *root;
	int numberOfVerticies = graph->numberOfVerticies;
	int numberOfEdges = graph->numberOfEdges;
	qsort(graph->edges, graph->numberOfEdges, sizeof(TEdge), isGreater);

	TSubSet *subsets = (TSubSet*) malloc((numberOfVerticies + 1) * sizeof(TSubSet));

	for(int i = 0; i < numberOfVerticies + 1; i++){
		subsets[i].origin = i;
		subsets[i].rank = 0;
	}

	int i = 0, countSpanning = 0;
	TEdge currentEdge;

	while ((i < numberOfEdges) && (countSpanning < numberOfVerticies - 1)){

		currentEdge = graph->edges[i];

		int currentX = findSet(subsets, currentEdge.x);
		int currentY = findSet(subsets, currentEdge.y);

		if (currentX != currentY){
			spanningTree[countSpanning] = currentEdge;
			Merge(subsets, currentX, currentY);
			countSpanning++;
		}
		i++;
	}

	if (countSpanning != numberOfVerticies - 1){
		free(subsets);
		return NO_SPANNING_TREE;
	}

	free(subsets);

	return SUCCESS;
}

void printSpanningTree(FILE* output, TEdge *spanningTree, int numberOfVerticies){
	for (int i = 0; i < numberOfVerticies - 1; i++){
		fprintf(output, "%d ", spanningTree[i].x);
		fprintf(output, "%d ", spanningTree[i].y);
		fprintf(output, "\n");
	}
}
