#include <stdio.h>
#include <stdlib.h>

struct node
{
    void* data;
    struct node* next;
};

typedef struct node* Node;

Node new_Node(void* d){
    Node n = (Node)malloc(sizeof(struct node));
    n->data = d;
    n->next = NULL;
    return n;
}

struct LinkList{
    struct node* head;
    struct node* tail;
    int size;
};

typedef struct LinkList* linkList;

linkList new_List(){
    linkList l = (linkList)malloc(sizeof(struct LinkList)); 
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void push_back_List(void* data, linkList l){
    Node n = new_Node(data);
    if(l->size == 0){
        l->head = n;
        l->tail = n;
        l->size+=1;
        return;
    }
    l->tail->next = n;
    l->tail = n;
    l->size += 1;
}

void* pop_front_List(linkList l){
    Node n = l->head;
    if(l->size == 0){
        return NULL;
    }
    l->head = n->next;
    n->next = NULL;
    l->size-=1;
    void* ans = n->data;
    free(n);
    return ans;
}

void free_List(linkList l){
    Node n = l->head;
    if(n==NULL){
        free(l);
        return;
    }
    if(n->next==NULL){
        free(n->data);
        free(n);
        free(l);
        return;
    }
    free(n->data);
    l->head = n->next;
    free(n);
    free_List(l);
}

void print_intList(linkList l){
    Node current = l->head;
    while(current != NULL){
        int* d = (int*)current->data;
        printf("Node : %d\n",*d);
        current = current->next;
    }
}