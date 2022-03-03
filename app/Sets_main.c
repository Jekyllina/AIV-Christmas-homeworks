#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Sets.h"

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
    printf("\n--- Search test ---\n");

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
    printf("\n--- Remove test ---\n");

    char *key_remove = "hello";
    struct set_node *node_to_remove = set_remove(table, key_remove, 5);
    
    if(!node_to_remove)
        printf("Key -%s- not found in the Set\n", key_remove);
    else
        printf("Removed: %s\n", node_to_remove->key);

    char *key_remove2 = "dog";
    struct set_node *node_to_remove2 = set_remove(table, key_remove2, 3);
    
    if(!node_to_remove2)
        printf("Key -%s- not found in the Set\n", key_remove2);
    else
        printf("Removed: %s\n", node_to_remove2->key);

    //try to insert a key that already exist  
    struct set_node *element07 = set_insert(table, "ww", 2);
    
    print_table(table, size);    
    
    return 0;
}