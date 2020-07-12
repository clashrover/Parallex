#include "linkList.h"
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
    linkList l = new_List(int_compare);
    for(int i=0;i<10;i++){
        int* x = (int*)malloc(sizeof(int));
        *x=i;
        int* y = (int*)malloc(sizeof(int));
        *y=100*i;
        insert((void*)x,(void*)y, l);
    }
    //--- Test iterator ---//
    // iterator i = new_Iterator(l);
    // while(hasNext(i)==1){
    //     int* d = (int*) next(i);
    //     printf("%d\n",*d); 
    // }
    // free_Iterator(i);

    //--- Test get ---//
    // int* d = (int*)malloc(sizeof(int));
    // *d = 0;
    // int* d1 = (int*) get((void*)d,l);
    // if(d1!=NULL){
    //     printf("%d\n",*d1);
    // }
    // free(d); 

    //--- Test has ---//
    // int* d = (int*)malloc(sizeof(int));
    // *d = 5;
    // if(has((void*)d,l) == 1){
    //     printf("has\n");
    // }else{
    //     printf("not found\n");
    // }
    // free(d);

    //--- Test delete ---//
    // int* i1=(int*)malloc(sizeof(int));
    // *i1=0;
    // while(size(l)>0){
    //     iterator i = new_Iterator(l);
    //     while(hasNext(i)==1){
    //         int* d = (int*) next(i);
    //         printf("%d ",*d); 
    //     }
    //     printf("\n");
    //     free_Iterator(i);
    //     void* dat = delete((void*)i1,l);
    //     if(dat==NULL){
    //         break;
    //     }
    //     free(dat);
    //     *i1 = *i1 +1;
    // }
    // free(i1);

    // testing of iterator done above //
    free_List(l);
}