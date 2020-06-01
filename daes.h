#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define L8(x) ((x<<8)|(x>>24))
#define sTrans(src) (s[(src)>>4][(src)&15])
#define sTransInv(src) (sInv[(src)>>4][(src)&15])
#define tTrans(l,src) (t[l][(src)>>4][(src)&15])
#define tTransInv(l,src) (tInv[l][(src)>>4][(src)&15])
typedef unsigned int i32;
typedef unsigned char i8;
i32 glsExt(i32 a,i32 b){
    i32 ans=0,mod=0x8d800000,chk=0x80000000;
    while(a){
        if(a&1) ans^=b;
        a=a>>1;
        b=b<<1;
    }
    while(mod!=0x8d){
        if(ans&chk) ans^=mod;
        chk=chk>>1;
        mod=mod>>1;
    }
    return (i8)ans;
}
void keyInv(i32 *key){
    i8 tmp[4];
    for(int i=4;i<=39;i++){
        tmp[0]=glsExt(key[i]>>24,0x0e)^glsExt((key[i]>>16)&255,0x0b)^glsExt((key[i]>>8)&255,0x0d)^glsExt(key[i]&255,0x09);
        tmp[1]=glsExt(key[i]>>24,0x09)^glsExt((key[i]>>16)&255,0x0e)^glsExt((key[i]>>8)&255,0x0b)^glsExt(key[i]&255,0x0d);
        tmp[2]=glsExt(key[i]>>24,0x0d)^glsExt((key[i]>>16)&255,0x09)^glsExt((key[i]>>8)&255,0x0e)^glsExt(key[i]&255,0x0b);
        tmp[3]=glsExt(key[i]>>24,0x0b)^glsExt((key[i]>>16)&255,0x0d)^glsExt((key[i]>>8)&255,0x09)^glsExt(key[i]&255,0x0e);
        key[i]=(tmp[0]<<24)|(tmp[1]<<16)|(tmp[2]<<8)|tmp[3];
    }
}
void aesBlockInv(i32 *src,i32 *key,i32 *dst){
    for(int i=0;i<=4;i++) src[i]^=key[40+i];
    for(int i=9;i>=1;i--){
        for(int j=0;j<4;j++) dst[j]=tTransInv(0,((src[j]>>24)&255))^tTransInv(1,((src[(j+3)&3]>>16)&255))^tTransInv(2,((src[(j+2)&3]>>8)&255))^tTransInv(3,((src[(j+1)&3])&255));
        for(int j=0;j<4;j++) src[j]=dst[j]^key[(i<<2)|j];
    }
    for(int j=0;j<4;j++) dst[j]=(((sTransInv(src[j]>>24)&255)<<24)|(sTransInv((src[(j+3)&3]>>16)&255)<<16)|(sTransInv((src[(j+2)&3]>>8)&255)<<8)|sTransInv(src[(j+1)&3]&255))^key[j];
}
