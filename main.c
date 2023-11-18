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

void *my_free(size_t size){

}
    

void* my_malloc(size_t size){
    
    if(!free_root){
        //if the tree is empty get the block of memory
        //largeBlock ptr will be start of the memory endpoint will be ptr+size
        if(size>largeBlockSize){
            perror("Not enough memory");
            exit(EXIT_FAILURE);
        }
        int* a;
        a=largeBlock;
        
        a=a+(int)size;
        free_root=insertTree(free_root,largeBlockSize-size, a);
        
        return largeBlock;
    }
    struct treeNode* ret = bestFit(free_root, size);
    if(!ret){
        perror("Not enough T memory");
        exit(EXIT_FAILURE);
        return NULL;
    }else{
        int* a;
        a=ret->start;
        int* b;
        b=a+size;
        
        free_root=insertTree(free_root, (ret->size)-size, b);
        deleteNode(free_root, ret->size);
        
       
        
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
    int* p = my_malloc(50);
    int* n=my_malloc(20);
    printf("%p\n", p);
    
    printf("%p\n", p+50);
    printf("%p\n", n);
    preOrder(free_root);
    printf("\n");
    int* m=my_malloc(30);
   
    printf("%p\n", m);
    printf("%p\n", p+70);
    preOrder(free_root);
    printf("\n");
}
