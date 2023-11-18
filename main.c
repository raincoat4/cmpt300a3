#include <stdlib.h>
#include <stdio.h>
#include "avltree.h"
//have a variable that keeps track of the largest gap between memory
//so that you can check in O(1) time if there the job can fit
//i think we can use a stack for this but im still thinking about how to do it
//its hard to know how to get the largest gap between memory without actually going
//through every time a job is freed to calculate the gaps but im pretty sure its 
//possible to do it without
struct Node jobs_root;

void* largeBlock;
int largeBlockSize;
void* mem_init(size_t size){
    void* largeBlock = malloc(size);
    largeBlockSize=size;
    if(largeBlock == NULL){
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return largeBlock;
}
void* my_malloc(size_t size){
    if(!avl_root){
        //if the tree is empty get the block of memory
        //largeBlock ptr will be start of the memory endpoint will be ptr+size
        jobs_root=insert(jobs_root,largeBlockSize-size, (uintptr_t)largeBlock+size);
        return (uintptr_t)largeBlock;
    }
    struct Node* ret = bestFit(jobs_root, size);
    if(!ret){
        perror("Not enough memory");
        exit(EXIT_FAILURE);
        return NULL;
    }else{
        deleteNode(jobs_root, ret->size);
        jobs_root=insert(jobs_root, (ret->size)-size, (ret->start)+size);
        return ret->start;
    }
}

int main(){
    
}
