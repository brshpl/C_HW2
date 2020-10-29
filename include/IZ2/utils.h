#ifndef TESTY_UTILS_H
#define TESTY_UTILS_H

#include "array.h"

#define NUMBER_OF_MARKS (5)
enum Rating { TERRIBLE, BAD, OK, GOOD, EXCELLENT };

// size_t не используется для экономии места в памяти
struct Mark {
    unsigned int object_id;
    unsigned int user_id;
    enum Rating mark;
};  // 12 bytes

struct Object {
    double average_mark;
    unsigned int id;
    unsigned int count_of[NUMBER_OF_MARKS];
};  // 16 bytes

struct User {
    array* marked_obj_ids;
    unsigned int id;
};  // 12 bytes

double calculate_average_mark(struct Object* obj);

int was_marked_by_user(struct User* user, struct Object* object);
int comp_objects(void* param1, void* param2);

#endif //TESTY_UTILS_H
