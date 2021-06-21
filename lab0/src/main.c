#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include <stdbool.h>
#define SIZE 15
#define FRAC_SIZE 13

int char_to_int(char ch) {
	if (ch >= '0' && ch <= '9') return ch - '0';
	if (ch >= 'a' && ch <= 'z') return ch - 'a' + 10;
	return -1;
}

char int_to_char(int a) {
	return (a < 10) ? '0' + a : 'a' + (a - 10);
}

bool is_in_range(const char input_num[SIZE], int b1) {
	for (int i = 0; i < (int)strlen(input_num); i++) {
		if (input_num[i] != '.') {
			if (char_to_int(input_num[i]) >= b1) return false;
		}
	}
	return true;
}

void swap(char* a, char* b) {
	char temp = *b;
	*b = *a;
	*a = temp;
}

void reverse_string(char* str) {
	int str_len = strlen(str);

	for (int i = 0; i < str_len / 2; ++i) {
		swap(&str[i], &str[str_len - i - 1]);
	}
}

void print_string(char* str){
	int str_len = strlen(str);

	for (int i = 0; i < str_len; ++i) {
		printf("%c", str[i]);
	}
}

long double convert_to_10(const char* input_num, int b1) {
	const char* point_ptr = strchr(input_num, '.');
	int integer_part_SIZE = point_ptr == NULL ? (int)strlen(input_num) : point_ptr - input_num;
	long double num_in_10 = 0;

	for (int i = 0; input_num[i] != '\0'; ++i) {
		if (input_num[i] != '.') {
			num_in_10 += char_to_int(tolower(input_num[i])) * pow(b1, integer_part_SIZE - 1);
			--integer_part_SIZE;
		}
	}

	return num_in_10;
}
void convert_int_and_print(long long int n_part, int b2) {
	char converted_num[52] = { 0 };
	short next_digit_idx = 0;

	while (n_part != 0) {
		converted_num[next_digit_idx] = int_to_char(n_part % b2);
		n_part /= b2;
		next_digit_idx++;
	}
	reverse_string(converted_num);
	print_string(converted_num);
}

void convert_frac_and_print(long double frac_part_in_10, int base2) {
	int arr[FRAC_SIZE] = { 0 }, count = 0;

	for (int i = 0; i < FRAC_SIZE && frac_part_in_10 * base2 - arr[i] != 0; i++) {
		arr[i] = (int)(frac_part_in_10 * base2);
		frac_part_in_10 = frac_part_in_10 * base2 - arr[i];
		count++;
	}
	printf(".");

	for (int i = 0; i < count; i++) {
		printf("%c", int_to_char(arr[i]));
	}

	printf("\n");
}

void data_check(int b1, int b2, char input_num[SIZE]) {
	int length = strlen(input_num);
	const char digits[] = "1234567890abdcef.";
	char double_dot_flag = 0;

	if (input_num[0] == '0' && input_num[1] == '\0') {
		printf("0");
		return;
	}

	for (int i = 0; i < length; ++i) {
		if (input_num[i] == '.') double_dot_flag++;
		if (!strchr(digits, tolower(input_num[i]))){
			printf("bad input");
			return;
		}
	}

	if (input_num[0] == '.' || input_num[length - 1] == '.'){
		printf("bad input");
		return;
	}
	
	if (!is_in_range(input_num, b1)){
		printf("bad input");
		return;
	}
	
	if (b1 < 2 || b2 > 16 || double_dot_flag > 1){
		printf("bad input");
		return;
	}
}

void convert(int b1, int b2, char input_num[SIZE]) {
	char flag = 0;

	for (int i = 0; i < (int)strlen(input_num); ++i) {

		if (input_num[i] == '.') {
			flag = 1;
			char int_part[SIZE], frac_part[SIZE];
			strncpy(int_part, input_num, i);
			int_part[i] = '\0';
			strcpy(frac_part, input_num + i + 1);

			if (int_part[0] == '0' && int_part[1] == '\0' && frac_part[0] == '0' && frac_part[1] == '\0') {
				printf("bad input");
				return;
			}

			convert_int_and_print((convert_to_10(int_part, b1)), b2);

			if (frac_part[0] != '\0') {
				if (int_part[0] == '0' && int_part[1] == '\0') printf("0");
				convert_frac_and_print((convert_to_10(input_num, b1) - convert_to_10(int_part, b1)), b2);
			}
		}
	}
	if (b2 == 10) convert_to_10(input_num, b1);

	if (flag == 0) {
		convert_int_and_print((convert_to_10(input_num, b1)), b2);
	}

	printf("\n");
}

int main(void) {
	int b1, b2;
	char input_num[SIZE];

	if (scanf("%d %d %14s", &b1, &b2, input_num) != 3) {
		printf("Failed to read.\n");
	}
	else {
		data_check(b1, b2, input_num);
		convert(b1, b2, input_num);
	}

	getchar();
	return 0;
}
