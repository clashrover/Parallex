#ifndef LINKLIST_H
#define LINKLIST_H


typedef struct node* Node;
Node new_Node(void* d);

typedef struct LinkList* linkList;
linkList new_List();

void push_back_List(void* data, linkList l);
void* pop_front_List(linkList l);
void free_List(linkList l);
void print_intList(linkList l);

// Online struct of iterator is public.
struct Iterator{
    linkList l;
    Node current;
};
typedef struct Iterator* iterator; 

iterator new_Iterator(linkList l);
void* next_Iterator(iterator i);
void free_Iterator(iterator i);

void insert_List(Node n,int pos,linkList l);
void* delete_List(int pos, linkList l);

#endif