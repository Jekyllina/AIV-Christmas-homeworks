#include <stdio.h>
#include "LinkedLists.h"

int main()
{
    struct string_item *my_linked_list = NULL;
    
    struct string_item *element01 = string_item_new("Hello World");
    struct string_item *element02 = string_item_new("Test001");
    struct string_item *element03 = string_item_new("Test002");
    struct string_item *element04 = string_item_new("Hello");
    struct string_item *element05 = string_item_new("Tail");
    
    list_append_casting(&my_linked_list, element01);
    list_append_casting(&my_linked_list, element02);
    list_append_casting(&my_linked_list, element03);
    list_append_casting(&my_linked_list, element04);
    list_append_casting(&my_linked_list, element05);
        
    list_remove_casting(&my_linked_list, element02);    
    
    
    struct string_item *string_item = my_linked_list;  

    while(string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item*)string_item->node.next;
    }
        
    
    printf("\n");   
    
    struct string_item *reversed = NULL;    
    struct string_item *string_item_reversed = reverse_linkedlist(&my_linked_list, &reversed);    
    printf("Reversed: \n");
    
    while(string_item_reversed)
    {
        printf("%s\n", string_item_reversed->string);
        string_item_reversed = (struct string_item*)string_item_reversed->node.next;
    }
    
    clear_myelement(&element05); 
    clear_myelement(&element04);       
    clear_myelement(&element03);       
    clear_myelement(&element01);       
    clear_myelement(&element02);    
    
    my_linked_list = NULL;  
    
    return 0;
}