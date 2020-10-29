#ifndef IZ2_USERS_MARKS_OBJECTS_H
#define IZ2_USERS_MARKS_OBJECTS_H

#include "utils.h"

// top_n_arr - array, where we should store TOP-N Object* for *user
// N = top_n_arr->capacity
int top_n_for_user(array* marks, array* objects, struct User* user, array* top_n_arr);
int add_to_top_n(array* top_n_arr, struct Object* obj);

FILE* load_from_files(FILE* users_file, FILE* objects_file, FILE* marks_file,
                      array* users_arr, array* obj_arr, array* marks_arr);

#endif //IZ2_USERS_MARKS_OBJECTS_H
