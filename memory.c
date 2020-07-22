#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

static unsigned char *memory;
static BStree bst;

// Initialize a char array containing size elements and initialize a BST
void mem_ini(unsigned int size) {
	memory = (unsigned char *) malloc(size);
	bst = bstree_ini(size/5); // size/5 is large enough
	bstree_insert(bst, 0, size);
}

//Allocates size bytes by using BST of free blocks and modifies the BST of free blocks
void *simu_malloc(unsigned int size) {
    //creating local variables
    int freeKey;
    int freeBlock;

    //finding the index of free memory based on the size given
    freeKey = *bstree_data_search(bst, size+4);
    freeBlock = *bstree_search(bst, freeKey);

    //removing the free block from the BST
    bstree_delete(bst, freeKey);

    //setting first 4 bytes of memory block to size int with a pointer
    unsigned char *memInt = &memory[freeKey];
    *memInt = size;

    //inserting remaining of free block into BST if any remaining memory exists
    if(freeBlock-(size+4) > 0){
        bstree_insert(bst, freeKey+4+size, freeBlock-(size+4));
    }

    return &memory[freeKey+4];
}

// Puts the allocated memory given to be free memory
// Adds memory with index (key) and size (data) back into the bst of free blocks.
void simu_free(void *ptr) {
    unsigned char *currPtr = (unsigned char *) ptr;
    int index = currPtr - memory;

    Key newIndex = index-4;
    Data newSize = 4 + *(currPtr-4);

    //inserting the above values into the BST
    bstree_insert(bst, newIndex, newSize);
}

// Prints the BST of free memory
void mem_print(void) {
    bstree_traversal(bst);
}

// Frees all memory and the BST
void mem_free(void) {
    free(memory);
    bstree_free(bst);
}

