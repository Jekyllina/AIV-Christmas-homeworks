#pragma once

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
void clear_list(struct string_item **list);


#define list_node_doubleptr(obj) (struct list_node **)obj
#define list_node_ptr(obj) (struct list_node*)obj
#define list_append_casting(list, item) list_append(list_node_doubleptr(list), list_node_ptr(item))
#define list_remove_casting(list, item) list_remove(list_node_doubleptr(list), list_node_ptr(item));  
