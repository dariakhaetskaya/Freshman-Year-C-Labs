//
// Created by daria on 09.11.2019.
//

#ifndef UNTITLED6_RABIN_KARP_H
#define UNTITLED6_RABIN_KARP_H
#define max_size 17
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calculate_hash(unsigned const char* str, unsigned int size);
int recalc_hash(int* hash, unsigned char first, unsigned char last, unsigned int size);
void rabin_karp_search(FILE* input, FILE* output);
#endif //UNTITLED6_RABIN_KARP_H
