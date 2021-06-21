#ifndef AVLTREE_H
#define AVLTREE_H

#include<stdbool.h>
#include<stdio.h>

typedef struct Node Node;
struct Node {
	Node* left_child;
	Node* right_child;
	int value;
	int height;
};

typedef struct {
	Node* root;
	int height;
} Tree;


int tree_height(Node* root);

int balance_factor(Node* node);

int max (int a, int b);

void swap(int *a, int *b);

void update(Node* node);

void left_rotation(Node* node_a);

void right_rotation(Node* node_a);

void left_left_case(Node* node);

void left_right_case(Node* node);

void right_right_case(Node* node);

void right_left_case(Node* node);

void balance(Node* node);

Node* recursive_insert(Node* node, int new_value);

bool internal_recursive_insert(Node* node, int new_value);

bool insert(Tree* tree, int new_value);

void destroy_tree(Node* node);

#endif // AVLTREE_H
