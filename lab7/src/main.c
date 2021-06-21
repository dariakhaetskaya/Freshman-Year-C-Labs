#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define black 2
#define gray 1
#define white 0
#define ERROR 1

bool state = 0;//error tracker
int count_used = 0;//count color blocks ia allocator

typedef struct node {
    struct node* next;
    unsigned int id; //id of "y", destination node
} node;

node* allocate (node* memory_block){
    count_used++;
    return memory_block + (count_used - 1);
}

void add_edge (FILE* fout, node** head, unsigned int id, node* memory_block) {
    node* new_node = allocate(memory_block);

    if (new_node == NULL) {
        fprintf(fout, "memory error");
        return;
    }

    new_node->id = id;
    new_node->next = *head;
    *head = new_node;
}

void deep_first_search(short* color, node** graph, unsigned int current, unsigned int* output, int* current_output) {
    if (*(color + current) == black) {
        return;
    }

    if (*(color + current) == gray) {
        state = ERROR;
        return;
    }

    *(color + current) = gray;
    node* head = *(graph + current);

    while (head != NULL) {
        deep_first_search( color, graph, head->id, output, current_output);
        head = head->next;
    }

    *(color + current) = black;
    *(output + *current_output) = current;
    (*current_output)++;
}

int main() {

   FILE* fin = stdin;
   FILE* fout = stdout;

    int nvertices, nedges;

    //validity tests
    if (fscanf (fin, "%d", &nvertices) == EOF) {
        fprintf(fout, "bad number of lines");
        return 0;
    }

    if (fscanf (fin, "%d", &nedges) == EOF) {
        fprintf(fout, "bad number of lines");
        return 0;
    }

    if (nvertices < 0 || nvertices > 1000) {
        fprintf (fout, "bad number of vertices");
        return 0;
    }

    if (nedges < 0 || nedges > nvertices * (nvertices + 1) / 2) {
        fprintf (fout, "bad number of edges");
        return 0;
    }

    node** graph = malloc (sizeof(node*) * nvertices);
    node* memory_block = malloc (sizeof(node) * nedges);//memory block to implement manual allocation

    if (graph == NULL || memory_block == NULL) {
        fprintf (fin, "mem error");
        free(memory_block);
        free(graph);
        return 0;
    }

    for (int i = 0; i < nvertices; ++i) { //initialization
        *(graph + i) = NULL;
    }

    int from;
    int to;

    for (int i = 0; i < nedges; ++i) {
        if (fscanf (fin, "%d%d", &from, &to) == EOF) {
            fprintf (fout, "bad number of lines");
            state = ERROR;
            break;
        }

        if (from < 1 || from > nvertices || to < 1 || to > nvertices) {
            fprintf (fout, "bad vertex");
            state = ERROR;
            break;
        }

        add_edge (fout, &graph[from - 1], to - 1, memory_block);
    }

    short* color = malloc (sizeof(short) * nvertices);//array for painting the graph in 3 colors

    for (int i = 0; i < nvertices; ++i) {
        color[i] = white;
    }

    unsigned int* output = malloc (sizeof(unsigned int) * nvertices); //output array
    int current_output = 0;//temporary output var

    for (int i = 0; i < nvertices; ++i) {
         if (graph[i] != NULL) {
            deep_first_search(color, graph, i, output, &current_output);
        }
    }

    if (state != ERROR){

        for (int i = current_output - 1; i >= 0; --i) {
            fprintf(fout, "%u ", output[i] + 1);
        }

        for (int i = 0; i < nvertices; ++i) {
            if (color[i] == 0) {
                fprintf(fout, "%d ", i + 1);
             }
        }

    } else {
        fprintf(fout, "impossible to sort\n");
    }

    free(output);
    free(color);
    free(memory_block);
    free(graph);

    fclose(fin);
    fclose(fout);
    return 0;
}
