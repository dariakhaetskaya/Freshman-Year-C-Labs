#include"stack.h"
#include<stdlib.h>


void push(Stack* stack, token* new_token) {
	if (stack == NULL) {
		exit(0);
	}
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		exit(0);
	}
	new_node->prev = stack->head;
	new_node->token = new_token;
	stack->head = new_node;
	return;
}

token* pop(Stack* stack) {
	if (stack == NULL || stack->head == NULL) {
		return NULL;
	}
	Node* node_to_pop = stack->head;
	token* value = node_to_pop->token;
	stack->head = stack->head->prev;
	free(node_to_pop);
	return value;
}

void reverse(Stack* stack) {
	if (stack->head == NULL) {
		exit(0);
	}

	Node* prev_node, * cur_node;

	prev_node = stack->head;
	cur_node = stack->head->prev;
	stack->head = stack->head->prev;

	prev_node->prev = NULL;

	while (stack->head != NULL)
	{
		stack->head = stack->head->prev;
		cur_node->prev = prev_node;
		prev_node = cur_node;
		cur_node = stack->head;
	}

	stack->head = prev_node;
	return ;
}

void destroy_stack(Stack* stack)
{
	Node* current = stack->head;
	Node* prev;
	while (current != NULL) {
		prev = current->prev;
		free(current->token);
		free(current);
		current = prev;
	}
	stack->head = NULL;
}
