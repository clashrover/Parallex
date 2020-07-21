#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int int_compare(void* i,void* j){
    if(*(int*)i > *(int*)j){
        return 1;
    }
    if(*(int*)i < *(int*)j){
        return -1;
    }
    return 0;
}

int main(){
    BST b = new_BST(int_compare);
    for(int i=0;i<10;i++){
        int* key = (int*)malloc(sizeof(int));
        int* data = (int*)malloc(sizeof(int));
        *key = i;
        *data = 100*i;
        insert((void*)key,(void*)data,b);
    }
    for(int i=-10;i<0;i++){
        int* key = (int*)malloc(sizeof(int));
        int* data = (int*)malloc(sizeof(int));
        *key = i;
        *data = 100*i;
        insert((void*)key,(void*)data,b);
    }
    for(int i=-5;i<0;i++){
        int* key = (int*)malloc(sizeof(int));
        *key = i;
        void* data = get((void*)key,b);
        printf("%d ", *(int*)data);
    }
    printf("\n");
}