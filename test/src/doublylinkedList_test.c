#define CLOVE_SUITE_NAME DoublyLinkedListTest
#include "clove-experimental.h"
#include "DoublyLinkedLists.h"

struct doubly_string_item *my_linked_list;

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
    struct doubly_list_node *node = doubly_list_get_tail((struct doubly_list_node **)&my_linked_list);

    CLOVE_NULL(node);
}

CLOVE_TEST(GetHeadFailsWithEmptyList)
{
    struct doubly_list_node *node = doubly_list_pop((struct doubly_list_node **)&my_linked_list);

    CLOVE_NULL(node);
}

CLOVE_TEST(StringItemCreationSuccess)
{
    struct doubly_string_item *element = doubly_string_item_new("Item");
    
    CLOVE_NOT_NULL(element);
}

CLOVE_TEST(AppendSuccess)
{
    struct doubly_string_item *element01 = doubly_string_item_new("Red");
    doubly_list_append_casting(&my_linked_list, element01);

    CLOVE_NOT_NULL(my_linked_list);
}

CLOVE_TEST(GetTailSuccess)
{
    struct doubly_string_item *element01 = doubly_string_item_new("Yellow");
    struct doubly_string_item *element02 = doubly_string_item_new("Orange");

    doubly_list_append_casting(&my_linked_list, element01);
    doubly_list_append_casting(&my_linked_list, element02);

    struct doubly_string_item *tail = (struct doubly_string_item *)doubly_list_get_tail((struct doubly_list_node **)&my_linked_list);

    CLOVE_STRING_EQ("Orange", tail->string);
}

CLOVE_TEST(GetHeadSuccess)
{
    struct doubly_string_item *element01 = doubly_string_item_new("Green");
    struct doubly_string_item *element02 = doubly_string_item_new("Black");

    doubly_list_append_casting(&my_linked_list, element01);
    doubly_list_append_casting(&my_linked_list, element02);

    struct doubly_string_item *head = (struct doubly_string_item *)doubly_list_pop((struct doubly_list_node **)&my_linked_list);

    CLOVE_STRING_EQ("Green", head->string);
}