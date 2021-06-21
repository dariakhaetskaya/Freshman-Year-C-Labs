// Created by daria on 13.11.2019.

#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 17
#define MAX_CHAR_SIZE 256
#include"boyer_moore.h"
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

void create_shifting_table(unsigned char* pattern, int* table, int length) {
	for (int i = 0; i < MAX_CHAR_SIZE; table[i++] = length){
		for (int i = 0; i < length - 1; ++i){
		table[(int)pattern[i]] = length - i - 1;
		}
	}
}

unsigned char* copy_string(unsigned char *dest, const unsigned char *src)
{
	return memcpy (dest, src, strlen ((const char *)src) + 1);
}

void boyer_moore_search(FILE* input, FILE* output) {
	unsigned char template[MAX_SIZE] = { 0 };
	int shifting_table[MAX_CHAR_SIZE];

	if ((int)fscanf(input, "%16[^\n]", template) == EOF) {
		return;
	}

	if ((int)fgetc(input) == EOF) {
		return;
	}

	unsigned int template_len = strlen((const char*)template);
	if (template_len == 0) {
		exit(0);
	}

	char* signed_buffer = (char*)malloc(template_len + 1);
	unsigned char* buffer = (unsigned char*)malloc(template_len + 1);
	create_shifting_table(template,shifting_table,template_len);

	if (buffer == NULL){
		free(buffer);
		free(signed_buffer);
		return;
	}

	if (signed_buffer == NULL){
		free(signed_buffer);
		free(buffer);

		return;
	}

	unsigned int number_of_matched = 0, position = 1, shift = 0;

	while (fgets(signed_buffer + shift, template_len - shift + 1, input) != NULL) {

		unsigned int shifting = 0;
		buffer = (unsigned char *)signed_buffer;

		if (buffer[template_len - 1 ] == '\0') {
				free(buffer);
				return;
		}

		for (int i = template_len - 1; i >= 0; --i) {
			

			fprintf(output, "%u ", i + position);
			if (buffer[i] == template[i]) {
				number_of_matched++;
			}
			else {
				break;
			}
		}

		shifting = shifting_table[buffer[template_len - 1]];
		shift = template_len - shifting;

		if (number_of_matched == template_len) {
			shifting = template_len;
			shift = 0;
		}

		if (shifting != template_len) {
			unsigned char tmp_buffer[MAX_SIZE];
			copy_string(tmp_buffer, buffer);

			for (unsigned int i = 0, j = shifting; j < template_len; i++, j++) {
				buffer[i] = tmp_buffer[j];
			}
		}

		position += shifting;
		number_of_matched = 0;
	}
	free(buffer);
	return;
}
