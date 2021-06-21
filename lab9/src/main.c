#include "dijkstra.h"

int main(){
	FILE *input = fopen("in.txt", "r");
	FILE *output = fopen("out.txt", "w");

	int numberOfVertices = 0;

	if (fscanf(input, "%d ", &numberOfVertices) != 1){
		fprintf(output, "failed to read\n");
		fclose(input);
		fclose(output);
		return 0;
	}

	if (numberOfVertices < 0 || numberOfVertices > 5000){
		fprintf(output, "bad number of vertices\n");
		fclose(input);
		fclose(output);
		return 0;
	}

	unsigned int src, dest;

	if (fscanf(input, "%u %u", &src, &dest) != 2){
		fprintf(output, "failed to read\n");
		fclose(input);
		fclose(output);
		return 0;
	}

	if (src > (unsigned int)numberOfVertices || dest > (unsigned int)numberOfVertices){
		fprintf(output, "bad path\n");
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

	if (numberOfEdges < 0 || numberOfEdges > numberOfVertices*(numberOfVertices + 1)/2){
		fprintf(output, "bad number of edges\n");
		fclose(input);
		fclose(output);
		return 0;
	}

	TGraph *graph = createGraph(numberOfVertices);
	TState state = InitializeGraph(graph, input, numberOfEdges);

	if (numberOfVertices == 0){
		state = BAD_VERTEX;
	}

	if (state != SUCCESS){
		fprintf(stderr, "%d\n", state);
		switch(state){
		case BAD_LENGTH: fprintf(output, "bad length\n");
						 break;

		case BAD_VERTEX: fprintf(stderr, "%d\n", state);
						fprintf(output, "bad vertex\n");
						 break;

		case BAD_NUM_OF_LINES:
						 fprintf(output, "bad number of lines\n");
						 break;
		default: break;
		}
		destroyGraph(graph);
		fclose(input);
		fclose(output);
		return 0;
	}

	TVertex* vertices = (TVertex* )calloc(graph->numberOfVertices, sizeof(TVertex));
	InitializeVertices(vertices, graph->numberOfVertices);;
	state = DijkstraAlgorithm(graph, vertices, src, dest);

	PrintDist(output, vertices, numberOfVertices);

	if (state == NO_PATH || state == LARGER_INT_MAX){
		if (state == LARGER_INT_MAX){
			fprintf(output, "overflow\n");
		} else {
			fprintf(output, "no path\n");
		}
		free(vertices);
		destroyGraph(graph);
		fclose(input);
		fclose(output);
		return 0;
	}

	PrintPath(output, vertices, dest);
	destroyGraph(graph);
	free(vertices);

	fclose(input);
	fclose(output);
	return 0;
}
