#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

// IMPLEMENTING HAND-IN-HAND Locking //
// Create a buffer to collect operations, when find, get, iterator is called empty the buffer //
// by executing the instructions using threads. Buffer consists of insert and delete instructions//

//------------------------------------------------------------------

struct node;
typedef struct node* Node;

Node new_Node(void* key,void* data);

typedef int (*Compare) (void* key1, void* key2);
typedef struct buffer* Buffer;
struct LinkList;
typedef struct LinkList* linkList;
void clear_buffer(linkList l);

struct event_node;
typedef struct event_node* event;

struct buffer;

linkList new_List(Compare c);

int size(linkList l);

//------------------------------------------------------------------

void* insert(void* arg);

void pInsert(void* key, void* data,linkList l);

//------------------------------------------------------------------

void* delete(void* arg);


void pDelete(void* key, linkList l);

//------------------------------------------------------------------

void* get(void*key, linkList l);

int has(void*key, linkList l);

//------------------------------------------------------------------

void free_List(linkList l);

//------------------------------------------------------------------

struct Iterator{
    linkList list;
    Node current;
};
typedef struct Iterator* iterator; 

iterator new_Iterator(linkList l);

void* next(iterator i);

int hasNext(iterator i);

void free_Iterator(iterator i);

//------------------------------------------------------------------


void clear_buffer(linkList l);

#endif