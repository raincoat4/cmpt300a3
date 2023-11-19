#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "avltree.h"
#include "hashmap.h"
//have a variable that keeps track of the largest gap between memory
//so that you can check in O(1) time if there the job can fit
//i think we can use a stack for this but im still thinking about how to do it
//its hard to know how to get the largest gap between memory without actually going
//through every time a job is freed to calculate the gaps but im pretty sure its 
//possible to do it without


void* largeBlock;
int largeBlockSize;
struct hashMap *startMap;
struct hashMap *endMap;
struct treeNode *free_root;

void mem_init(size_t size){
    //initialize memory block
    free_root=NULL;
    largeBlock = (void*)malloc(size);
    largeBlockSize=size;
    if(largeBlock == NULL){
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }


    //initialize startpoint hashmap
    struct hashMap* startMap = (struct hashMap*)malloc(sizeof(struct hashMap));
	initializeHashMap(startMap);

    //initialize endpoint hashmap
    struct hashMap* endMap = (struct hashMap*)malloc(sizeof(struct hashMap));
	initializeHashMap(endMap);

    
}
//asdasd

void *my_free(void *ptr){
    struct treeNode* memToFree = ptr;
    //this is startpoint of the node we want to free
    int* thisStartPoint = memToFree->startPoint;
    int* nextStartPoint = memToFree->startPoint + memToFree->size + 1;
    //might need to assign to void ptr first
    struct treeNode* nodeInFront = search(startMap, nextStartPoint);
    //nodeInFront is never NULL since the hashmap always has nodes wheher the space is being used or not
    if(!nodeInFront){
        printf("node in front is null");
        return;
    }
    //this will either be just the size of the node we wanna free or the size of the node we wanna free + node in front
    int sizeOfNode;
    //if nodeInFront is free memory
    if(!(nodeInFront->inUse)){
        sizeOfNode = memToFree->size + nodeInFront->size;
        //remove the node in front from all structures because its gonna combine with the one we are pointing to
        //delete from hashmap first because the tree is gonna free the memory
        delete(startMap, nextStartPoint);
        //might be size - 1 idk
        int* nextEndPoint = *nextStartPoint + nodeInFront->size;
        delete(endMap, nextEndPoint);
        free_root = deleteNode(free_root, nodeInFront->size);    
    }
    else{
        //if nodeInFront is being used then just add the node to free to the tree
        sizeOfNode = memToFree->size;
    }
    free_root = insertTree(free_root, sizeOfNode, thisStartPoint);
}
    

void* my_malloc(size_t size){
    
    if(!free_root){
        //if the tree is empty get the block of memory
        //largeBlock ptr will be start of the memory endpoint will be ptr+size
        if(size>largeBlockSize){
            perror("Not enough memory");
            exit(EXIT_FAILURE);
        }
        void* a;
        a=largeBlock;
        
        a=a+(int)size+1;
        free_root=insertTree(free_root,largeBlockSize-size, a);
        
        return largeBlock;
    }
    struct treeNode* ret = bestFit(free_root, size);
    if(!ret){
        perror("Not enough T memory");
        exit(EXIT_FAILURE);
        return NULL;
    }else{
        void* a;
        a=ret->start;
        void* b;
        b=a+(int)size+1;
        
        free_root=insertTree(free_root, (ret->size)-size, b);
        deleteNode(free_root, ret->size,a);
        //insertMap(startMap, a, free_root);
        //insertMap(endMap, b, free_root);
        return a;
    }
}

void preOrder(struct treeNode *root)
{
    if(root != NULL)
    {
        printf("%d ", root->size);
        preOrder(root->left);
        preOrder(root->right);
    }
    
}

int main(){
    mem_init(100);
    void* p = my_malloc(25);
    preOrder(free_root);
    printf("\n");
    void* n=my_malloc(25);
    printf("%p\n", p);
    
    printf("%p\n", p+25+1);
    printf("%p\n", n);
    preOrder(free_root);
    printf("\n");
    void* m=my_malloc(30);
    
    printf("%p\n", m);
    printf("%p\n", p+70+2);
    preOrder(free_root);
    printf("\n");
}
