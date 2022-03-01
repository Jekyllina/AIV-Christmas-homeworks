#define CLOVE_SUITE_NAME LinkedListTest
#include "clove-experimental.h"
#include "LinkedLists.h"

struct string_item *my_linked_list;

CLOVE_SUITE_SETUP() {    
    my_linked_list = NULL;
}

CLOVE_SUITE_TEARDOWN() {
    clear_myelement(&my_linked_list);
}

CLOVE_TEST(ListIsNull)
{
    CLOVE_NULL(my_linked_list);
}

CLOVE_TEST(GetTailFailsWithEmptyList)
{
    struct list_node *node = list_get_tail((struct list_node**)&my_linked_list);

    CLOVE_NULL(node);
}

CLOVE_TEST(GetHeadFailsWithEmptyList)
{
    struct list_node *node = list_pop((struct list_node**)&my_linked_list);

    CLOVE_NULL(node);
}

CLOVE_TEST(StringItemCreationSuccess)
{
    struct string_item *element = string_item_new("Item");
    
    CLOVE_NOT_NULL(element);
}

CLOVE_TEST(AppendSuccess)
{
    struct string_item *element = string_item_new("Item");
    list_append_casting(&my_linked_list, element);

    CLOVE_NOT_NULL(my_linked_list);    
}

CLOVE_TEST(GetTailSuccess)
{
    struct string_item *element = string_item_new("Item");
    struct string_item *element02 = string_item_new("Item02");

    list_append_casting(&my_linked_list, element);
    list_append_casting(&my_linked_list, element02);

    struct string_item *tail = (struct string_item*)list_get_tail((struct list_node**)&my_linked_list);

    CLOVE_STRING_EQ("Item02", tail->string);  
}

CLOVE_TEST(GetHeadSuccess)
{
    struct string_item *element = string_item_new("Item");
    struct string_item *element02 = string_item_new("Item02");

    list_append_casting(&my_linked_list, element);
    list_append_casting(&my_linked_list, element02);

    struct string_item *head = (struct string_item*)list_pop((struct list_node**)&my_linked_list);

    CLOVE_STRING_EQ("Item", head->string);  
}

CLOVE_TEST(Remove)
{
    struct string_item *element = string_item_new("Item");
    struct string_item *element02 = string_item_new("Item02");

    list_append_casting(&my_linked_list, element);
    list_append_casting(&my_linked_list, element02);

    struct string_item *removed = (struct string_item*)list_remove_casting(&my_linked_list, element);

    CLOVE_STRING_EQ("Item", removed->string);      
}

CLOVE_TEST(ReverseList)
{
    struct string_item *element = string_item_new("Item");
    struct string_item *element02 = string_item_new("Item02");
    struct string_item *element03 = string_item_new("Item03");

    list_append_casting(&my_linked_list, element);
    list_append_casting(&my_linked_list, element02);
    list_append_casting(&my_linked_list, element03);
    
    struct string_item *reversed = NULL;   
    struct string_item *string_item_reversed = reverse_linkedlist(&my_linked_list, &reversed);   
    
    struct string_item *reversedTail = (struct string_item*)list_get_tail((struct list_node**)&reversed);
    struct string_item *reversedHead = (struct string_item*)list_pop((struct list_node**)&reversed);
    
    CLOVE_STRING_EQ("Item", reversedTail->string);  
    CLOVE_STRING_EQ("Item03", reversedHead->string); 
}

CLOVE_TEST(ClearList)
{
    struct string_item *item = string_item_new("Item");
    list_append_casting(&my_linked_list, item);    
    
    //clear_myelement(&item);
    //clear_myelement(&my_linked_list);

    //CLOVE_NULL(item);
    //CLOVE_NULL(my_linked_list);
}