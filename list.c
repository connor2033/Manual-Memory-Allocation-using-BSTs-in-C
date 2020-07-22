#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "memory.h"

// initializes a linked list with a head
List list_ini(void) {
	List_node *head = (List_node *) simu_malloc( sizeof(List_node) );
	head->next = NULL;
	return head;
}

// Returns the address of given keys associated data if it is in the list,
// otherwise return NULL
Data *list_search(List list, Key key) {
    List_node *curr = list->next;
    while (curr != NULL){
        if(curr->key == key) return &(curr->data);
        curr = curr->next;
    }
    return NULL;
}

// adds node with given Key and Data to the Front of the list
void list_add(List list, Key key, Data data) {
    if(list_search(list, key) == NULL){

        // creating a new node, setting key and data, pointing it to the first non head node,
        // and then pointing head to it.
        List_node *newNode= (List_node *) simu_malloc( sizeof(List_node) );
        newNode->key = key;
        newNode->data = data;
        newNode->next = list->next;
        list->next = newNode;
    }
    else return;
}

// Deletes the node with the given key if it exists in the list
void list_delete(List list, Key key) {

    //if key exists in list
    if(list_search(list, key) != NULL){

        //getting node with key and predecessor node
        List_node *currNode = list->next;
        List_node *preNode = list->next;
        while (currNode->key != key){
            preNode = currNode;
            currNode = currNode->next;
        }

        //if it's the last node
        if(currNode->next == NULL){
            preNode->next = NULL;
            simu_free(currNode);
        }
        //if it's first node
        else if(currNode == list->next){
            list->next = currNode->next;
            simu_free(currNode);
        }
        //if it's middle of list
        else{
            preNode->next = currNode->next;
            simu_free(currNode);
        }
    }
    else return;
}

// Prints the key and data from each node in the list
void list_print(List list) {
    List_node *curr = list->next;
    while (curr != NULL){
        printf("%d\t\t%d \n", curr->key, curr->data);
        curr = curr->next;
    }
}

//Frees the linked list
void list_free(List list) {
    simu_free(list);
}