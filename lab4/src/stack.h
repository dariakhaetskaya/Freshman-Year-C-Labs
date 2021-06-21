#ifndef STACK_H
#define STACK_H

#include<stdbool.h>
#include<stdio.h>
#include"token.h"

typedef struct Node Node;
struct Node {
	token* token;
	Node* prev;

};

typedef struct {
	Node* head;
} Stack;

void push(Stack* stack, token* new_token);
token* pop(Stack* stack);
void reverse(Stack* stack);
//void destroy();
void destroy_stack(Stack* stack);

#endif // STACK_H
