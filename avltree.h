#ifndef _AVLTREE_H_
#define _AVLTREE_H_

struct Node 
{ 
    int key; 
    struct Node *left; 
    struct Node *right; 
    int height; 
}; 
int height(struct Node *N);
int max(int a, int b);
struct Node* newNode(int key);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node* insert(struct Node* node, int key);
struct Node * minValueNode(struct Node* node);
struct Node* deleteNode(struct Node* root, int key);
#endif