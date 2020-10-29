#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../include/IZ2/generator.h"

void generate_users(array* users_arr) {
    if (users_arr == NULL)
        return;
    for (unsigned int i = 0; i < users_arr->capacity; ++i) {
        struct User cur_user;
        cur_user.id = i;
        array* user_marks = malloc(sizeof(array));
        cur_user.marked_obj_ids = user_marks;
        array_new(user_marks, sizeof(unsigned int), 0);
        array_add(users_arr, &cur_user);
    }
}

void generate_objects(array* objects_arr) {
    if (objects_arr == NULL)
        return;
    for (unsigned int i = 0; i < objects_arr->capacity; ++i) {
        struct Object cur_object;
        cur_object.id = i;
        cur_object.average_mark = 0;
        for (size_t j = 0; j < NUMBER_OF_MARKS; ++j) {
            cur_object.count_of[j] = 0;
        }
        array_add(objects_arr, &cur_object);
    }
}

void generate_marks(array* marks_arr, array* users_arr, array* objects_arr) {
    if (marks_arr == NULL || users_arr == NULL || objects_arr == NULL)
        return;
    size_t max_marks = users_arr->size * objects_arr->size;
//    double chance = (double) marks_arr->capacity / (double) max_marks;
    double chance = 31250.0 / 170000000.0;
    if (chance > 1)
        chance = 1;

    srandom(time(NULL));
    long int chance_map = (long int) (chance * max_marks);

    size_t marks_left = marks_arr->capacity;
    size_t marks_free = max_marks;
    for (size_t i = 0; i < array_size(objects_arr); ++i) {
        struct Object* cur_object = array_get(objects_arr, i);
        for (size_t j = 0; j < array_size(users_arr); ++j) {
            if ((random() % max_marks < chance_map || marks_left >= marks_free)
                && marks_left > 0) {
                struct Mark cur_mark;
                struct User* cur_user = array_get(users_arr, j);
                cur_mark.mark = random() % NUMBER_OF_MARKS;
                cur_mark.object_id = cur_object->id;
                cur_mark.user_id = cur_user->id;
                ++cur_object->count_of[cur_mark.mark];
                array_add(marks_arr, &cur_mark);
                array_add(cur_user->marked_obj_ids, &cur_object->id);
                --marks_left;
                if (marks_left % 10000000 == 0)
                    printf("%zu   %d\n", marks_left, cur_object->id);
            }
            --marks_free;
            if (marks_left == 0)
                break;
        }
        calculate_average_mark(cur_object);
        if (marks_left == 0)
            break;
    }
}
