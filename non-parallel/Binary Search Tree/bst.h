#ifndef BST_H
#define BST_H
typedef struct node* Node;
struct node;


Node new_Node(void* key, void* data);

typedef int (*Compare)(void* key1,void* key2);
struct bst;

typedef struct bst* BST;


BST new_BST(Compare c);

void* my_get(void* key, Node root, BST b);

void* get(void* key,BST b);

void my_insert(Node n, Node root,BST b);
void insert(void* key, void*data, BST b);

Node find_delete_successor(Node root);

void* my_delete(Node child,Node parent, void* key, BST b);

void* delete(void* key, BST b);

Node getRoot(BST b);


void dfs(Node r);
#endif