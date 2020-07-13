#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

// IMPLEMENTING HAND-IN-HAND Locking //
// Create a buffer to collect operations, when find, get, iterator is called empty the buffer //
// by executing the instructions using threads. Buffer consists of insert and delete instructions//

//------------------------------------------------------------------

struct node
{
    void* key;
    void* data;
    struct node* next;
    pthread_mutex_t lock;
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
typedef struct buffer* Buffer;
struct LinkList{
    struct node* head;
    int size;
    Compare compare;
    Buffer buf;
};
typedef struct LinkList* linkList;
void clear_buffer(linkList l);

struct event_node{
    int type;
    void* key;
    void* data;
    linkList list;
};
typedef struct event_node* event;

struct buffer{
    int size;
    event array[10];
    int pos;
};

linkList new_List(Compare c){
    linkList l = (linkList)malloc(sizeof(struct LinkList)); 
    Node n = new_Node(NULL,NULL);
    l->head = n;
    l->size = 0;
    l->compare = c;

    l->buf = (Buffer)malloc(sizeof(struct buffer));
    l->buf->size=0;
    l->buf->pos = 0;
    return l;
}

int size(linkList l){
    return l->size;
}

//------------------------------------------------------------------

void* insert(void* arg){
    event e = (event)arg;
    void* key = e->key;
    void* data = e->data;
    linkList l = e->list;
    Node prev=l->head;
    pthread_mutex_lock(&prev->lock);
    printf("Thread number lock prev %ld\n", pthread_self());
    Node n = new_Node(key,data);
    Node curr;
    while((curr = prev->next)!=NULL){
        pthread_mutex_lock(&curr->lock);
        printf("Thread number lock curr %ld\n", pthread_self());
        if(l->compare(curr->key,key)>0){
            prev->next = n;
            n->next = curr;
            l->size++;
            // printf("Thread number %ld\n", pthread_self());
            printf("Thread number unlock prev %ld\n", pthread_self());
            pthread_mutex_unlock(&prev->lock);
            printf("Thread number unlock curr ending %ld\n", pthread_self());
            pthread_mutex_unlock(&curr->lock);
            pthread_exit(NULL);
        }
        printf("Thread number unlock prev %ld\n", pthread_self());
        pthread_mutex_unlock(&prev->lock);
        prev= curr;
    }
    prev->next = n;
    n->next = curr;
    l->size++;
    printf("Thread number unlock prev ending %ld\n", pthread_self());
    pthread_mutex_unlock(&prev->lock);
    pthread_exit(NULL);
}

void pInsert(void* key, void* data,linkList l){
    if(l->buf->size <10){
        event e = (event)malloc(sizeof(struct event_node));
        e->type=1;
        e->key = key;
        e->data = data;
        e->list = l;
        l->buf->array[l->buf->pos] = e;
        l->buf->pos++;
        l->buf->size++;
    }else{
        clear_buffer(l);
        event e = (event)malloc(sizeof(struct event_node));
        e->type=1;
        e->key = key;
        e->data = data;
        e->list = l;
        l->buf->array[l->buf->pos] = e;
        l->buf->pos++;
        l->buf->size++;
    }
}

//------------------------------------------------------------------

void* delete(void* arg){
    event e = (event)arg;
    void* key = e->key;
    linkList l = e->list;

    Node prev = l->head;
    Node curr = l->head->next;
    if(l->size == 0){
        perror("Delete: List empty\n");
        pthread_exit(NULL);
    }
    while(l->compare(curr->key,key)<0){
        prev = curr;
        curr=curr->next;
        if(curr==NULL){
            perror("Delete: key not found\n");
            pthread_exit(NULL);
        }
    }
    if(l->compare(curr->key,key)!=0){
        perror("Delete: key not found\n");
        pthread_exit(NULL);
    }
    prev->next = curr->next;
    curr->next = NULL;
    free(curr->key);
    curr->key = NULL;
    void* data = curr->data;
    free(curr);
    curr = NULL;
    l->size--;
    pthread_exit(data);
}


void pDelete(void* key, linkList l){
    if(l->buf->size <10){
        event e = (event)malloc(sizeof(struct event_node));
        e->type=2;
        e->key = key;
        e->data = NULL;
        e->list = l;
        l->buf->array[l->buf->pos] = e;
        l->buf->pos++;
        l->buf->size++;
    }else{
        clear_buffer(l);
        event e = (event)malloc(sizeof(struct event_node));
        e->type=2;
        e->key = key;
        e->data = NULL;
        e->list = l;
        l->buf->array[l->buf->pos] = e;
        l->buf->pos++;
        l->buf->size++;
    }
}

//------------------------------------------------------------------

void* get(void*key, linkList l){
    clear_buffer(l);
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
    clear_buffer(l);

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

//------------------------------------------------------------------

void free_List(linkList l){
    clear_buffer(l);
    Node n = l->head;
    if(n==NULL){
        free(l->buf);
        l->buf = NULL;
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
        free(l->buf);
        l->buf = NULL;
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

//------------------------------------------------------------------

struct Iterator{
    linkList list;
    Node current;
};
typedef struct Iterator* iterator; 

iterator new_Iterator(linkList l){
    clear_buffer(l);
    iterator i = (iterator)malloc(sizeof(struct Iterator));
    i->list=l;
    i->current = l->head;
}

void* next(iterator i){
    clear_buffer(i->list);
    i->current = i->current->next;
    void* data = i->current->data;
    return data;
}

int hasNext(iterator i){
    clear_buffer(i->list);
    if(i->current->next != NULL){
        return 1;
    }
    return 0;
}

void free_Iterator(iterator i){
    clear_buffer(i->list);
    i->list=NULL;
    i->current = NULL;
    free(i);
    i=NULL;
}

//------------------------------------------------------------------

void clear_buffer(linkList l){
    Buffer b = l->buf;
    if(b->size == 0){
        return;
    }
    int i=0;
    pthread_t threads[b->size];
    int iret[b->size];
    while(i<b->size){
        event e = b->array[i];
        if(e->type == 1){
            iret[i] = pthread_create(&threads[i],NULL,insert,(void*)e);
        }else{
            iret[i] = pthread_create(&threads[i],NULL,delete,(void*)e);
        }
        if(iret[i] != 0) {
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    void** d;
    for(int j=0;j<b->size;j++){
        pthread_join(threads[j],d);
    }
    for(int j=0;j<b->size;j++){
        free(b->array[j]);
        b->array[j]=NULL;
    }
    b->size = 0;
    b->pos = 0;
}