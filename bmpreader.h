//read bmp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
struct bmpClass{
    unsigned char fileHdr[20];
    unsigned char infoHdr[50];
    int *bmpBuffer,*size;
    void init(FILE * bmpInput){
        fread(fileHdr,1,14,bmpInput);
        fread(infoHdr,1,40,bmpInput);
        size=(int *)(infoHdr+20);
        bmpBuffer=(int *)malloc(((*size+7)>>2)<<2);
        memset(bmpBuffer,0,((*size+7)>>2)<<2);
        fread(bmpBuffer,1,*size,bmpInput);
        printf("Successfully read bitmap data of %d bytes.\n",*size);
    }
    void save(FILE *bmpOutput,unsigned int *cryptRes){
        fwrite(fileHdr,1,14,bmpOutput);
        fwrite(infoHdr,1,40,bmpOutput);
        int length=((((((*size+3)>>2)<<2)+3)>>2)<<2);
        fwrite(cryptRes,1,length,bmpOutput);
        free(bmpBuffer);
    }
};