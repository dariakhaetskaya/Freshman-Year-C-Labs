#include<string.h>
#include<stdlib.h>
#include"parse.h"

int char_to_int(char ch) {
	if (ch >= '0' && ch <= '9') return ch - '0';
	return -1;
}

token_type define_type(char c) {
	token_type type;
	if (c >= '0' && c <= '9') {
		type = number;
		return type;
	}

	if (c == '(') {
		type = open_bracket;
		return type;
	}

	if (c == ')') {
		type = close_bracket;
		return type;
	}

	if (c == '*' || c == '/' || c == '-' || c == '+') {
		type = operater;
		return type;
	}

	if (c >= 'a' && c <= 'z') {
		return -1;
	}

	if (c == ' ') {
		type = neutral;
		return type;
	}
	return -1;
}

Stack* parse(FILE* input, Stack* stack, state *state) {

	token_type previous_token_type = neutral;
	token_type current_token_type = neutral;

	int buffer_for_nums = 0, unmatched_brackets = 0;

	for (unsigned int i = 1; !feof(input); ++i) {
		char current_char;
		int fgetc_result = fgetc(input);
		if (fgetc_result == EOF || fgetc_result == '\n' || fgetc_result == '\r' || *state == error) {
			break;
		}

		current_char = (char)fgetc_result;

		if ((int)define_type(current_char) != -1 && *state == success) {
			current_token_type = define_type(current_char);
		}
		else {
			*state = error;
		}

		if (current_token_type == number && *state == success) {

			if (previous_token_type == number) {
				buffer_for_nums *= 10;
				buffer_for_nums += char_to_int(current_char);
			}
			else {
				buffer_for_nums += char_to_int(current_char);
			}
			
		}

		if (current_token_type != number && previous_token_type == number && *state == success) {
			token* saved_token = (token*)malloc(sizeof(token));
			if (saved_token == NULL) {
				return NULL;
			}
			saved_token->type = number;
			saved_token->value.number = buffer_for_nums;
			push(stack, saved_token);
			buffer_for_nums = 0;
		}

		if (current_token_type == operater && *state == success) {
			if (previous_token_type == operater) {
				*state = error;
			}

			token* current_token = (token*)malloc(sizeof(token));
			if (current_token == NULL) {
				return NULL;
			}
			current_token->value.operater = current_char;
			current_token->type = current_token_type;
			push(stack, current_token);
			
		}

		if (current_token_type == open_bracket && *state == success) {
			if (previous_token_type == close_bracket || previous_token_type == number) {
				*state = error;
			}
			token* current_token = (token*)malloc(sizeof(token));
			if (current_token == NULL) {
				return NULL;
			}
			current_token->type = current_token_type;
			current_token->value.operater = current_char;
			push(stack, current_token);
			unmatched_brackets++;
		}

		if (current_token_type == close_bracket && *state == success) {
			if (previous_token_type == open_bracket || previous_token_type == operater || previous_token_type == neutral) {
				*state = error;
			}
			token* current_token = (token*)malloc(sizeof(token));
			if (current_token == NULL) {
				return NULL;
			}
			current_token->value.operater = current_char;
			current_token->type = current_token_type;
			push(stack, current_token);
			unmatched_brackets--;
		}

		if (*state == success){
			if (previous_token_type == number && current_token_type == neutral) {
				*state = error;
			}

			previous_token_type = current_token_type;
		}
	}

	if (unmatched_brackets != 0 && *state == success) {
		*state = error;
	}

	if (previous_token_type == number && *state == success) {
		token* saved_token = (token*)malloc(sizeof(token));
		if (saved_token == NULL) {
			return NULL;
		}
		saved_token->type = number;
		saved_token->value.number = buffer_for_nums;
		push(stack, saved_token);
	}

	if (stack->head == NULL && *state == success) {
		*state = error;
	}

	if( *state == success){
	reverse(stack);
	return stack;
	} else {
		destroy_stack(stack);
		return NULL;
	}
}
