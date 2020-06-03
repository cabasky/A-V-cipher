#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "tbox.h"
#include "bmpreader.h"
#include "aes.h"
#include "daes.h"
#include "vcrypt.h"
using namespace std;
typedef unsigned int i32;
typedef unsigned char i8;

int main(){
    //freopen("out2.txt","w",stdout);
    i8 path[128],key[1024];
    i32 f1,f2;
    printf("Input the file name:\n");
    scanf("%s",path);
    FILE *bmpIn=fopen((const char *)path,"rb");
    FILE *bmpOut=fopen("result.bmp","wb");
    bmpClass rawBmp;
    rawBmp.init(bmpIn);
    fclose(bmpIn);
    printf("Select a algorithm to deal with data: 1.AES 2.Vigenere\n");
    scanf("%d",&f1);
    printf("Encrypt(1) or decrypt(2):");
    scanf("%d",&f2);
    printf("Input your key:\n");
    if(f1==1){
        int psize=(*(rawBmp.size)+3)>>2,p=0;
        i32 *cryptRes=(i32*)malloc((psize<<2)+16);
        i32 keyAES[100];
        scanf("%s",key);
        while(strlen((const char *)key)!=16){    
            printf("The length must be 16 bytes, input again:\n");
            scanf("%s",key);
        }
        c2i(key,keyAES,16);
        keyExt(keyAES);
        if(f2==1)
            while(p<psize){
                aesBlock((i32*)rawBmp.bmpBuffer+p,keyAES,cryptRes+p);
                p+=4;
            }
        else if(f2==2){
            keyInv(keyAES);
            while(p<psize){
                aesBlockInv((i32*)rawBmp.bmpBuffer+p,keyAES,cryptRes+p);
                p+=4;
            }
        }
        rawBmp.save(bmpOut,cryptRes);
        free(cryptRes);
    }
    else if(f1==2){
        scanf("%s",key);
        int len=strlen((const char *)key);
        if(f2==2) vKeyInv(key);
        vBlock((i8*)rawBmp.bmpBuffer,*(rawBmp.size),key,len);
        rawBmp.save(bmpOut,(i32*)rawBmp.bmpBuffer);
    }
    fclose(bmpOut);
    return 0;
}