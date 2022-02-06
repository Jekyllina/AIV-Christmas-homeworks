#include <stdio.h>
#include "dynarray_refactored.h"

int main()
{
    dynarray_t array;
    dynarray_init_type(&array, int, 10);
    
    int a = 100;
    int b = 200;
    int c = 300;
    int d = 50;
    dynarray_append(&array, &a);
    dynarray_append(&array, &b);
    dynarray_append(&array, &c);
    dynarray_append(&array, &c);    
    dynarray_append(&array, &c);   
    dynarray_append(&array, &d);    
    dynarray_append(&array, &b);  

    printf("Dimensione: %d\n", _msize(array.data));
    printf("Number of elements = %llu; Capacity = %zu\n", dynarray_len(&array), array.capacity);

    for (size_t i = 0; i < dynarray_len(&array); i++)
    {
        int value;

        if(!dynarray_get(&array, i, &value))
        {
            printf("[%llu] %d\n", i, value);
        }
    }  

    dynarray_remove(&array, 6);
    dynarray_remove(&array, 2);
    dynarray_remove(&array, 0);

    printf("Dimensione: %d\n", _msize(array.data));
    printf("Number of elements = %llu; Capacity = %zu\n", dynarray_len(&array), array.capacity);

    for (size_t i = 0; i < dynarray_len(&array); i++)
    {
        int value;

        if(!dynarray_get(&array, i, &value))
        {
            printf("[%llu] %d\n", i, value);
        }
    }  

    dynarray_append(&array, &d);    
    dynarray_append(&array, &b); 
    dynarray_append(&array, &a); 

    printf("Dimensione: %d\n", _msize(array.data));
    printf("Number of elements = %llu; Capacity = %zu\n", dynarray_len(&array), array.capacity);

    for (size_t i = 0; i < dynarray_len(&array); i++)
    {
        int value;

        if(!dynarray_get(&array, i, &value))
        {
            printf("[%llu] %d\n", i, value);
        }
    }  

    dynarray_clear(&array);

    return 0;
}