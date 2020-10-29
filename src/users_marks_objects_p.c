//
// Created by brshpl on 29.10.2020.

//

#include <stdlib.h>
#include "IZ2/users_marks_objects_p.h"

int add_to_top_n_p(array* top_n_arr, struct Object* obj, size_t begin, size_t end, size_t arr_size) {
    if (top_n_arr == NULL || obj == NULL)
        return -1;
    if (arr_size == 0) {
        array_set(top_n_arr, begin, &obj);
        return OK;
    }
    if (arr_size < end - begin) {
        array_set(top_n_arr, begin + arr_size, &obj);
        if (array_sort(top_n_arr, comp_objects) == -1)
            return -1;
        return OK;
    }
    struct Object** arr_obj = array_get(top_n_arr, array_size(top_n_arr) - 1);
    if ((*arr_obj)->average_mark < obj->average_mark) {
        array_set(top_n_arr, array_size(top_n_arr) - 1, &obj);
        array_sort(top_n_arr, comp_objects);
    }
    return OK;
}

int top_n_for_user_fork(array* marks, array* objects, struct User* user,
        array* shared_arr, size_t capacity, size_t begin, size_t end, int num_pid) {
    if (marks == NULL || user == NULL || shared_arr == NULL || shared_arr->capacity == 0)
        return -1;
    size_t size_inside_arr = 0;
    for (size_t i = begin; i < end; ++i) {
        struct Object* cur_obj = array_get(objects, i);
        if ( was_marked_by_user(user, cur_obj) == 0 ) {
            add_to_top_n(shared_arr, cur_obj, num_pid * capacity,
                         (num_pid + 1) * capacity, size_inside_arr);
            ++size_inside_arr;
        }
    }
    return OK;
}

array* shared_memory(int size){
    array* addr = mmap(NULL, sizeof(array), PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    addr->data = mmap(NULL, size * sizeof(struct Object), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == NULL)
        return NULL;
    return addr;
}

int create_processes (int processes_number, int* processes_name){
    int result = -1;
    for (int i = 0; i < processes_number; ++i){
        int pid = fork();
        if (pid == 0)
            return ++result;
        ++result;
        if (pid != -1)
            processes_name[i] = pid;
    }
    return -2;
}

int top_n_for_user_p(array* marks, array* objects, struct User* user, array* top_n_arr) {

    int processes_number = get_nprocs();
    array* share_arr = shared_memory(top_n_arr->capacity * processes_number);
    int *processes_names = (int*)malloc(processes_number * sizeof(int));
    if (processes_names == NULL)
        return -1;
    int num_pid = create_processes(processes_number, processes_names);
    if (num_pid != -2){
        size_t begin = num_pid * (objects->size / processes_number);
        size_t end = begin;
        if (num_pid != processes_number - 1) {
            end = (num_pid + 1) * (objects->size / processes_number);
        } else {
            end = objects->size;
        }
        share_arr->size = share_arr->capacity;
        top_n_for_user_fork(marks, objects, user, share_arr, top_n_arr->capacity,
                            begin, end, num_pid);
        exit(0);
    }
    for ( int num = 0; num != processes_number; ++num ) {
        while ( waitpid(processes_names[num], NULL, 0) > 0 ) {} }
    array_sort(share_arr, comp_objects);
    free(processes_names);
    for (size_t i = 0; i < top_n_arr->capacity; ++i) {
        array_set(top_n_arr, i, array_get(share_arr, i));
    }
    return 0;
}
