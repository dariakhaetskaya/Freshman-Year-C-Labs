#include"avltree.h"

int main(){
	FILE* input = fopen("in.txt", "r");
	FILE* output = fopen("out.txt", "w");

	Tree tree = {.root = NULL};

	int size = 0;

	if (fscanf(input, "%d", &size) != 1){
		fclose(input);
		fclose(output);
		return 0;
	}

	int value;

	for (int i = 0; i < size; ++i){
		if (fscanf(input, "%d", &value) == 1){
			if(!insert(&tree, value)){
				fprintf(output, "failed to insert new node\n");
			}
		}
	}

	fprintf(output, "%d\n", tree_height(tree.root));
	destroy_tree(tree.root);
	fclose(input);
	fclose(output);

	return 0;
}
