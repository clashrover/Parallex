#include "linkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    clock_t t; 
    t = clock();
    for(int i=0;i<1000;i++){
        int* x = (int*)malloc(sizeof(int));
        *x=i;
        int* y = (int*)malloc(sizeof(int));
        *y=100*i;
        insert((void*)x,(void*)y, l);
    }
    // t = clock() - t;
    // double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    // printf("Time Single threaded took %f seconds to execute \n", time_taken); 
    
    // //--- Test iterator ---//
    // iterator i = new_Iterator(l);
    // while(hasNext(i)==1){
    //     int* d = (int*) next(i);
    //     // printf("%d\n",*d); 
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
    // clock_t t; 
    // t = clock();
    int* i1=(int*)malloc(sizeof(int));
    *i1=0;
    while(*i1<1000){
        void*d = delete((void*)i1,l);
        free(d);
        *i1 = *i1 +2;
    }
    free(i1);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("Time Single threaded took %f seconds to execute \n", time_taken); 
    
    iterator i = new_Iterator(l);
    while(hasNext(i)==1){
        int* d = (int*) next(i);
        printf("%d ",*d); 
    }
    printf("\n");
    free_Iterator(i);

    // testing of iterator done above //
    free_List(l);
}