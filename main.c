#include <stdio.h>
#include "memory.h"
#include "list.h"


int main(){

    //Making Memory System
    int memSize = 0;
    scanf("%d", &memSize);
    mem_ini(memSize);

    //Making Linked List
    List digList;
    digList = list_ini();

    //scanning in the digits line by line until End Of File (EOF)
    int digit;
    while (scanf("%d", &digit) != EOF){

        // if digit already in list then take note of # of occurrences, then remove and
        // and add with occurrences+1
        if(list_search(digList, digit) != NULL){
            int occurrences = *list_search(digList, digit);
            list_delete(digList, digit);
            list_add(digList, digit, occurrences+1);
        }
        //if digit not yet in list
        else{
            list_add(digList, digit, 1);
        }
    }

    //Printing output
    printf("\nInteger\t\tOccurrences\n");
    list_print(digList);

    //freeing memory of program
    list_free(digList);
    mem_free();
}