#ifndef TESTY_USERS_MARKS_OBJECTS_P_H
#define TESTY_USERS_MARKS_OBJECTS_P_H

#include <sys/mman.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <unistd.h>
#include "array.h"
#include "utils.h"

int add_to_top_n_p(array* top_n_arr, struct Object* obj, size_t begin,
                 size_t end, size_t arr_size);

int top_n_for_user_fork(array* marks, array* objects, struct User* user,
                        array* shared_arr, size_t capacity, size_t begin,
                        size_t end, int num_pid);

array* shared_memory(int size);

int create_processes (int processes_number, int* processes_name);

int top_n_for_user_p(array* marks, array* objects, struct User* user, array* top_n_arr);

#endif //TESTY_USERS_MARKS_OBJECTS_P_H
