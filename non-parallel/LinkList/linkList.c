#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    void* key;
    void* data;
    struct node* next;
};

typedef struct node* Node;

Node new_Node(void* key,void* data){
    Node n = (Node)malloc(sizeof(struct node));
    n->data = data;
    n->key = key;
    n->next = NULL;
    return n;
}

typedef int (*Compare) (void* key1, void* key2);

struct LinkList{
    struct node* head;
    int size;
    Compare compare;
};

typedef struct LinkList* linkList;

linkList new_List(Compare c){
    linkList l = (linkList)malloc(sizeof(struct LinkList)); 
    Node n = new_Node(NULL,NULL);
    l->head = n;
    l->size = 0;
    l->compare = c;
    return l;
}

int size(linkList l){
    return l->size;
}

void insert(void* key, void* data,linkList l){
    Node prev=l->head;
    Node n = new_Node(key,data);
    Node curr;
    while((curr = prev->next)!=NULL){
        if(l->compare(curr->key,key)>0){
            prev->next = n;
            n->next = curr;
            l->size++;
        }
        prev= curr;
    }
    prev->next = n;
    n->next = curr;
    l->size++;
}

void* delete(void* key, linkList l){
    Node prev = l->head;
    Node curr;
    while((curr = prev->next) != NULL){
        if(l->compare(curr->key,key)==0){
            prev->next = curr->next;
            curr->next = NULL;
            l->size--;
            free(curr->key);
            curr->key = NULL;
            void* data = curr->data;
            free(curr);
            return data;
        }
        prev = curr;
    }
    return NULL;
}

void* get(void*key, linkList l){
    Node prev = l->head;
    Node curr = l->head->next;
    if(l->size == 0){
        perror("Get: List empty\n");
        return NULL;
    }
    while(l->compare(curr->key,key)<0){
        prev = curr;
        curr=curr->next;
        if(curr==NULL){
            perror("Get: key not found\n");
            return NULL;
        }
    }
    if(l->compare(curr->key,key)!=0){
        perror("Get: key not found\n");
        return NULL;
    }
    return curr->data;
}

int has(void*key, linkList l){
    Node prev = l->head;
    Node curr = l->head->next;
    if(l->size == 0){
        return 0;
    }
    while(l->compare(curr->key,key)<0){
        prev = curr;
        curr=curr->next;
        if(curr==NULL){
            return 0;
        }
    }
    if(l->compare(curr->key,key)!=0){
        return 0;
    }
    return 1;
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
        free(n->key);
        n->key = NULL;
        free(n);
        n=NULL;
        free(l);
        l=NULL;
        return;
    }
    free(n->data);
    n->data = NULL;
    free(n->key);
    n->key = NULL;
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

void* next(iterator i){
    i->current = i->current->next;
    void* data = i->current->data;
    return data;
}

int hasNext(iterator i){
    if(i->current->next != NULL){
        return 1;
    }
    return 0;
}

void free_Iterator(iterator i){
    i->l=NULL;
    i->current = NULL;
    free(i);
    i=NULL;
}
