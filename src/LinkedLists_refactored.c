#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "LinkedLists_refactored.h"

struct list_node *list_get_tail(struct list_node **head)
{  
    struct list_node *current_node = *head;  
    struct list_node *last_node = NULL;

    while(current_node)
    {
        last_node = current_node;
        current_node = current_node->next;        
    }

    return last_node;
}

struct list_node *list_append(struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail(head);

    if(!tail)
    {
        *head = item;  
    }
    else
    {
        tail->next = item;
    }

    item->next = NULL;  
    
    return item;
}

struct list_node *list_pop(struct list_node **head)
{  
    struct list_node *current_head = *head;

    if(!current_head)
    {
        return NULL;
    }

    *head = (*head)->next;  
    current_head->next = NULL; 

    return current_head;
}

struct list_node *list_remove(struct list_node **head, struct list_node *item)
{
    struct list_node *current_node = *head;
    struct list_node *tmp_node = NULL;
    
    if(!current_node)
    {
        return NULL;
    }

    if(current_node == item)
    {       
        list_pop(head);
        return 0;
    }  

    while(current_node->next != item)
    {
        current_node = current_node->next;        
    }

    tmp_node = current_node->next;
    current_node->next = tmp_node->next;
    current_node = tmp_node;
    current_node->next = NULL;
    
    return current_node;
}




struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));

    if(!item)
    {
        return NULL;
    }

    item->string = string;

    return item;
}


int main()
{
    struct string_item *my_linked_list = NULL;
    
    struct string_item *element01 = string_item_new("Hello World");
    struct string_item *element02 = string_item_new("Test001");
    struct string_item *element03 = string_item_new("Test002");
    struct string_item *element04 = string_item_new("Hello");
    struct string_item *element05 = string_item_new("Tail");
    
    list_append_casting(&my_linked_list, list_node_ptr(element01));
    list_append_casting(&my_linked_list, list_node_ptr(element02));
    list_append_casting(&my_linked_list, list_node_ptr(element03));
    list_append_casting(&my_linked_list, list_node_ptr(element04));
    list_append_casting(&my_linked_list, list_node_ptr(element05));
        
    list_remove((struct list_node **)&my_linked_list, (struct list_node*)element02);
    
    struct string_item *string_item = my_linked_list;
    
    while(string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item*)string_item->node.next;
    }

    return 0;
}