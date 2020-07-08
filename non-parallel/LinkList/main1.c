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
    linkList l = new_List();
    for(int i=0;i<10;i++){
        int* x = (int*)malloc(sizeof(int));
        *x=i;
        push_back_List((void*)x,l);
    }
    // print_intList(l);
    iterator i = new_Iterator(l);
    // while(i->current!=NULL){
    //     int* d = (int*) next_Iterator(i);
    //     printf("%d\n",*d); 
    // }
    int* a1 = (int*)malloc(sizeof(int));
    *a1 = 55;
    int* a2 = (int*)malloc(sizeof(int));
    *a2 = 56;
    int* a3 = (int*)malloc(sizeof(int));
    *a3 = 57;
    Node nn = new_Node((void*)a1);
    insert_List(nn,0,l);
    Node n1 = new_Node((void*)a2);
    insert_List(n1,2,l);
    Node n2 = new_Node((void*)a3);
    insert_List(n2,3,l);
    int* p = (int*) delete_List(0,l);
    free(p);
    p = (int*) delete_List(0,l);
    free(p);
    p = (int*) delete_List(10,l);
    free(p);
    iterator j = new_Iterator(l);
    while(j->current!=NULL){
        int* d = (int*) next_Iterator(j);
        printf("%d\n",*d); 
    }
    free_Iterator(i);
    free_Iterator(j);
    free_List(l);
}