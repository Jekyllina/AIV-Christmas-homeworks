#pragma once

size_t djb33x_hash(const char *key, const size_t keylen);

struct set_node
{
    const char *key;
    size_t key_len;
    struct set_node *prev;
    struct set_node *next;  
};

struct set_table
{
    struct set_node **nodes; 
    size_t hashmap_size;
};

struct set_table *set_table_new(const size_t hashmap_size);
struct set_node *set_search(struct set_table *table, const char *key, const size_t key_len);
struct set_node *set_insert(struct set_table *table, const char *key, const size_t key_len);
struct set_node *set_remove(struct set_table *table, const char *key, const size_t key_len);
void print_table(struct set_table *table, const size_t hashmap_size);