#include <stdlib.h>

typedef struct node* Node;
struct node{
    void* key;
    void* data;
    Node left;
    Node right;
};


Node new_Node(void* key, void* data){
    Node n= (Node)malloc(sizeof(struct node));
    n->key = key;
    n->data = data;
    n->left  = NULL;
    n->right = NULL;
    return n;
}

typedef int (*Compare)(void* key1,void* key2);
struct bst{
    Node* root;
    Compare compare;
};

typedef struct bst* BST;


BST new_BST(Compare c){
    BST b = (BST)malloc(sizeof(struct bst));
    b->compare = c;
    b->root = NULL;
    return b;
}

void my_insert(Node n, Node root,BST b){
    if(b->compare(n->key,root->key)<=0){
        if(root->left !=NULL){
            my_insert(n,root->left,b);
        }else{
            root->left = n;
        }
    }
    else{
        if(root->right != NULL){
            my_insert(n,root->right,b);   
        }else{
            root->right = n;
        }
    }
    return;
}

void insert(void* key, void*data, BST b){
    Node n = new_Node(key,data);
    if(b->root == NULL){
        b->root = n;
        return;
    }
    my_insert(n,b->root,b);
}


void* delete(void* key, BST b){
    if(b->root == NULL){
        return NULL;
    }
    if(b->compare(key,root->key) == 0){
        if(root->left !=NULL){
            return my_delete(key,root->left,b);
        }else{
            return NULL;
        }
    }
    return my_delete(key,b->root,b);
}
