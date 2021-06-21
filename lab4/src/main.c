#include"calculator.h"
#include"parse.h"

int main() {
	//FILE* input = fopen("in.txt", "r");
	//FILE* output = fopen("out.txt", "w");
	FILE* input = stdin;
	FILE* output = stdout;

	Stack stack = { .head = NULL };
	state state = success;

	parse(input, &stack,&state);
	if (state == error){
		fprintf(stdout, "syntax error\n");
		return 0;
	}

	Stack postfix_expr = infix_to_postfix(&stack, &state);
	if (state == error){
		fprintf(stdout, "syntax error\n");
		return 0;
	}

	int result = calculate_postfix(&postfix_expr, &state);

	if(state == division_by_zero) {

		fprintf(stdout, "division by zero\n");

	} else if (state == error){

		fprintf(stdout, "syntax error\n");
		return 0;

	} else {

	fprintf(output, "%d\n", result);
	destroy_stack(&stack);
	destroy_stack(&postfix_expr);
	fclose(input);
	fclose(output);

}
	return 0;
}
