#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef unsigned int i32;
typedef unsigned char i8;

void vKeyInv(i8 *key){
    while(*key){
        *key=(~*key)+1;
        key++;
    }
}

void vBlock(i8 *buffer,i32 size,i8 *key,i32 len){
    for(int i=0;i<size;i++) buffer[i]+=key[i%len];
}