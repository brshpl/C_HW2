#ifndef IZ2_ARRAY_H
#define IZ2_ARRAY_H

#include <string.h>

#define DEFAULT_ARR_CAPACITY 10

typedef struct {
    void* data;
    size_t size;
    size_t capacity;
    size_t elem_size;
} array;


// capacity_arr - желаемый размер памяти для array. '0' - default
int array_new(array* new_arr, size_t elem_size, size_t capacity_arr);

size_t array_size(array* arr);

int array_resize(array* arr, size_t new_capacity);

int array_add(array* arr, void* elem);

int array_set(array* arr, size_t index, void* elem);

void* array_get(array* arr, size_t index);

int array_sort(array *arr, int (*comp)(void*, void*));

int array_remove(array* arr);

#endif //IZ2_ARRAY_H
