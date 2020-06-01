#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "tbox.h"
#include "bmpreader.h"
#include "aes.h"
#include "daes.h"
using namespace std;
typedef unsigned int i32;
typedef unsigned char i8;

int main(){
    //freopen("out2.txt","w",stdout);
    FILE *bmpIn=fopen("a.bmp","rb");
    bmpClass rawBmp;
    rawBmp.init(bmpIn);
    fclose(bmpIn);
    int psize=(*(rawBmp.size)+3)>>2,p=0;
    i32 *cryptRes=(i32*)malloc((psize<<2)+16);
    cout<<endl;
    i32 key[100]={
        0x31323334,0x35363738,0x39303132,0x33343536
    };
    i32 data32[100];
    i32 dst[100];
    i8 data[100]="wuyikoeidaisuki!";
    c2i(data,data32,16);
    cout<<0<<endl;

    keyExt(key);
    while(p<psize){
        aesBlock((i32*)rawBmp.bmpBuffer+p,key,cryptRes+p);
        p+=4;
    }
    cout<<1<<endl;
    aesBlock(data32,key,dst);
    for(int i=0;i<4;i++){
        printf("%08x",cryptRes[i]);
    }
    cout<<endl;
    for(int i=0;i<4;i++){
        printf("%08x",dst[i]);
    }
    cout<<endl;
    FILE *bmpOut=fopen("b.bmp","wb");
    rawBmp.save(bmpOut,cryptRes);
    fclose(bmpIn);
    fclose(bmpOut);
    i32 data2[4]={0x77a55d65,0xd58e57b4,0xec08a861,0xbd82af89};
    i32 dst2[100];
    aesBlockInv(data2,key,dst2);
    for(int i=0;i<4;i++){
        printf("%08x",dst2[i]);
    }
    cout<<endl;
    //free(cryptRes);
    bmpIn=fopen("b.bmp","rb");
    bmpClass r2;
    r2.init(bmpIn);
    psize=(*(r2.size)+3)>>2,p=0;
    cout<<3<<endl;
    keyExt(key);
    keyInv(key);
    while(p<psize){
        aesBlockInv((i32*)r2.bmpBuffer+p,key,cryptRes+p);
        p+=4;
    }
    cout<<2<<endl;
    bmpOut=fopen("c.bmp","wb");
    rawBmp.save(bmpOut,cryptRes);
    free(cryptRes);
    fclose(bmpIn);
    fclose(bmpOut);
    return 0;
}