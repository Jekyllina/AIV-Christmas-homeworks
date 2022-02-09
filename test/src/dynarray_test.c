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