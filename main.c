#include <stdlib.h>
#include <stdio.h>

//have a variable that keeps track of the largest gap between memory
//so that you can check in O(1) time if there the job can fit
//i think we can use a stack for this but im still thinking about how to do it
//its hard to know how to get the largest gap between memory without actually going
//through every time a job is freed to calculate the gaps but im pretty sure its 
//possible to do it without

void* mem_init(size_t size){
    void* largeBlock = malloc(size);
    if(largeBlock == NULL){
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return largeBlock;
}

int main(){
    
}
