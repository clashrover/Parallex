#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    Node root;
    Compare compare;
};

typedef struct bst* BST;


BST new_BST(Compare c){
    BST b = (BST)malloc(sizeof(struct bst));
    b->compare = c;
    b->root = NULL;
    return b;
}

void* my_get(void* key, Node root, BST b){
    if(root == NULL){
        return NULL;
    }
    if(b->compare(key,root->key)<0){
        return my_get(key,root->left,b);
    }
    if(b->compare(key,root->key)==0){
        return root->data;
    }
    return my_get(key,root->right,b);
    
}

void* get(void* key,BST b){
    if(b->root == NULL){
        return NULL;
    }
    return my_get(key,b->root,b);
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

Node find_delete_successor(Node root){
    Node parent = root;
    Node child = root->right;
    if(child==NULL){
        return NULL;
    }
    if(child->left == NULL){
        parent->right = child ->right;
        child->right = NULL;
        return child;
    }
    while(child->left != NULL){
        parent = child;
        child = child->left;
    }
    parent->left = NULL;
    return child;
}

void* my_delete(Node child,Node parent, void* key, BST b){
    if(b->compare(key,child->key)<0){
        parent = child;
        child = child->left;
        return my_delete(child,parent,key,b);
    }else if(b->compare(key,child->key)==0){
        Node n = find_delete_successor(child);
        if(n==NULL){
            void* data = child->data;
            if(b->compare(child->key,parent->key)<=0){
                parent->left = child->left;
                child ->left = NULL;
            }else{
                parent->right = child->left;
                child ->left = NULL;
            }
            free(child->key);
            free(child);
            return data;
        }
        void* data = child -> data;
        child->data = n->data;
        child->key = n->key;
        free(n);
        return data;
    }
    parent = child;
    child = child->right;
    return my_delete(child,parent,key,b);
}

void* delete(void* key, BST b){
    Node parent = b->root;
    if(parent == NULL){
        return NULL;
    }
    if(b->compare(key,parent->key)<0){
        Node child = parent -> left;
        return my_delete(child,parent,key,b);
    }else if(b->compare(key,parent->key)==0){
        Node n = find_delete_successor(parent);
        if(n==NULL){
            b->root = parent->left;
            parent->left = NULL;
            void* data = parent ->data;
            free(parent->key);
            free(parent);
            return data;
        }
        void* data = parent -> data;
        free(parent->key);
        parent -> data = n->data;
        parent ->key = n->key;
        free(n);
        return data;
    }
    Node child = parent->right;
    return my_delete(child,parent,key,b);
}


Node getRoot(BST b){
    if(b==NULL){
        return NULL;
    }
    return b->root;
}

void dfs(Node r){
    if(r==NULL){
        return;
    }
    printf("%d ",*(int*)r->key);
    dfs(r->left);
    dfs(r->right);
}
