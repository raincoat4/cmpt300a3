#ifndef _AVLTREE_H_
#define _AVLTREE_H_
typedef struct Node Node;
struct Node 
{ 
    int size; //size
    int start;
    struct Node *left; 
    struct Node *right; 
    int height; 
}; 
int getEnd(struct Node *N);
int getStart(struct Node *N);
int getSize(struct Node *N);
int height(struct Node *N);
int max(int a, int b);
struct Node* newNode(int size);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node* insert(struct Node* node, int size);
struct Node * minValueNode(struct Node* node);
struct Node* deleteNode(struct Node* root, int size);

#endif