#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "dynarray_refactored.h"

int dynarray_init(dynarray_t *array, const size_t size_of_element, size_t capacity)
{
    array -> number_of_elements = 0;  
    array -> size_of_element = size_of_element;
    array->capacity = capacity;  
    array -> data = malloc(capacity * size_of_element);  
    array ->tmp_data = malloc(size_of_element);
        
    if(!array->tmp_data)
    {
        return -1;
    }

    return 0;
}

void dynarray_clear(dynarray_t *array)
{
    array -> number_of_elements = 0;
    free(array -> data);
    array -> data = NULL;  
    free(array->tmp_data);
    array->tmp_data = NULL;
}

int dynarray_append(dynarray_t *array, const void *value)
{
    const size_t new_size = array -> number_of_elements + 1; 

    size_t offset = array->number_of_elements * array->size_of_element;  
    array->number_of_elements = new_size;

    if(array->number_of_elements > array->capacity)
    {
        uint8_t *new_ptr = realloc(array -> data, new_size * array -> size_of_element);
        size_t new_capacity = array->capacity + 1;

        if(!new_ptr)  
        {
            return -1;
        }

        array->data = new_ptr;
        array->capacity = new_capacity;        
    }     

    memcpy(array->data + offset, value, array->size_of_element);

    return 0;  
}

size_t dynarray_len(const dynarray_t *array) 
{
    return array->number_of_elements;
}

int dynarray_get(const dynarray_t *array, const size_t index, void *value)  
{   
    if(index >= array->number_of_elements)
    {
        return -1;
    }
   
    const size_t offset = index * array->size_of_element;
    memcpy(value, array->data + offset, array->size_of_element);
    return 0;
}

int dynarray_remove(dynarray_t *array, const size_t index)
{
    if(index >= array->number_of_elements)
    {
        return -1;
    }

    const size_t offset = index * array->size_of_element;
    
    if(index < array->number_of_elements - 1)
    {        
        memcpy(array->tmp_data, array->data + offset, array->size_of_element);
    
        memmove(array->data + offset, array->data + offset + array->size_of_element, (array->number_of_elements - index) * array->size_of_element);
    }
    else
    {
        array->data[index] = 0;
    }

    const size_t new_size = array -> number_of_elements - 1; 
    array->number_of_elements = new_size;   

    if((array->capacity - array->number_of_elements) > 5)  //if there are 5+ free spaces, resize the allocated memory to array->number_of_elements + 2
    {
        uint8_t *new_ptr = realloc(array -> data, (new_size + 2) * array -> size_of_element);  

        if(!new_ptr)  
        {
            if(index < array->number_of_elements - 1)
            {                
                memmove(array->data + offset + array->size_of_element, array->data + offset, (array->number_of_elements - index) * array->size_of_element);
                memcpy(array->data + offset, array->tmp_data, array->size_of_element);                        
            }

            return -1;
        }
        
        array->data = new_ptr;
        array->capacity = new_size + 2;
    }    
     
    return 0;
}

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

    printf("Dimensione: %zu\n", _msize(array.data));
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

    printf("Dimensione: %zu\n", _msize(array.data));
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

    printf("Dimensione: %zu\n", _msize(array.data));
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