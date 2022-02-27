#include <stddef.h>
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

        item->prev = NULL;
        item->next = NULL;      
    }   

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

struct doubly_list_node *take_list_item(struct doubly_list_node **head, int element_index)
{
    int counter = 0;

    struct doubly_list_node *current_node = *head;  
    struct doubly_list_node *node_to_take = NULL;
    
    while(current_node)
    {
        node_to_take = current_node;
        current_node = current_node->next;  

        if(counter == element_index)   
            break;

        counter++;   
    }    

    return node_to_take;
}

int take_list_items_count(struct doubly_list_node **head)
{
    int counter = 0;

    struct doubly_list_node *current_node = *head;  
    struct doubly_list_node *node_to_take = NULL;
    
    while(current_node)
    {
        node_to_take = current_node;
        current_node = current_node->next;         
        counter++;   
    }    

    return counter;
}

struct doubly_list_node *shuffle_doublylist(struct doubly_list_node **head, int number_of_shuffles)
{
    int randomN = 0;
    int randomN2 = 0;

    int elements = take_list_items_count(head);
    
    for (int i = 0; i < number_of_shuffles; i++)
    {
        randomN = rand() % elements;
        
        randomN2 = rand() % (elements-1);
        
        if(i%2 == 0)
        {            
            struct doubly_list_node *node = take_list_item(head, randomN);
            struct doubly_list_node *node_removed = doubly_list_remove(head, node);
            struct doubly_list_node *node2 = take_list_item(head, randomN2);
            
            doubly_insert_before_item(head, node2, node_removed);            
        }
        else
        {            
            struct doubly_list_node *node = take_list_item(head, randomN);
            struct doubly_list_node *node_removed = doubly_list_remove(head, node);
            struct doubly_list_node *node2 = take_list_item(head, randomN2);
            
            doubly_insert_after_item(head, node2, node_removed);            
        }
    }

    return *head;    
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

void clear_myelement(struct doubly_string_item **item)
{    
    free(*item);
    *item = NULL;
}