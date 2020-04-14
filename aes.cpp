#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "tbox.h"
#define L8(x) ((x<<8)|(x>>24))
#define sTrans(src) (s[(src)>>4][(src)&15])
#define tTrans(l,src) (t[l][(src)>>4][(src)&15])
using namespace std;
typedef unsigned int i32;
typedef unsigned char i8;

i32 gFunction(i32 key,i32 l){
    key=L8(key);
    i32 ans=0;
    ans=(((sTrans(key>>24))<<24)|
    ((sTrans((key>>16)&255))<<16)|
    ((sTrans((key>>8)&255))<<8)|
    (sTrans(key&255)))^
    (rc[l]<<24);
    return ans;
}

void keyExt(i32 *key){
    for(int i=4;i<44;i+=4){
        key[i]=gFunction(key[i-1],i>>2)^key[i-4];
        key[i+1]=key[i-3]^key[i];
        key[i+2]=key[i-2]^key[i+1];
        key[i+3]=key[i-1]^key[i+2];
    }
}

void aesBlock(i32 *src,i32 *key,i32 *dst){
    keyExt(key);
    for(int i=0;i<4;i++)
        src[i]^=key[i];
    for(int i=0;i<4;i++){
        printf("%08x",src[i]);
    }
    printf("\n");
    puts("");
    for(int i=1;i<10;i++){
        printf("%d.\n",i);
        for(int j=0;j<4;j++){
            dst[j]=tTrans(0,((src[j]>>24)&255))^tTrans(1,((src[(j+1)&3]>>16)&255))^tTrans(2,((src[(j+2)&3]>>8)&255))^tTrans(3,((src[(j+3)&3])&255));
        }
        for(int j=0;j<4;j++){
            src[j]=dst[j]^key[(i<<2)|j];
        }
        for(int j=0;j<4;j++){
            printf("%08x",src[j]);
        }
        puts("");
        puts("");
    }
    for(int i=0;i<4;i++){
        printf("\n%02x\n",(src[i]>>24)&255);
        dst[i]=((sTrans((src[i]>>24)&255)<<24)|(sTrans((src[(i+1)&3]>>16)&255)<<16)|(sTrans((src[(i+2)&3]>>8)&255)<<8)|sTrans(src[(i+3)&3]&255))^key[40+i];
    }
}
void c2i(i8 *src,i32 *dst,int n){
    int stp=n>>2;
    for(int i=0;i<stp;i++)
        dst[i]=(src[i<<2]<<24)|(src[(i<<2)+1]<<16)|(src[(i<<2)+2]<<8)|(src[(i<<2)+3]);
}
int main(){
    freopen("out2.txt","w",stdout);
    i32 key[100]={
        0x31323334,0x35363738,0x39303132,0x33343536
    };
    i32 key2[100]={0x3CA10B21,0x57F01916,0x902E1380,0xACC107BD};
    keyExt(key2);
    printf("%08x\n",gFunction(key2[3],1));
    keyExt(key);
    puts("---key---");
    for(int i=0;i<44;i++){
        
        printf("%08x",key[i]);
        if((i+1)%4==0){
            puts("");
            puts("");
        }
    }
    puts("---------");


    i32 data32[100];
    i32 dst[100];
    i8 data[100]="wuyikoeidaisuki!";
    c2i(data,data32,16);
    for(int i=0;i<4;i++){
        printf("%08x",data32[i]);
    }
    puts("");
    aesBlock(data32,key,dst);
    for(int i=0;i<4;i++){
        printf("%08x",dst[i]);
    }
    return 0;
}