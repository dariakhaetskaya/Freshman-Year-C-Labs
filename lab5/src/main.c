#include "zipper.h"

int main() {
    FILE* input = fopen("in.txt" ,"rb");
    FILE* output= fopen("out.txt","wb");

    int mode = fgetc(input);
    fseek(input, 2,SEEK_CUR);

    if (mode == 'c'){ //zip
        int symbols[countChars] = {0};
        unsigned char buffer[bufferSize];
        int count = 1;

        while(count > 0){ // calculate frequency
            count = fread(buffer, sizeof(unsigned char), bufferSize, input);
            for (int i = 0; i < count; ++i) {
                symbols[buffer[i]]++;
            }
        }

        for(int i = 0;i < countChars; ++i){ // check file
            if(symbols[i] != 0)
                break;
            if(i == countChars - 1){
                fclose(input);
                fclose(output);
                return 0;
            }
        }

        short bitsInRemain = 0;
        HuffmanNode *root = buildHuffmanTree(symbols);
        short **code=(short**)calloc(countChars, sizeof(short*));
        if(code==NULL){
            fprintf(output,"error memory allocation");
            freeTree(root);
            fclose(input);
            fclose(output);
            return 0;
        }
        for(int i = 0;i < countChars; ++i){
            code[i] = NULL;
        }
        short charCode[estimatedTreeHeight] = {0};
        encode(charCode, root, 0, code, root);
        unsigned char a;
        fseek(output, 1, SEEK_CUR);
        printTree(root, output, &bitsInRemain, &a);
        bitsInRemain = codeToBin(code, output, bitsInRemain, &a);
        bitsInRemain -= 1;

        if(bitsInRemain < 0){
            bitsInRemain = 7;
        }
        fseek(output, 0, SEEK_SET);
        fprintf(output,"%hd",bitsInRemain);

        freeTree(root);
        freeCodes(code);

       } else { //unzip

        unsigned char buffer[bufferSize];
        unsigned char bitBuffer[bitBufferSize];
        HuffmanNode **root = (HuffmanNode **)calloc(1, sizeof(HuffmanNode *));

        char bitsInRemain = getc(input);

        if(bitsInRemain < '0' || bitsInRemain > '8'){
            free(root);
            fclose(input);
            fclose(output);
            return 0;
        }
        int count = 0;
        int processed = Read(input,buffer,bitBuffer);
        recoverTree(bitBuffer,buffer, input, root, &count,&processed);
        if (count == 0){
            processed = Read(input,buffer,bitBuffer);
        }
        decode(output, input, buffer,bitBuffer, &count, *root, bitsInRemain, &processed);
        freeTree(*root);
        free(root);

       }

    fclose(input);
    fclose(output);
    return 0;
}
