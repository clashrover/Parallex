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

#endif