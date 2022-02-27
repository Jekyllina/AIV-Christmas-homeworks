#define CLOVE_SUITE_NAME DoublyLinkedListTest
#include "clove-experimental.h"
#include "DoublyLinkedLists.h"
#include <stdio.h>

#define rand() 1

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

CLOVE_TEST(Remove)
{
    struct doubly_string_item *element03 = doubly_string_item_new("White");
    struct doubly_string_item *element04 = doubly_string_item_new("Blue");

    doubly_list_append_casting(&my_linked_list, element03);
    doubly_list_append_casting(&my_linked_list, element04);

    struct doubly_string_item *itemRemoved = (struct doubly_string_item *)doubly_list_remove_casting(&my_linked_list, element04);

    int numElements = take_list_items_count((struct doubly_list_node **)&my_linked_list);

    CLOVE_STRING_EQ("Blue", itemRemoved->string);

    CLOVE_INT_EQ(1, numElements);
}

CLOVE_TEST(InsertAfterItem)
{
    struct doubly_string_item *element05 = doubly_string_item_new("Red");
    struct doubly_string_item *element06 = doubly_string_item_new("Black");

    doubly_list_append_casting(&my_linked_list, element05);
    doubly_list_append_casting(&my_linked_list, element06);

    struct doubly_string_item *element07 = doubly_string_item_new("Yellow");

    doubly_insert_after_item_cast(&my_linked_list, element05, element07);

    int numElements = take_list_items_count((struct doubly_list_node **)&my_linked_list);

    CLOVE_PTR_EQ(element07, element05->node.next);
    CLOVE_PTR_EQ(element07, element06->node.prev);
    CLOVE_PTR_EQ(element06, element07->node.next);

    CLOVE_INT_EQ(3, numElements);
}

CLOVE_TEST(InsertBeforeItem)
{
    struct doubly_string_item *element08 = doubly_string_item_new("Green");
    struct doubly_string_item *element09 = doubly_string_item_new("White");

    doubly_list_append_casting(&my_linked_list, element08);
    doubly_list_append_casting(&my_linked_list, element09);

    struct doubly_string_item *element10 = doubly_string_item_new("Orange");

    doubly_insert_before_item_cast(&my_linked_list, element08, element10);

    int numElements = take_list_items_count((struct doubly_list_node **)&my_linked_list);

    CLOVE_PTR_EQ(element10, element08->node.prev);
    CLOVE_PTR_EQ(element08, element10->node.next);

    CLOVE_INT_EQ(3, numElements);
}

CLOVE_TEST(TakeAnItem)
{
    struct doubly_string_item *element01 = doubly_string_item_new("Purple");
    struct doubly_string_item *element02 = doubly_string_item_new("Blue");

    doubly_list_append_casting(&my_linked_list, element01);
    doubly_list_append_casting(&my_linked_list, element02);

    struct doubly_string_item *item = (struct doubly_string_item *)take_list_item((struct doubly_list_node **)&my_linked_list, 1);

    CLOVE_STRING_EQ("Blue", item->string);
}

CLOVE_TEST(ItemsCount)
{
    struct doubly_string_item *element01 = doubly_string_item_new("Black");
    struct doubly_string_item *element02 = doubly_string_item_new("Red");
    struct doubly_string_item *element03 = doubly_string_item_new("Yellow");

    doubly_list_append_casting(&my_linked_list, element01);
    doubly_list_append_casting(&my_linked_list, element02);
    doubly_list_append_casting(&my_linked_list, element03);

    int numElements = take_list_items_count((struct doubly_list_node **)&my_linked_list);

    CLOVE_INT_EQ(3, numElements);
}

CLOVE_TEST(ShuffleList)
{    
    struct doubly_string_item *element01 = doubly_string_item_new("Grey");
    struct doubly_string_item *element02 = doubly_string_item_new("Yellow");
    struct doubly_string_item *element03 = doubly_string_item_new("Blue");

    doubly_list_append_casting(&my_linked_list, element01);
    doubly_list_append_casting(&my_linked_list, element02);
    doubly_list_append_casting(&my_linked_list, element03);

    int numElements = take_list_items_count((struct doubly_list_node **)&my_linked_list);

    struct doubly_string_item *shuffledList = (struct doubly_string_item *)doubly_shuffle_list_cast(&my_linked_list, 2);

    int numElementsShuffledList = take_list_items_count((struct doubly_list_node **)&shuffledList);

    struct doubly_string_item *item0 = (struct doubly_string_item *)take_list_item((struct doubly_list_node **)&shuffledList, 0);
    struct doubly_string_item *item1 = (struct doubly_string_item *)take_list_item((struct doubly_list_node **)&shuffledList, 1);
    struct doubly_string_item *item2 = (struct doubly_string_item *)take_list_item((struct doubly_list_node **)&shuffledList, 2);
    
    CLOVE_NOT_NULL(shuffledList);
    CLOVE_INT_EQ(numElements, numElementsShuffledList);    

    CLOVE_STRING_EQ(item0->string, element01->string);
    CLOVE_STRING_EQ(item1->string, element03->string);
    CLOVE_STRING_EQ(item2->string, element02->string);
}

//to do: clear