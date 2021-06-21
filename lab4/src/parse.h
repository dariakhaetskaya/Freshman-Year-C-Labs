#ifndef PARSE_H
#define PARSE_H

#include"stack.h"

int char_to_int(char ch);
token_type define_type(char c);
void exit_and_clear_mem(Stack* stack, state *state);
Stack* parse(FILE* input, Stack* stack, state *state);

#endif // PARSE_H
