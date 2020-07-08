#include "linkList.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    linkList l = new_List();
    for(int i=0;i<10;i++){
        int* x = (int*)malloc(sizeof(int));
        *x=i;
        push_back_List((void*)x,l);
    }
    for(int i=0;i<10;i++){
        char* x = (char*)malloc(sizeof(char));
        *x='a'+i;
        push_back_List((void*)x,l);
    }
    for(int i=0;i<10;i++){
        int* di =(int*) pop_front_List(l);
        printf("%d",*di);
        free(di);
    }
    for(int i=0;i<10;i++){
        char* di =(char*) pop_front_List(l);
        printf("%c",*di);
        free(di);
    }
    // print_intList(l);
    // iterator i = new_Iterator(l);
    free_List(l);
}