#define CLOVE_SUITE_NAME DynarrayTest
#include "clove-experimental.h"
#include "dynarray_refactored.h"

dynarray_t array;

CLOVE_SUITE_SETUP() {    
    dynarray_init_type(&array, int, 10);
}

CLOVE_SUITE_TEARDOWN() {
    dynarray_clear(&array);
}

CLOVE_TEST(CreateArray) {
    CLOVE_NOT_NULL(&array);
}

CLOVE_TEST(ArrayIsEmpty) {
    int elements = dynarray_len(&array);
    CLOVE_INT_EQ(0, elements);
}

CLOVE_TEST(ClearedArray) {
    dynarray_clear(&array);
    CLOVE_NULL(array.data);
}

CLOVE_TEST(AppendSuccess) {
    int a = 10;
    dynarray_append(&array, &a);

    CLOVE_NOT_NULL(&array);
}

CLOVE_TEST(VerifyGetLen)
{
    int a = 10;
    dynarray_append(&array, &a);

    int elements = dynarray_len(&array);
    CLOVE_INT_EQ(1, elements);
}

CLOVE_TEST(VerifyAddedElementWithGet)
{
    int a = 10;
    dynarray_append(&array, &a);

    int value;
    dynarray_get(&array, 0, &value);
    CLOVE_INT_EQ(10, value);
}

CLOVE_TEST(RemoveElement)
{
    int a = 10;
    int b = 30;
    int c = 50;
    dynarray_append(&array, &a);
    dynarray_append(&array, &b);
    dynarray_append(&array, &c);

    dynarray_remove(&array, 1);

    int elements = dynarray_len(&array);
    CLOVE_INT_EQ(2, elements);
}

CLOVE_TEST(RemoveElementAndVerifyIfOthersAreStillCorrect)
{
    int a = 10;
    int b = 30;
    int c = 50;
    dynarray_append(&array, &a);
    dynarray_append(&array, &b);
    dynarray_append(&array, &c);

    dynarray_remove(&array, 1);

    int value;
    dynarray_get(&array, 0, &value);
    CLOVE_INT_EQ(10, value);

    int value2;
    dynarray_get(&array, 1, &value2);
    CLOVE_INT_EQ(50, value2);
}