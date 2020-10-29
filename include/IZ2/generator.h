#ifndef IZ2_GENERATOR_H
#define IZ2_GENERATOR_H

#include "users_marks_objects.h"

// generates array of User
// size = users_arr->capacity
void generate_users(array* users_arr);

// generates array of Object without marks
// size = objects_arr->capacity
void generate_objects(array* objects_arr);

// generates array of random marks for random objects set by random users
// size = marks_arr->capacity
// NOTE: size <= array_size(users_arr) * array_size(objects_arr)
void generate_marks(array* marks_arr, array* users_arr, array* objects_arr);

#endif //IZ2_GENERATOR_H
