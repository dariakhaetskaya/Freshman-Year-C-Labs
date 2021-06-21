#ifndef TOKEN_H
#define TOKEN_H

typedef union token_value { int number; char operater; }token_value;

typedef enum token_type { open_bracket, close_bracket, number, operater, neutral } token_type;

typedef struct token { token_type type; token_value value; } token;

typedef enum state { success, error, division_by_zero} state;

#endif // TOKEN_H
