#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DoublyLinkedLists.h"

int main()
{
    srand(time(NULL));    

    struct doubly_string_item *my_linked_list = NULL;
    
    struct doubly_string_item *element01 = doubly_string_item_new("Red");
    struct doubly_string_item *element02 = doubly_string_item_new("Yellow");
    struct doubly_string_item *element03 = doubly_string_item_new("Orange");
    struct doubly_string_item *element04 = doubly_string_item_new("Green");
    struct doubly_string_item *element05 = doubly_string_item_new("Blue");

    struct doubly_string_item *element06 = doubly_string_item_new("Black");
    struct doubly_string_item *element07 = doubly_string_item_new("White");

    
    doubly_list_append_casting(&my_linked_list, element01);
    doubly_list_append_casting(&my_linked_list, element02);
    doubly_list_append_casting(&my_linked_list, element03);
    doubly_list_append_casting(&my_linked_list, element04);
    doubly_list_append_casting(&my_linked_list, element05);
        
    doubly_list_remove_casting(&my_linked_list, element01);
   
    doubly_insert_before_item_cast(&my_linked_list, element02, element07);
    doubly_insert_after_item_cast(&my_linked_list, element07, element06);

    struct doubly_string_item *string_item = my_linked_list;    
    
    while(string_item)
    {       
        printf("%s\n", string_item->string);
        string_item = (struct doubly_string_item*)string_item->node.next;
    }


    printf("\n After shuffle\n");
    struct doubly_string_item *string_item_shuffled = (struct doubly_string_item *)doubly_shuffle_list_cast(&my_linked_list, 4);
   
    while(string_item_shuffled)
    {       
        printf("%s\n", string_item_shuffled->string);
        string_item_shuffled = (struct doubly_string_item*)string_item_shuffled->node.next;
    }


    clear_myelement(&element05);
    clear_myelement(&element04);
    clear_myelement(&element03);
    clear_myelement(&element02);    
    clear_myelement(&element06);
    clear_myelement(&element07);
    clear_myelement(&element01);

    my_linked_list = NULL;

    return 0;
}