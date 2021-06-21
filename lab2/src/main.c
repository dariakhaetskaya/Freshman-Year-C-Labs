#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define max_size 11

void swap(char* a, char* b) {
    char saved_value = *a;
    *a = *b;
    *b = saved_value;
}

unsigned int find_index_min_element(const char* number, char min_larger_than_number) {
    int number_length = (int)strlen(number);
    char min = '9';
    int min_index = -1;

    for (int i = 0; i < number_length; ++i) {
        if (number[i] <= min && number[i] > min_larger_than_number) {
            min = number[i];
            min_index = i;
        }
    }

    return min_index + 1;
}

void reverse_string(char* str) {
    unsigned int length = strlen(str);

    for (unsigned int i = 0; i < length / 2; ++i) {
        swap(&str[i], &str[length - i - 1]);
    }
}

void permutation(char* input_number, unsigned int p_count) {
    unsigned int number_length = strlen(input_number);

    for (int idx = number_length - 2; idx >= 0 && p_count != 0; --idx) {

        if (input_number[idx] < input_number[idx + 1]) { //if we found an element that breaks the order
            swap(&input_number[idx],				 //we swap it with the min element with lagrer index
                 &input_number[find_index_min_element(input_number + idx + 1, input_number[idx]) + idx]); //which is larger than the "breaker"
            reverse_string(input_number + idx + 1); //and then we just revers the order of the elements in the string
            printf("%s\n", input_number);
            idx = number_length - 1;
            --p_count;
        }
    }
}

unsigned int char_count_in_string(char* input_number, char character) {
    unsigned int count = 0, number_length = strlen(input_number);

    for (unsigned int i = 0; i < number_length; ++i) {
        if (input_number[i] == character) {
            count++;
        }
    }
    return count;
}

bool is_valid(char* input_number) {
    int number_length = (int)strlen(input_number);

    for (int i = 0; i < max_size - 1; ++i) {
        if (char_count_in_string(input_number, i + '0') > 1) {
            return false;
        }
    }

    for (int i = 0; i < number_length; ++i) {
        if (input_number[i] < '0' || input_number[i] > '9') {
            return false;
        }
    }

    return true;
}

int main() {
    unsigned int number_of_permutations = 0;
    char input_number[max_size] = { 0 };

    if (scanf("%10s %u", input_number, &number_of_permutations) != 2) {
        return -1;
    }

    if (is_valid(input_number)) {
        permutation(input_number, number_of_permutations);
    }
    else {
        printf("bad input");
    }

    return 0;
}
