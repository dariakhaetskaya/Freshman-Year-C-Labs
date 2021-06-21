#include"avltree.h"
#include<stdlib.h>

int tree_height(Node* node){

	if(node != NULL){
		int lh = 0;
		int rh = 0;

		if (node->left_child != NULL){
			lh = node->left_child->height;
		}
		if (node->right_child != NULL){
			rh = node->right_child->height;
		}
		return max(lh, rh) + 1;
	} else {
		return 0;
	}
}

int balance_factor(Node* node){
	if (node == NULL){
		return 0;
	}

	int left_subtree_h = 0, right_subtree_h = 0;

	if (node->left_child != NULL){
		left_subtree_h = tree_height(node->left_child);
	}

	if (node->right_child != NULL){
		right_subtree_h = tree_height(node->right_child);
	}

	return right_subtree_h - left_subtree_h;
}

int max (int a, int b){

	return (a < b) ? b : a;
}

void swap(int *a, int *b){
	if(a == b){
		return;
	}

	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void update(Node* node){

	node->height = tree_height(node);
}

void left_rotation(Node* node_a){
	Node* node_b = node_a->right_child;

	Node* q = node_b->right_child;
	Node* r = node_b->left_child;
	Node* p = node_a->left_child;

	node_b->left_child = p;
	node_b->right_child = r;

	swap (&node_a->value, &node_b->value);
	swap (&node_a->height, &node_b->height);

	node_a->left_child = node_b;
	node_a->right_child = q;

	update(node_a);
	update(node_b);
}

void right_rotation(Node* node_a){

	Node* node_b = node_a->left_child;

	Node* q = node_b->left_child;
	Node* r = node_b->right_child;
	Node* p = node_a->right_child;

	node_b->right_child = p;
	node_b->left_child = r;

	swap (&node_a->value, &node_b->value);
	swap (&node_a->height, &node_b->height);

	node_a->right_child = node_b;
	node_a->left_child = q;

	update(node_a);
	update(node_b);

}

void left_left_case(Node* node){

	right_rotation(node);
}

void left_right_case(Node* node){
	left_rotation(node->left_child);
	left_left_case(node);
}

void right_right_case(Node* node){

	left_rotation(node);
}

void right_left_case(Node* node){
	right_rotation(node->right_child);
	right_right_case(node);
}

void balance(Node* node){

	char bf =  balance_factor(node);

	if(bf == -2){
		if(balance_factor(node->left_child) <= 0){
			left_left_case(node);
		} else {
			left_right_case(node);
		}

	} else if (bf == 2){
		if (balance_factor(node->right_child) >= 0){
			right_right_case(node);
		} else {
			right_left_case(node);
		}
	}
	node -> height = tree_height(node);

}

Node* recursive_insert(Node* node, int new_value){
	if (node == NULL){
		Node* new_node = (Node*)calloc(1,sizeof(Node));
		new_node->value = new_value;
		new_node->height = 1;
		return new_node;
	}
	node->height = tree_height(node);

	if (node->value > new_value){
		node->left_child = recursive_insert(node->left_child, new_value);
	} else {
		node->right_child = recursive_insert(node->right_child, new_value);
	}
	update(node); 
	balance(node);

	return node;
}

bool insert(Tree* tree, int new_value) {
	if (tree == NULL) {
		return false;
	}
	if ((tree->root = recursive_insert(tree->root, new_value))){
		tree->height = tree_height(tree->root);
		return true;
	}

	return false; 
}

void destroy_tree(Node* node){
	if (node != NULL){
		if (node->left_child != NULL){
			Node* lc = node->left_child;
			destroy_tree(lc);

		}

	if (node->right_child != NULL){
			Node* rc = node->right_child;
			destroy_tree(rc);
		}

	free(node);
	}

}
