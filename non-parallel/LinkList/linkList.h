#ifndef LINKLIST_H
#define LINKLIST_H

struct node;

typedef struct node* Node;

Node new_Node(void* key,void* data);

typedef int (*Compare) (void* key1, void* key2);

struct LinkList;

typedef struct LinkList* linkList;

linkList new_List();

void insert(void* key, void* data,linkList l);

void* delete(void* key, linkList l);

void* get(void*key, linkList l);

int has(void*key, linkList l);

int size(linkList l);

void free_List(linkList l);



struct Iterator{
    linkList l;
    Node current;
};
typedef struct Iterator* iterator; 

iterator new_Iterator(linkList l);

void* next(iterator i);

int hasNext(iterator i);

void free_Iterator(iterator i);


#endif