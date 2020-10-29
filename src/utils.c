#include "IZ2/utils.h"

#define ERROR -1
#define OK 0

double calculate_average_mark(struct Object* obj) {
    if (obj == NULL)
        return ERROR;
    size_t sum = 0;
    size_t total_count = 0;
    for (int i = 0; i < NUMBER_OF_MARKS; ++i) {
        size_t count = obj->count_of[i];
        sum += count * (i + 1);
        total_count += count;
    }
    obj->average_mark = (double) sum / (double) total_count;
    return obj->average_mark;
}

#define YES 1
#define  NO 0
int was_marked_by_user(struct User* user, struct Object* object) {
    if (user == NULL || object == NULL)
        return ERROR;
    for (size_t i = 0; i < array_size(user->marked_obj_ids); ++i) {
        unsigned int* cur_obj_id = array_get(user->marked_obj_ids, i);
        if (*cur_obj_id == object->id)
            return YES;
    }
    return NO;
}

int comp_objects(void* param1, void* param2) {
    struct Object** obj1 = param1;
    struct Object** obj2 = param2;
    if ((*obj1)->average_mark < (*obj2)->average_mark)
        return 1;
    else
        return 0;
}