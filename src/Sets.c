#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;    
}

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

struct set_table *set_table_new(const size_t hashmap_size)  
{
    struct set_table *table = malloc(sizeof(struct set_table));

    if(!table)
    {
        return NULL;
    }

    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));  

    if(!table->nodes)
    {
        free(table);
        return NULL;
    }

    return table;
}

struct set_node *set_insert(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;  

    struct set_node *head = table->nodes[index];  

    if(!head)
    {
        table->nodes[index] = malloc(sizeof(struct set_node));

        if(!table->nodes[index])
        {
            return NULL;
        }

        table->nodes[index]->key = key;
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->prev = NULL;
        table->nodes[index]->next = NULL;

        return table->nodes[index];
    }

    struct set_node *new_item = malloc(sizeof(struct set_node));

    if(!new_item)
    {
        return NULL;
    }

    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = NULL;

    struct set_node *tail = head;

    while(head)
    {
        tail = head;
        head = head->next;
    }

    tail->next = new_item;
    new_item->prev = tail;

    return new_item;
}

struct set_node *set_search(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;  

    struct set_node *node_to_find = table->nodes[index];

    if(!node_to_find)
    {
        return NULL;
    }
    else
    {
        while(node_to_find)
        {
            if(node_to_find->key_len == key_len)
            {
                if(strcmp(node_to_find->key, key) == 0)
                    break;
                else
                    node_to_find = node_to_find->next;
            }
            else
                node_to_find = node_to_find->next;
        }    
    } 
    
    return node_to_find;  
}

struct set_node *set_remove(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;  

    struct set_node *node_to_remove = set_search(table, key, key_len);

    if(!node_to_remove)
    {
        return NULL;
    }
    
    struct set_node *prev_node = node_to_remove->prev;
    struct set_node *next_node = node_to_remove->next;

    if(!prev_node)
    {
        if(next_node)
            table->nodes[index] = next_node;
    }

    if(!next_node)
    {
        prev_node->next = NULL;
    }
    else
    {
        prev_node->next = next_node;    
        next_node->prev = prev_node;    
    }    

    node_to_remove->next = NULL;
    node_to_remove->prev = NULL; 

    return node_to_remove;
}

void print_table(struct set_table *table, const size_t hashmap_size)
{
    for (size_t i = 0; i < hashmap_size; i++)
    {
        struct set_node *head = table->nodes[i]; 
        
        if(!head)
        {
            continue;
        }

        while(head)
        {
            printf("Index: %zu, Key: %s\n", i, head->key);
            head = head->next;
        }
    }    
}

int main()
{
    struct set_table *table = NULL;
    int size = 5;
    table = set_table_new(size);

    struct set_node *element01 = set_insert(table, "hello", 5);
    struct set_node *element02 = set_insert(table, "yellow", 6);
    struct set_node *element03 = set_insert(table, "a", 1);
    struct set_node *element04 = set_insert(table, "ww", 2);
    struct set_node *element05 = set_insert(table, "you", 3);    

    print_table(table, size);

    //search
    char *key = "hello";
    struct set_node *find_node = set_search(table, key, 5);

    if(!find_node)
        printf("Key -%s- not found in the Set\n", key);
    else
        printf("Node found: %s\n", find_node->key);


    char *key2 = "red";
    struct set_node *find_node2 = set_search(table, key2, 3);

    if(!find_node2)
        printf("Key -%s- not found in the Set\n", key2);
    else
        printf("Node found: %s\n", find_node2->key);


    //remove
    char *key_remove = "hello";
    struct set_node *node_to_remove = set_remove(table, key_remove, 5);
    
    if(!node_to_remove)
        printf("Key -%s- not found in the Set\n", key_remove);
    else
        printf("Removed: %s\n", node_to_remove->key);

    print_table(table, size);    
    
    return 0;
}