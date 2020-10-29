#include <stdlib.h>
#include "../include/IZ2/array.h"

#define ERROR -1
#define OK 0

int array_new(array* new_arr, size_t elem_size, size_t capacity_arr) {
    if (new_arr == NULL || elem_size == 0)
        return ERROR;
    if (capacity_arr == 0)
        capacity_arr = DEFAULT_ARR_CAPACITY;
    if ((new_arr->data = malloc(capacity_arr * elem_size)) == NULL)
        return ERROR;
    new_arr->size = 0;
    new_arr->capacity = capacity_arr;
    new_arr->elem_size = elem_size;
    return OK;
}

size_t array_size(array* arr) {
    if (arr == NULL)
        return 0;
    return arr->size;
}

int array_resize(array* arr, size_t new_capacity) {
    if (arr == NULL)
        return ERROR;
    arr->capacity = new_capacity;
    arr->data = realloc(arr->data, new_capacity * arr->elem_size);
    if (arr->data == NULL) {
        return ERROR;
    }
    return OK;
}

int array_add(array* arr, void* elem) {
    if (arr == NULL || elem == NULL)
        return ERROR;
    if (arr->size >= arr->capacity)
        if (array_resize(arr, arr->size * 2) == ERROR)
            return ERROR;
//    if ((arr->data[arr->size] = malloc(arr->elem_size)) == NULL)
//        return ERROR;
    void* mem = memcpy(arr->data + arr->elem_size * arr->size, elem, arr->elem_size);
    if (mem == NULL)
        return ERROR;
    ++arr->size;
    return OK;
}

int array_set(array* arr, size_t index, void* elem) {
    if (arr == NULL || index >= arr->size || elem == NULL)
        return ERROR;
    void* dest = arr->data + index * arr->elem_size;
    if (memcpy(dest, elem, sizeof(arr->elem_size)) == NULL)
        return ERROR;
    return OK;
}

void* array_get(array* arr, size_t index) {
    if (arr == NULL || index >= arr->size)
        return NULL;
    return arr->data + index * arr->elem_size;
}

int array_sort(array *arr, int (*comp)(void*, void*)) {
    if (arr == NULL || comp == NULL)
        return ERROR;
    for (int start_ind = 0; start_ind < array_size(arr); ++start_ind) {
        int best_ind = start_ind;
        for (int cur_ind = start_ind + 1; cur_ind < array_size(arr); ++cur_ind)
        {
            if (comp(array_get(arr, best_ind), array_get(arr, cur_ind)))
                best_ind = cur_ind;
        }
        void* tmp = malloc(arr->elem_size);
        memcpy(tmp, array_get(arr, start_ind), arr->elem_size);
        memcpy(array_get(arr, start_ind), array_get(arr, best_ind), arr->elem_size);
        memcpy(array_get(arr, best_ind), tmp, arr->elem_size);
        free(tmp);
    }
    return OK;
}

int array_remove(array* arr) {
    if (arr == NULL)
        return ERROR;
    arr->size = 0;
    free(arr->data);
    arr->capacity = 0;
    return OK;
}