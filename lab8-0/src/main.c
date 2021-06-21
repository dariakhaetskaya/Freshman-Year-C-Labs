#include <stdio.h>
#include "kruskal.h"

int main(){
	FILE *input = fopen("in.txt", "r");
	FILE *output = fopen("out.txt", "w");

	int numberOfVerticies = 0;
	if (fscanf(input, "%d ", &numberOfVerticies) != 1){
		fprintf(output, "failed to read\n");
		fclose(input);
		fclose(output);
		return 0;
	}
	if (numberOfVerticies < 0 || numberOfVerticies > 5000){
		fprintf(output, "bad number of vertices\n");
		fclose(input);
		fclose(output);
		return 0;
	}
	int numberOfEdges = 0;
	if (fscanf(input, "%d ", &numberOfEdges) != 1){
		fprintf(output, "failed to read\n");
		fclose(input);
		fclose(output);
		return 0;
	}
	if (numberOfEdges < 0 || numberOfEdges > numberOfVerticies*(numberOfVerticies + 1)/2){
		fprintf(output, "bad number of edges\n");
		fclose(input);
		fclose(output);
		return 0;
	}

	TGraph *graph = createGraph(numberOfEdges, numberOfVerticies);
	TState state = initializeGraph(&graph, input);

	if (state != SUCCESS){
		switch(state){
		case BAD_LENGTH: fprintf(output, "bad length\n");
						 break;

		case BAD_VERTEX: fprintf(output, "bad vertex\n");
						 break;

		case BAD_NUM_OF_LINES:
						 fprintf(output, "bad number of lines\n");
						 break;
		default: break;
		}
		fclose(input);
		fclose(output);
		destroyGraph(&graph);
		return 0;
	}

	TEdge *spanningTree = (TEdge* )calloc(numberOfVerticies, sizeof(TEdge));
	if (spanningTree == NULL){
		fprintf(output, "failed to allocate memory\n");
	}

	if (KruskalSpanningTree(&graph, spanningTree) == NO_SPANNING_TREE){
		fprintf(output, "no spanning tree\n");
		fclose(input);
		fclose(output);
		free(spanningTree);
		destroyGraph(&graph);
		return 0;
	}

	printSpanningTree(output, spanningTree, graph->numberOfVerticies);
	free(spanningTree);
	destroyGraph(&graph);
	fclose(input);
	fclose(output);
	return 0;
}
