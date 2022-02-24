#define CLOVE_SUITE_NAME LinkedListTest
#include "clove-experimental.h"
#include "LinkedLists_refactored.h"

struct string_item *my_linked_list;

CLOVE_SUITE_TEARDOWN() {
    //toDo: clear list
}