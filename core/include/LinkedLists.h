#pragma once

//Many of these functions have a define with the cast integrated for faster use at the bottom of this document

struct list_node
{    
    struct list_node *next;  
};

struct list_node *list_get_tail(struct list_node **head);
struct list_node *list_append(struct list_node **head, struct list_node *item);
struct list_node *list_pop(struct list_node **head);
struct list_node *list_remove(struct list_node **head, struct list_node *item);


struct string_item
{
    struct list_node node;
    const char *string;
};

struct string_item *string_item_new(const char *string);
void clear_myelement(struct string_item **item);
struct string_item *reverse_linkedlist(struct string_item **list, struct string_item **reversed_list);


#define list_node_doubleptr(obj) (struct list_node **)obj
#define list_node_ptr(obj) (struct list_node*)obj

#define list_get_tail_casting(list) list_get_tail(list_node_doubleptr(list))
#define list_append_casting(list, item) list_append(list_node_doubleptr(list), list_node_ptr(item))
#define list_pop_casting(list) list_pop(list_node_doubleptr(list))
#define list_remove_casting(list, item) list_remove(list_node_doubleptr(list), list_node_ptr(item))  