//
// Created by daria on 09.11.2019.
//
#define _CRT_SECURE_NO_WARNINGS
#include "rabin_karp.h"
#include<stdbool.h>

const int powers_of_3[max_size] = { 1, 3, 9, 27, 81, 243, 729, 2187,6561, 19683,
									 59049, 177147, 531441, 1594323, 4782969, 14348907 };


int calculate_hash(unsigned const char* str, unsigned int size) {
	int hash_value = 0;

	for (unsigned int i = 0; i < size; ++i) {
		hash_value += (str[i] % 3) * powers_of_3[i];
	}

	return hash_value;
}

int recalc_hash(int* hash, unsigned char first, unsigned char last, unsigned int size) {
	*hash -= first % 3;
	*hash /= 3;
	*hash += (last % 3) * powers_of_3[size - 1];

	return *hash;
}

void rabin_karp_search(FILE* input, FILE* output) {
	unsigned char template[max_size] = { 0 };
	
	if ((int)fscanf(input, "%16[^\n]", template) == EOF) {
		return;
	}

	if ((int)fgetc(input) == EOF) {
		return;
	}

	unsigned int template_len = strlen((const char *)template);
	if (template_len == 0) {
		exit(0);
	}

	int template_hash_value = calculate_hash(template, template_len);
	fprintf(output, "%d ", template_hash_value);

	unsigned char* buffer = (unsigned char*)malloc(template_len + 1);
	if (buffer == NULL) {
		return;
	}

	if (fread(buffer, sizeof(unsigned char), template_len, input) != template_len) {
		free(buffer);
		return;
	}

	int buffer_hash_value = calculate_hash(buffer, template_len);

	for (unsigned int i = 1; !feof(input); ++i) {
		bool is_equal = 0;

		if (buffer_hash_value == template_hash_value) {
			is_equal = 1;
			for (unsigned int j = 0; j < template_len; ++j) {
				fprintf(output, "%u ", j + i);
				if (buffer[j] != template[j]) break;
			}
		}

		if (is_equal) {
			i += template_len - 1;
			if ((int)fread(buffer, sizeof(unsigned char), template_len, input) == EOF) {
				free(buffer);
				return;
			}
			buffer_hash_value = calculate_hash(buffer, template_len);

		}
		else {
			unsigned char first = buffer[0];
			memmove(buffer, buffer + 1, template_len * sizeof(unsigned char));
			buffer[template_len - 1] = fgetc(input);
			recalc_hash(&buffer_hash_value, first, buffer[template_len - 1], template_len);
		}
		is_equal = 0;
	}
	free(buffer);
}
