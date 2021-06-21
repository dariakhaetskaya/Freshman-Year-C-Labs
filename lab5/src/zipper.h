#include <stdio.h>
#include <stdlib.h>
#define bufferSize 512
#define bitBufferSize 4096
#define countChars 256
#define estimatedTreeHeight 26

typedef struct HuffmanNode{
    struct HuffmanNode* left;
    struct HuffmanNode* right;
    int frequency;
    unsigned char letter;
}HuffmanNode;

int compare(const void* a, const void* b);

void charToByte(short n, short arr[8]);

short byteToChar(unsigned char arr[8]);

HuffmanNode* buildHuffmanTree(const int symbols[countChars]);

void encode(short sym_code[18],HuffmanNode* Tree, unsigned int height,short** code,HuffmanNode* head);

short codeToBin(short** code,FILE* output,short bits, unsigned char* a);

void writeBit(FILE* output,short* bits,char n, unsigned char* a);

void printTree(HuffmanNode* head,FILE* output,short* bits, unsigned char* a);

void binToCode(unsigned char* buf_bits, unsigned char c,int* g);

int Read(FILE* input, unsigned char* buf, unsigned char* buf_bits);

void recoverTree(unsigned char* bitBuffer, unsigned char* buffer, FILE* input, HuffmanNode**head, int* count, int* processed);

void decode(FILE* output, FILE* input, unsigned char* buffer, unsigned char* bitBuffer, int* count, HuffmanNode* head, char bits, int* processed);

void freeTree(HuffmanNode* tree);

void freeCodes(short* code[countChars]);
