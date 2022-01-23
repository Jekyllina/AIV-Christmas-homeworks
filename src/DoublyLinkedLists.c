#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedLists.h"

struct doubly_list_node *doubly_list_get_tail(struct doubly_list_node **head)
{
    struct doubly_list_node *current_node = *head;  
    struct doubly_list_node *last_node = NULL;
    
    while(current_node)
    {
        last_node = current_node;
        current_node = current_node->next;        
    }

    return last_node;
}

struct doubly_list_node *doubly_list_append(struct doubly_list_node **head, struct doubly_list_node *item)
{
    struct doubly_list_node *tail = doubly_list_get_tail(head);

    if(!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }

    item->prev = tail;
    item->next = NULL;

    return item;
}

struct doubly_list_node *doubly_list_pop(struct doubly_list_node **head)
{
    struct doubly_list_node *current_head = *head;

    if(!current_head)
    {
        return NULL;
    }

    *head = (*head)->next;  
    
    current_head->next = NULL; 

    return current_head;
}

struct doubly_list_node *doubly_list_remove(struct doubly_list_node **head, struct doubly_list_node *item)
{    
    struct doubly_list_node *prev_node = item->prev;
    struct doubly_list_node *next_node = item->next; 

    if(!prev_node)
    {       
        doubly_list_pop(head);
        next_node->prev = NULL;
        return 0;
    } 
    else
    {
        if(!next_node)
        {
            prev_node->next = NULL; 
        }  
        else
        {
            prev_node->next = next_node;    
            next_node->prev = prev_node;    
        }  
    }     

    item->prev = NULL;
    item->next = NULL;    
    
    return item;
}

struct doubly_list_node *doubly_insert_after_item(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *item_to_add)
{
    struct doubly_list_node *next_node = item->next;

    if(!next_node)
    {
        item_to_add->next = NULL;        
    }
    else
    {
        next_node->prev = item_to_add;
        item_to_add->next = next_node;
    }
    
    item_to_add->prev = item;
    item->next = item_to_add;

    return item_to_add;
}

struct doubly_list_node *doubly_insert_before_item(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *item_to_add)
{
    struct doubly_list_node *prev_node = item->prev;

    if(!prev_node)
    {        
        *head = item_to_add;
        item_to_add->prev = NULL;
        item->prev = item_to_add;
        item_to_add->next = item;
    }
    else
    {        
        item_to_add->prev = prev_node;
        prev_node->next = item_to_add;

        item->prev = item_to_add;
        item_to_add->next = item;
    }
    
    return item_to_add;    
}



struct doubly_string_item *doubly_string_item_new(const char *string)
{
    struct doubly_string_item *item = malloc(sizeof(struct doubly_string_item));

    if(!item)
    {
        return NULL;
    }

    item->string = string;

    return item;
}

int main()
{
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

    return 0;
}