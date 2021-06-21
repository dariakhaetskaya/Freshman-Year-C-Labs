#include "calculator.h"
#include<stdlib.h>

int get_priority(char operater) {
	switch (operater) {
	case '(':
	case ')':
		return 1;
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	case '^':
		return 4;
	default:
		return 0;
	}
}

int make_operation(int right, int left, char operator, state *state) {
	switch (operator)
	{
	case '*':
		return right * left;
	case '/':
		return left / right;
	case '+':
		return right + left;
	case '-':
		return left - right;

	default:
		*state = error;
		return 0;
	}
}

Stack infix_to_postfix(Stack* input_stack, state *state) {

	reverse(input_stack);

	token* closing_bracket = (token*)malloc(sizeof(token)); //and one matching closing brasket to the end of the input
	if (closing_bracket == NULL) {
		*state = error;
		//return NULL
	} else {
		closing_bracket->type = close_bracket;
		closing_bracket->value.operater = ')';
		push(input_stack, closing_bracket);
	}
	
	reverse(input_stack);
	
	Stack stack_for_calculation = { .head = NULL };
	Stack postfix_expr = { .head = NULL };

	token* opening_bracket = (token*)malloc(sizeof(token));//push opening brasket at the tail not to check if we have something in remain in stack or not
	if (opening_bracket == NULL) {
		*state = error;
		//return NULL;
	} else {
		opening_bracket->type = open_bracket;
		opening_bracket->value.operater = '(';
		push(&stack_for_calculation, opening_bracket);
	}

	

	if (stack_for_calculation.head == NULL) {
		*state = error;
		//return NULL;
	}

	bool found_matching_bracket = false;
	while (input_stack->head != NULL && *state == success) {

		token* current_token = pop(input_stack);

		switch (current_token->type) {

		case open_bracket:
			push(&stack_for_calculation, current_token);
			break;

		case number:
			push(&postfix_expr, current_token);
			break;

		case operater:
		{
			
			while (stack_for_calculation.head->token != NULL && (stack_for_calculation.head->token->type != open_bracket) &&
					(get_priority(current_token->value.operater) <= get_priority(stack_for_calculation.head->token->value.operater))) {

				token* tmp_token = pop(&stack_for_calculation);
				push(&postfix_expr, tmp_token);
			}

			push(&stack_for_calculation, current_token);
			break;
			
		}

		case close_bracket:
			found_matching_bracket = true;
			
			if (stack_for_calculation.head == NULL) {
				break;
			}

			while (stack_for_calculation.head->token->type != open_bracket){
				token* tmp_token = pop(&stack_for_calculation);
				push(&postfix_expr, tmp_token);

				if (stack_for_calculation.head == NULL) break;
			}

			if (stack_for_calculation.head->token->type == open_bracket) {
				free(pop(&stack_for_calculation));
			}

			if (stack_for_calculation.head == NULL) {
				free(current_token);
				break;
			}

			if (stack_for_calculation.head->token->value.operater == open_bracket) {
				found_matching_bracket = true;
			}

			if (!found_matching_bracket) {
				destroy_stack(input_stack);
				destroy_stack(&stack_for_calculation);
				*state = error;
			}

			found_matching_bracket = false;
			free(current_token);
			break;

		default: 
			free(current_token);
			break;
		}
	}
	if (*state == success){
		destroy_stack(input_stack);
		destroy_stack(&stack_for_calculation);
	}
	return postfix_expr;

}

int calculate_postfix(Stack* postfix_expr, state *state) {
	int result = 0;
	Stack stack_for_calculation = { .head = NULL };
	
	int left = 0, right = 0;
	reverse(postfix_expr);

	while (postfix_expr->head != NULL && *state == success) {
		token *right_token, *left_token;
		token* current_token = pop(postfix_expr);

		switch (current_token->type)
		{
		case number:
			push(&stack_for_calculation, current_token);
			break;

		case operater:

			right_token = pop(&stack_for_calculation);
			right = right_token->value.number;
			free(right_token);

			if (stack_for_calculation.head == NULL) {
				free(current_token);
				//destroy_stack(&stack_for_calculation);
				//destroy_stack(postfix_expr);
				*state = error;
			}

			if (*state == success){
				left_token = pop(&stack_for_calculation);
				left = left_token->value.number;
				free(left_token);
			}

			if (right == 0 && current_token->value.operater == '/' && *state == success) {
				free(current_token);
				//destroy_stack(&stack_for_calculation);
				//destroy_stack(postfix_expr);
				*state = division_by_zero;
			}
			if (*state == success){
				current_token->type = number;
				//fprintf(stdout, "left %d\n", left);
				//fprintf(stdout, "right %d\n", right);
				current_token->value.number = make_operation(right, left, current_token->value.operater, state);
				//fprintf(stdout, "%d\n", current_token->value.number); //correct
				push(&stack_for_calculation, current_token);
			}
			break;

		default:
			free(current_token);
			break;
		}

	}
	if (*state == success){
	result = pop(&stack_for_calculation)->value.number;
	//fprintf(stdout, "%d\n", result); //correct here as well
	}

	destroy_stack(&stack_for_calculation);
	destroy_stack(postfix_expr);
	return result;
}
