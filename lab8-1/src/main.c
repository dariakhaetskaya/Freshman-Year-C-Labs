#include "prim.h"

void ErrorHandler(TState state, FILE* output){
	switch(state){
	case BAD_LENGTH: fprintf(output, "bad length\n");
					 break;

	case BAD_VERTEX: fprintf(output, "bad vertex\n");
					 break;

	case BAD_NUM_OF_LINES:
					 fprintf(output, "bad number of lines\n");
					 break;

	case BAD_NUM_OF_EDGES:
					 fprintf(output, "bad number of edges\n");
					 break;

	case BAD_NUM_OF_VERT:
					 fprintf(output, "bad number of vertices\n");
					 break;

	case READ_FALURE:
					 fprintf(output, "failed to read\n");
					 break;

	case NO_SPANNING_TREE:
					 fprintf(output, "no spanning tree\n");
					 break;
	case SUCCESS:	 break;
	}
}

int main(){
	FILE *input = fopen("in.txt", "r");
	FILE *output = fopen("out.txt", "w");

	TState state = SUCCESS;
	int numberOfVertices = 0;

	if (fscanf(input, "%d ", &numberOfVertices) != 1){
		state = READ_FALURE;
	}

	if (numberOfVertices < 0 || numberOfVertices > 5000){
		state = BAD_NUM_OF_VERT;
	}

	int numberOfEdges = 0;

	if (fscanf(input, "%d ", &numberOfEdges) != 1){
		state = READ_FALURE;
	}
	if (numberOfEdges < 0 || numberOfEdges > numberOfVertices*(numberOfVertices + 1)/2){
		state = BAD_NUM_OF_EDGES;
	}
	if(numberOfEdges == 0 && numberOfVertices == 0){
		state = NO_SPANNING_TREE;
	}

	if (state != SUCCESS){
		ErrorHandler(state, output);
		fclose(input);
		fclose(output);
		return 0;
	}

	TGraph *graph = createGraph(numberOfVertices);
	state = initializeGraph(graph, input, numberOfEdges);

	if (state != SUCCESS){
		ErrorHandler(state, output);
		destroyGraph(graph);
		fclose(input);
		fclose(output);
		return 0;
	}

	TVertex* vertices = (TVertex* )calloc(graph->numberOfVertices, sizeof(TVertex));
	initializeVertices(vertices, graph->numberOfVertices);

	if (PrimSpanningTree(graph, vertices) == NO_SPANNING_TREE){
		fprintf(output, "no spanning tree\n");
		free(vertices);
		destroyGraph(graph);
		fclose(input);
		fclose(output);
		return 0;
	}

	PrintTree(output, vertices, graph->numberOfVertices);
	destroyGraph(graph);
	free(vertices);
	fclose(input);
	fclose(output);
	return 0;
}

