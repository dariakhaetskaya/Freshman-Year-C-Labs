#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void swap(int* a, int* b) {
	if (*a != *b) {

		*a ^= *b;
		*b ^= *a;
		*a ^= *b;

	}
}

void quick_sort(int *array, int left, int right) {

	int center = 0, i = 0, j = 0;
	if (left >= right) return;
	i = left;
	j = right;
	center = array[(left + right) / 2];

	while (i <= j) {
		while (array[i] < center) i++;
		while (array[j] > center) j--; 
		if (i <= j) {
			swap(&array[i], &array[j]);
			i++; 
			j--;
		}
	}

	quick_sort(array, left, j);
	quick_sort(array, i, right);
}

int main() {
	int size = 0;
	if (scanf("%d", &size) != 1) {
		printf("failed to read size");
		return 0;
	}

	if (size < 0){
		printf("bad input");
		return 0;
	}

	int* array = malloc(size * sizeof(int));

	for (int i = 0; i < size; ++i) {
		if (scanf("%d", &array[i]) != 1) {
			printf("failed to read array element");
			free(array);
			return 0;
		}
	}

	quick_sort(array, 0, size - 1);

	for (int i = 0; i < size; ++i) {
		printf("%d ", array[i]);
	}

	free(array);
	return 0;
}
