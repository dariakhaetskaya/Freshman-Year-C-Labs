#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "rabin_karp.h"

int main() {
	FILE* input = fopen("in.txt", "r");
	FILE* output = fopen("out.txt", "w");

	rabin_karp_search(input, output);

	fclose(input);
	fclose(output);

	return 0;
}
