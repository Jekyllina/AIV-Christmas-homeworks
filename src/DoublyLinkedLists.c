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

    if(!next_node)
    {
        prev_node->next = NULL; 
    }  
    else
    {
        prev_node->next = next_node;    
        next_node->prev = prev_node;    
    } 
    
    if(!prev_node)
    {       
        doubly_list_pop(head);
        return 0;
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
        item->prev = item_to_add;
        item_to_add->next = item;
        *head = item_to_add;
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

//doesn't work
struct doubly_list_node *doubly_shuffle_list(struct doubly_list_node **head, struct doubly_list_node **arr, int num_of_elements)
{
    srand(time(NULL));
    
    int n;

    for(int i = 0; i < num_of_elements; i++)
    {
        n = rand() % num_of_elements;        
        struct doubly_list_node *item = arr[i];    
        struct doubly_list_node *item2 = arr[n];
        
        struct doubly_list_node *item_prev = item->prev;
        struct doubly_list_node *item_next = item->next;

        struct doubly_list_node *item2_prev = item2->prev;
        struct doubly_list_node *item2_next = item2->next;

        struct doubly_list_node *tmp = item;  
        
        item = item2; 
        
        if(!item2_prev)
        {            
            *head = item;
            item->prev = NULL;
        }
        else
        {            
            item->prev = item2_prev;
        }

        if(!item2_next)
        {           
            item->next  = NULL;
        }
        else
        {            
            item->next = item2_next;
        }


        item2 = tmp;      

        if(!item_prev)
        {            
            *head = item2;
            item2->prev = NULL;
        }
        else
        {            
            item2->prev = item_prev;
        }

        if(!item_next)
        {            
            item2->next  = NULL;
        }
        else
        {            
            item2->next = item_next;
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
        
    doubly_list_remove_casting(&my_linked_list, element02);

    doubly_insert_after_item_cast(&my_linked_list, element03, element06);
    doubly_insert_before_item_cast(&my_linked_list, element01, element07);

    struct doubly_string_item *string_item = my_linked_list;
    
    while(string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct doubly_string_item*)string_item->node.next;
    }    


    //doesn't work
    printf("After Shuffle:\n");
    struct doubly_list_node *arr[6] = {(struct doubly_list_node*)element01, (struct doubly_list_node*)element03, (struct doubly_list_node*)element04, (struct doubly_list_node*)element05, (struct doubly_list_node*)element06, (struct doubly_list_node*)element07};
    struct doubly_string_item *string_item2 = (struct doubly_string_item*)doubly_shuffle_list((struct doubly_list_node **)&my_linked_list, arr, 6);
    // doubly_shuffle_list((struct doubly_list_node **)&my_linked_list, arr, 6);
    // struct doubly_string_item *string_item2 = my_linked_list;

    while(string_item2)
    {
        printf("%s\n", string_item2->string);
        string_item2 = (struct doubly_string_item*)string_item2->node.next;
    }
    
    return 0;
}