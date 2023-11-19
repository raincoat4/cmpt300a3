#ifndef _AVLTREE_H_
#define _AVLTREE_H_
#include <stdbool.h>
typedef struct Node Node;
struct treeNode 
{ 
    int size; //size

    int startPoint;
    //int endPoint;
    struct treeNode *left; 
    struct treeNode *right; 
    struct treeNode *count;
    int* start;
    int height;
    bool inUse;

}; 
int getEnd(struct treeNode *N);
int getStart(struct treeNode *N);
int getSize(struct treeNode *N);
int height(struct treeNode *N);
int max(int a, int b);
struct treeNode* newNode(int size,int* start);
struct treeNode *rightRotate(struct treeNode *y);
struct treeNode *leftRotate(struct treeNode *x);
int getBalance(struct treeNode *N);
struct treeNode* insertTree(struct treeNode* node, int size,int* start);
struct treeNode * minValueNode(struct treeNode* node);
struct treeNode* deleteCountNode(struct treeNode* root, int* start);
struct treeNode* deleteNode(struct treeNode* root, int size, int* start);
struct treeNode* findNode(struct treeNode* root, int size, int* start);
struct treeNode* bestFit(struct treeNode* root, int size);
void* helperBF(struct treeNode* root, int size,struct treeNode* bFn);


#endif
