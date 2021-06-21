#ifndef CALCULATOR_H
#define CALCULATOR_H
#include"stack.h"

int get_priority(char operater);
bool is_priority_higher(char first, char second);
int make_operation(int right, int left, char operator, state *state);
Stack infix_to_postfix(Stack* input_stack, state *state);
int calculate_postfix(Stack* postfix_expr, state *state);

#endif // CALCULATOR_H
