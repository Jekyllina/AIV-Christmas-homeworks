#include <stddef.h>
#include <stdlib.h>
#include "LinkedLists.h"

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
        current_node = list_pop(head);        
    } 
    else
    {
        while(current_node->next != item)
        {
            current_node = current_node->next; 

            if(!current_node->next)    
            {
                return NULL;
            }   
        }

        tmp_node = current_node->next;  //node to remove
        current_node->next = tmp_node->next;  //the next of the current node become the next of the one i have to remove
        current_node = tmp_node;  //current node become the node i have to remove
        current_node->next = NULL;    
    }    
    
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

void clear_myelement(struct string_item **item)
{    
    free(*item);    
    *item = NULL;
}

//work in progress

// void clear_mylist(struct string_item **list)
// {   
//     struct list_node **node = (struct list_node **)list_remove_casting(&list, list_get_tail((struct list_node **)list));

//     while(node)
//     {      
//         free(*node);        
//         *node = NULL;

//         struct list_node* tail = (struct list_node*)list_get_tail((struct list_node**)list);

//         if (!tail)
//         {
//             node = NULL;
//         }
//         else
//         {
//             node = (struct list_node **)list_remove((struct list_node**)&list, tail);
//         }
//     }
     
//     free(*list);    
//     *list = NULL;
// }

struct string_item *reverse_linkedlist(struct string_item **list, struct string_item **reversed_list)
{
    struct string_item *item_removed = (struct string_item*)list_remove_casting(&list,list_get_tail((struct list_node **)list));
    
    while(item_removed)
    {               
        list_append((struct list_node **)&reversed_list, (struct list_node *)string_item_new(item_removed->string));
        
        struct list_node *tail = (struct list_node*)list_get_tail((struct list_node **)list);

        if(!tail)
        {
            item_removed = NULL;
        }
        else
        {
            item_removed = (struct string_item*)list_remove((struct list_node**)&list, tail);
        }        
    }
    
    return *reversed_list;
}