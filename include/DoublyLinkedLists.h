#pragma once

struct doubly_list_node
{
    struct doubly_list_node *prev;
    struct doubly_list_node *next;
};

struct doubly_list_node *doubly_list_get_tail(struct doubly_list_node **head);
struct doubly_list_node *doubly_list_append(struct doubly_list_node **head, struct doubly_list_node *item);
struct doubly_list_node *doubly_list_pop(struct doubly_list_node **head);
struct doubly_list_node *doubly_list_remove(struct doubly_list_node **head, struct doubly_list_node *item);
struct doubly_list_node *doubly_insert_after_item(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *item_to_add);
struct doubly_list_node *doubly_insert_before_item(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *item_to_add);


struct doubly_string_item
{
    struct doubly_list_node node;
    const char *string;
};

struct doubly_string_item *doubly_string_item_new(const char *string);

#define doubly_list_node_doubleptr(obj) (struct doubly_list_node **)obj
#define doubly_list_node_ptr(obj) (struct doubly_list_node*)obj
#define doubly_list_append_casting(list, item) doubly_list_append(doubly_list_node_doubleptr(list), doubly_list_node_ptr(item))    
#define doubly_list_remove_casting(list, item) doubly_list_remove(doubly_list_node_doubleptr(list), doubly_list_node_ptr(item));    
#define doubly_insert_after_item_cast(list, item, item_to_add) doubly_insert_after_item(doubly_list_node_doubleptr(list), doubly_list_node_ptr(item), doubly_list_node_ptr(item_to_add));        
#define doubly_insert_before_item_cast(list, item, item_to_add) doubly_insert_before_item(doubly_list_node_doubleptr(list), doubly_list_node_ptr(item), doubly_list_node_ptr(item_to_add));