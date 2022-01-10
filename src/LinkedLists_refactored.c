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

        if(!current_node->next)    
        {
            return NULL;
        }   
    }

    tmp_node = current_node->next;  //node to remove
    current_node->next = tmp_node->next;  //the next of the current node is the next of the one i have to remove
    current_node = tmp_node;  //current node become the node i have to remove
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

struct string_item *reverse_list (struct string_item **list, struct string_item **reversed_list)
{
    struct string_item *item_removed = (struct string_item*)list_remove((struct list_node**)&list,(struct list_node*)list_get_tail(list));
    
    while(item_removed)
    {               
        list_append((struct list_node **)&reversed_list, (struct list_node *)string_item_new(item_removed->string));
        
        struct list_node *tail = (struct list_node*)list_get_tail(list);

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

    printf("\n");


    struct string_item *reversed = NULL;    
    struct string_item *string_item_reversed = reverse_list(&my_linked_list, &reversed);    
    printf("Reversed: \n");
    
    while(string_item_reversed)
    {
        printf("%s\n", string_item_reversed->string);
        string_item_reversed = (struct string_item*)string_item_reversed->node.next;
    }

    return 0;
}