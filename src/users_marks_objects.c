#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/IZ2/users_marks_objects.h"

#define ERROR -1
#define OK 0
#define YES 1
#define  NO 0

int top_n_for_user(array* marks, array* objects, struct User* user, array* top_n_arr) {
    if (marks == NULL || user == NULL || top_n_arr == NULL || top_n_arr->capacity == 0)
        return ERROR;
    for (size_t i = 0; i < array_size(objects); ++i) {
        struct Object* cur_obj = array_get(objects, i);
        if ( was_marked_by_user(user, cur_obj) == NO ) {
            add_to_top_n(top_n_arr, cur_obj);
        }
    }
    return OK;
}



int add_to_top_n(array* top_n_arr, struct Object* obj) {
    if (top_n_arr == NULL || obj == NULL)
        return ERROR;
    if (array_size(top_n_arr) == 0) {
        array_add(top_n_arr, &obj);
        return OK;
    }
    if (array_size(top_n_arr) < top_n_arr->capacity) {
        array_add(top_n_arr, &obj);
        if (array_sort(top_n_arr, comp_objects) == ERROR)
            return ERROR;
        return OK;
    }
    struct Object** arr_obj = array_get(top_n_arr, array_size(top_n_arr) - 1);
    if ((*arr_obj)->average_mark < obj->average_mark) {
        array_set(top_n_arr, array_size(top_n_arr) - 1, &obj);
        array_sort(top_n_arr, comp_objects);
    }
    return OK;
}


FILE* load_from_files(FILE* users_file, FILE* objects_file, FILE* marks_file,
                      array* users_arr, array* obj_arr, array* marks_arr) {
    assert(users_file != NULL && objects_file != NULL && marks_file != NULL &&
           users_arr != NULL && obj_arr != NULL && marks_file != NULL);
    fread(obj_arr, sizeof(array), 1, objects_file);
    obj_arr->data = malloc(sizeof(struct Object) * array_size(obj_arr));
    fread(obj_arr->data, sizeof(struct Object), array_size(obj_arr), objects_file);

    fread(marks_arr, sizeof(array), 1, marks_file);
    marks_arr->data = malloc(sizeof(struct Mark) * array_size(marks_arr));
    fread(marks_arr->data, sizeof(struct Mark), array_size(marks_arr), marks_file);

    fread(users_arr, sizeof(array), 1, users_file);
    users_arr->data = malloc(array_size(users_arr) * sizeof(struct User));
    for (size_t i = 0; i < array_size(users_arr); ++i) {
        struct User *cur_user = array_get(users_arr, i);
        fread(cur_user, sizeof(struct User), 1, users_file);
        cur_user->marked_obj_ids = malloc(sizeof(array));
        array *ins_arr = cur_user->marked_obj_ids;
        fread(ins_arr, sizeof(array), 1, users_file);
        ins_arr->data = malloc(sizeof(unsigned int) * array_size(ins_arr));
        fread(ins_arr->data, sizeof(unsigned int), array_size(ins_arr), users_file);
    }
}
