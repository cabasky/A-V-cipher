#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int main(){
    char a[]="12345678";
    int *b=(int *)a;
    printf("%x %x %x %x",*b,b[1],b[2],b[3]);
    return 0;
}