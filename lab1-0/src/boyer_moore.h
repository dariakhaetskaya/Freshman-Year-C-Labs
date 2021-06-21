//
// Created by daria on 13.11.2019.
//
#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H
#include <stdio.h>
#include <stdlib.h>
int shifting_table(unsigned char* template, unsigned char sample);
void boyer_moore_search(FILE* input, FILE* output);
#endif 
