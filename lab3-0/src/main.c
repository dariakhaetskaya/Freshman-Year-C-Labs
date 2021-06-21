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

void shift_down(int* array, int N, int i) {
    int largest_child = 0;
    while (i * 2 + 1 < N) {
        if (i * 2 + 2 == N) {
            largest_child = i * 2 + 1;
        }
        else if (array[i * 2 + 1] > array[i * 2 + 2]) {
            largest_child = i * 2 + 1;
        }
        else {
            largest_child = i * 2 + 2;
        }
        if (array[i] < array[largest_child]) {
            swap(&array[i], &array[largest_child]);
            i = largest_child;
        }
        else {
            return;
        }
    }
}

void heap_sort(int* array, int N) {
    for (int i = N / 2; i >= 0; i--) {
        shift_down(array, N, i);
    }

    for (int i = N - 1; i >= 0; i--) {
        swap(&array[i], &array[0]);
        shift_down(array, i, 0);
    }
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

    int* array = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            printf("failed to read array element");
            free(array);
            return 0;
        }
    }

    heap_sort(array, size);

    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }

    free(array);
    return 0;
}
