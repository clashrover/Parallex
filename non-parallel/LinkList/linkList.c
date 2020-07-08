#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
        l=NULL;
        return;
    }
    if(n->next==NULL){
        free(n->data);
        n->data = NULL;
        free(n);
        n=NULL;
        free(l);
        l=NULL;
        return;
    }
    free(n->data);
    n->data = NULL;
    l->head = n->next;
    free(n);
    n=NULL;
    free_List(l);
}



struct Iterator{
    linkList l;
    Node current;
};
typedef struct Iterator* iterator; 

iterator new_Iterator(linkList l){
    iterator i = (iterator)malloc(sizeof(struct Iterator));
    i->l=l;
    i->current = l->head;
}

void* next_Iterator(iterator i){
    void* data = i->current->data;
    i->current = i->current->next;
    return data;
}

void free_Iterator(iterator i){
    i->l=NULL;
    i->current = NULL;
    free(i);
    i=NULL;
}

void insert_List(Node n,int pos,linkList l){
    if(pos<l->size){
        if(pos == 0){
            void* d=n->data;
            if(l->size == 1){
                n->next = l->head;
                l->head = NULL;
                l->head = n;
                l->tail = n->next;
                l->size = 2;
            }else{
                n->next = l->head;
                l->head = n;
                l->size++;
            }
        }else{
            Node c = l->head;
            int j=0;
            while(j<pos-1){
                c=c->next;
                j++;
            }
            Node n1 = c->next;
            n->next = n1;
            c->next = n;
            l->size++;
        }
    }
    return;
}

void* delete_List(int pos, linkList l){
    if(pos<l->size){
        if(pos == 0){
            Node n = l->head;
            void* d=n->data;
            if(l->size == 1){
                l->head = NULL;
                l->tail = NULL;
                l->size = 0;
                free(n);
                n=NULL;
                return d;
            }else{
                l->head = n->next;
                n->next = NULL;
                l->size--;
                free(n);
                n=NULL;
                return d;
            }
        }else{
            Node c = l->head;
            int j=0;
            while(j<pos-1){
                c=c->next;
                j++;
            }
            Node n = c->next;
            void* d = n->data;
            c->next = n->next;
            n->next = NULL;
            n->data =NULL;
            free(n);
            n=NULL;
            return d;
        }
    }
    return NULL;
}