#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "boyer_moore.h"

int main() {
	
	FILE* input = fopen("in.txt", "r");
	FILE* output = fopen("out.txt", "w");

	boyer_moore_search(input, output);
	
	fclose(input);
	fclose(output);

	return 0;
} 
