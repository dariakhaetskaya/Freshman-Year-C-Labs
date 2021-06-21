#include "zipper.h"

int compare(const void* a, const void* b){
    return ((*(HuffmanNode **)b)->frequency > (*(HuffmanNode **)a)->frequency);
}

void charToByte(short character, short byte[8]){ // break char into bits
    short count = 7;

    if(character == 0)
        return;

    while(character){
        byte[count] = (short)(character & 1);
        character = character >> 1;
        count--;
    }
}

short byteToChar(unsigned char byte[8]){ // turn byte to char
    short character = 0;
    short h = 1;
    for(int i = 7;i >= 0; --i){
        character += (short)(byte[i] - '0')*(h << (7 - i));
    }
    return character;
}

HuffmanNode* buildHuffmanTree(const int symbols[countChars]){
	int DifSum = 0;
	HuffmanNode *Tree[countChars];
    Tree[0] = NULL;

    for (int i = 0; i < countChars; ++i) {
        if (symbols[i] > 0) {
            HuffmanNode *root = (HuffmanNode *)calloc(1, sizeof(HuffmanNode));
            root->frequency = symbols[i];
            root->letter = i;
            Tree[DifSum] = root;
            DifSum += 1;
        }
    }

    while (DifSum > 1){
        qsort(Tree, DifSum, sizeof(HuffmanNode *), compare);
        HuffmanNode *currentHuffmanNode = (HuffmanNode *)calloc(1, sizeof(HuffmanNode));
        currentHuffmanNode->left = Tree[DifSum - 2];
        currentHuffmanNode->right = Tree[DifSum - 1];
        currentHuffmanNode->frequency = Tree[DifSum - 2]->frequency + Tree[DifSum - 1]->frequency;
        currentHuffmanNode->letter = 0;
        Tree[DifSum - 2] = currentHuffmanNode;
        DifSum--;
    }
    return *Tree;
}

void encode(short charCode[estimatedTreeHeight], HuffmanNode* Tree, unsigned int height, short** code, HuffmanNode* head){
    if(Tree->left == NULL && Tree->right == NULL) {
        if(Tree == head){
            height++;
        }
        code[Tree->letter] = (short*)calloc((height + 1), sizeof(short));
        code[Tree->letter][0] = height;

        for (unsigned int i = 1; i < height+1; ++i) {
            code[Tree->letter][i] = charCode[i];
        }

        return;
    }else{
        if(Tree->left){
            charCode[height + 1] = 0;
            encode(charCode, Tree->left, height + 1, code ,head);
        }
        if(Tree->right){
            charCode[height + 1] = 1;
            encode(charCode, Tree->right, height + 1, code, head);
        }
    }
}

short codeToBin(short** code,FILE* output,short bits, unsigned char* a){
    FILE * input2 = fopen("in.txt","rb");
    fseek(input2, 3, SEEK_CUR);
    short b;
    while(((b = fgetc(input2)) != EOF)){
        for(int i = 1;i <= code[b][0]; ++i){
            if(code[b][i] == 1)
                (*a) = (*a) | (1 << (7 - bits));
            bits++;
            if(bits == 8){
                fwrite(a, sizeof(unsigned char),1,output);
                bits = 0;
                (*a) = 0;
            }
        }
    }
    if(bits != 0){
        fwrite(a, sizeof(unsigned char), 1, output);
    }
    fclose(input2);
    return bits;
}

void writeBit(FILE* output,short* bits,char character, unsigned char* a){
    if(character){
        (*a) = (*a) | (1 << (7 - *bits));
    }

    (*bits) += 1;

    if((*bits) == 8){
        fwrite(a, sizeof(unsigned char), 1, output);
        (*bits) = 0;
        (*a) = 0;
    }
}

void printTree(HuffmanNode* head,FILE* output,short* bits, unsigned char* a){
    if((head->left == NULL) && (head -> right == NULL)) {
        short byte[8] = {0};
        charToByte(head->letter, byte);
        writeBit(output, bits, 0, a);
        for (int i = 0; i < 8; ++i) {
            writeBit(output, bits, byte[i], a);
        }
    } else {
        writeBit(output, bits, 1, a);
        if(head->left){
            printTree(head->left, output, bits, a);
        }
        if(head->right){
            printTree(head->right, output, bits, a);
        }
    }
}

void binToCode(unsigned char* bitBuffer, unsigned char character,int* count) {
    for (int i = 0; i < 8; ++i) {
        if ((character & (1 << (7 - i))) != 0)
            bitBuffer[*count] = '1';
        else
            bitBuffer[*count] = '0';
        *count += 1;
    }
}

int Read(FILE* input, unsigned char* buffer, unsigned char* bitBuffer){
    int processed = 0;
    int count = fread(buffer, sizeof(unsigned char), bufferSize, input);
    for(int i = 0;i < count; ++i){
        binToCode(bitBuffer, buffer[i], &processed);
    }
    return count * 8;
}

void recoverTree(unsigned char* bitBuffer, unsigned char* buffer, FILE* input, HuffmanNode**head, int* count, int* processed){
    if(bitBuffer[*count] == '0'){
        unsigned char byte[8];
        (*count) += 1;
        HuffmanNode *currentHuffmanNode = (HuffmanNode *)calloc(1, sizeof(HuffmanNode));
        if(*count >= ((*processed) - 8)) {
            unsigned char tempByte[8];
            int idx = 0;
            for(;*count + idx < *processed; ++idx){
                tempByte[idx] = bitBuffer[*count];
            }
            *count = 0;
            *processed = Read(input,buffer,bitBuffer);
            for(; idx < 8; ++idx){
                tempByte[idx] = bitBuffer[*count];
                (*count) += 1;
            }
            for (int i = 0; i < 8; ++i) {
                byte[i] = tempByte[i];
            }
        }
        
        else {
            for (int i = 0; i < 8; ++i) {
                byte[i] = bitBuffer[*count];
                (*count) += 1;
            }
        }
        currentHuffmanNode->letter = byteToChar(byte);
        *head = currentHuffmanNode;
    }
    else {
        (*count) += 1;
        if (*count >= bitBufferSize)
        {
            *processed = Read(input,buffer,bitBuffer);
            (*count) = 0;
        }
        HuffmanNode *root = (HuffmanNode *)calloc(1, sizeof(HuffmanNode));
        *head = root;
        if ((*head)->left == NULL)
            recoverTree(bitBuffer, buffer, input, &(*head)->left, count, processed);
        if ((*head)->right == NULL)
            recoverTree(bitBuffer, buffer, input, &(*head)->right, count, processed);
    }
}

void decode(FILE* output, FILE* input, unsigned char* buffer, unsigned char* bitBuffer, int* count, HuffmanNode* head, char bits, int* processed){
    unsigned char character[8];
    HuffmanNode* root = head;
    short idx = 0;
    do{
        if((*count) >= (*processed - 8)) {
            for (; *count < *processed; (*count) += 1) {
                character[idx] = bitBuffer[*count];
                idx++;
            }
            *processed = Read(input, buffer, bitBuffer);
            if (*processed == 0) {
                *count = 0;
                for (; *count < ((bits - '0') - 7 + idx); (*count) += 1) {
                       if (character[*count] == '1' && (root->right) != NULL) {
                    root = root->right;
                } else if (character[*count] == '0' && (root->left) != NULL) {
                    root = root->left;
                } else {
                    fprintf(output, "%c", root->letter);
                    if(root != head)
                        (*count) -= 1;
                    root = head;
                }
                    
                }
                if (root != head) {
                    fprintf(output, "%c", root->letter);
                }
                return;
            } else {
                *count = 0;
                for (; idx < 8; ++idx) {
                    character[idx] = bitBuffer[*count];
                    *count += 1;
                }
                idx = 0;
                for (int j = 0; j < 8; ++j) {
                    if (character[j] == '1' && (root->right) != NULL) {
                        root = root->right;
                    } else if (character[j] == '0' && (root->left) != NULL) {
                        root = root->left;
                    } else {
                        fprintf(output, "%c", root->letter);
                        if (root != head)
                            j--;
                        root = head;
                    }
                }
            }
        } else {
            for(;*count <= (*processed - 8);(*count) += 1){
                   if (bitBuffer[*count] == '1' && (root->right) != NULL) {
                    root = root->right;
                } else if (bitBuffer[*count] == '0' && (root->left) != NULL) {
                    root = root->left;
                } else {
                    fprintf(output, "%c", root->letter);
                    if(root != head)
                        (*count) -= 1;
                    root = head;
                }
            }
        }
    } while(1);
}

void freeTree(HuffmanNode* tree){
    if(tree){
        if (tree->left)
            freeTree(tree->left);
        if (tree->right)
            freeTree(tree->right);
        free(tree);
    }
}
void freeCodes(short* code[countChars]) {
    for (int i = 0; i < countChars; ++i) {
        if(code[i] != NULL)
            free(code[i]);
    }
    free(code);
}
