#include <stdio.h>
#include <stdlib.h>
#include "../include/IZ2/generator.h"
#include "../include/IZ2/users_marks_objects.h"

int main() {
    array Users;
    array_new(&Users, sizeof(struct User), 5000000);
    generate_users(&Users); // каждый user содержит выделенную malloc() память

    array Objects;
    array_new(&Objects, sizeof(struct Object), 16000);
    generate_objects(&Objects);

    array Marks;
    array_new(&Marks, sizeof(struct Mark), 500000000);
    generate_marks(&Marks, &Users, &Objects);

//    FILE* file = fopen("../input_files/objects.txt", "rb");
//    if (file == NULL) {
//        return -1;
//    }
//    fread(&Objects, sizeof(array), 1, file);
//    Objects.data = malloc(sizeof(struct Object) * array_size(&Objects));
//    fread(Objects.data, sizeof(struct Object), array_size(&Objects), file);
//    fclose(file);
//    printf("End reading objects.txt\n");
//
//    file = fopen("../input_files/marks.txt", "rb");
//    if (file == NULL) {
//        return -1;
//    }
//    fread(&Marks, sizeof(Marks), 1, file);
//    Marks.data = malloc(sizeof(struct Mark) * array_size(&Marks));
//    fread(Marks.data, sizeof(struct Mark), array_size(&Marks), file);
//    fclose(file);
//    printf("End reading marks.txt\n");
//
//    file = fopen("../input_files/users.txt", "rb");
//    if (file == NULL) return -1;
//    array Users_file;
//    fread(&Users_file, sizeof(array), 1, file);
//    Users_file.data = malloc(array_size(&Users_file) * sizeof(struct User));
//    for (size_t i = 0; i < array_size(&Users_file); ++i) {
//        struct User* cur_user = array_get(&Users_file, i);
//        fread(cur_user, sizeof(struct User), 1, file);
//        cur_user->marked_obj_ids = malloc(sizeof(array));
//        fread(cur_user->marked_obj_ids, sizeof(array), 1, file);
//        cur_user->marked_obj_ids->data = malloc(sizeof(unsigned int) * array_size(cur_user->marked_obj_ids));
//        fread(cur_user->marked_obj_ids->data, sizeof(unsigned int), array_size(cur_user->marked_obj_ids), file);
//    }
//    fclose(file);
//    printf("End reading users.txt\n");
//
//    printf("%zu %zu %zu\n", array_size(&Users_file), array_size(&Objects), array_size(&Marks));

    array top10;
    array_new(&top10, sizeof(struct Object*), 10);
    struct User* cur_user = array_get(&Users, 0);
    top_n_for_user(&Marks, &Objects, cur_user, &top10);

    for (int i = 0; i < 10; ++i) {
        struct Object** cur_obj = array_get(&top10, i);
        printf("%f %d %d %d %d %d %d\n", (*cur_obj)->average_mark,
               (*cur_obj)->id,
               (*cur_obj)->count_of[0],
               (*cur_obj)->count_of[1],
               (*cur_obj)->count_of[2],
               (*cur_obj)->count_of[3],
               (*cur_obj)->count_of[4]);
    }
    for (size_t i = 0; i < array_size(&Users); ++i) {
        struct User* user = array_get(&Users, i);
        array_remove(user->marked_obj_ids);
        free(user->marked_obj_ids);
    }
    array_remove(&Users);
    array_remove(&Objects);
    array_remove(&Marks);
    array_remove(&top10);
    return 0;
}


//
// DEBUG FUNCTIONS
//





//
//    for (size_t i = 0; i < array_size(&Marks_file); ++i) {
//        struct Mark* cur_mark = array_get(&Marks_file, i);
//        struct Object* cur_obj = array_get(&Objects, cur_mark->object_id);
//        ++cur_obj->count_of[cur_mark->mark];
//        calculate_average_mark(cur_obj);
//    }
//    printf("End to count\n");

//    printf("%zu", array_size(&Marks));

//    for (int i = 0; i < array_size(&Marks); ++i) {
//        struct Mark* cur_mark = array_get(&Marks, i);
//        struct User* cur_user = array_get(&Users, cur_mark->user_id);
//        struct Object* cur_obj = array_get(&Objects, cur_mark->object_id);
//        int found = 0;
//        for (int j = 0; j < array_size(cur_user->marked_obj_ids); ++j) {
//            unsigned int* obj_id = array_get(cur_user->marked_obj_ids, j);
//            if (*obj_id == cur_obj->id) {
//                found++;
//            }
//        }
//        if (found == 0 && array_size(cur_user->marked_obj_ids) != 0)
//            printf("Fail\n");
//        if (array_size(cur_user->marked_obj_ids) == 0)
//            printf(("Size == 0"));
//        if (!was_marked_by_user(cur_user, cur_obj)) {
//            printf(("was_marked - no"));
//        }
//    }

//    FILE *file = fopen("users.txt", "wb");
//    if (file == NULL) return -1;
//    fwrite(&Users, sizeof(Users), 1, file);
//    for (size_t i = 0; i < array_size(&Users); ++i) {
//        struct User* cur_user = array_get(&Users, i);
//        fwrite(cur_user, sizeof(struct User), 1, file);
//        fwrite(cur_user->marked_obj_ids, sizeof(array), 1, file);
//        fwrite(cur_user->marked_obj_ids->data, sizeof(unsigned int),
//               array_size(cur_user->marked_obj_ids), file);
//    }
//    fclose(file);
//
//    file = fopen("objects.txt", "wb");
//    if (file == NULL) return -1;
//    fwrite(&Objects, sizeof(Objects), 1, file);
//    fwrite(Objects.data, sizeof(struct Object), array_size(&Objects), file);
//    fclose(file);
//
//    printf("Begin to write\n");
//    file = fopen("marks.txt", "wb");
//    if (file == NULL) return -1;
//    fwrite(&Marks, sizeof(Marks), 1, file);
//    printf("Begin to write data\n");
//    fwrite(Marks.data, sizeof(struct Mark), array_size(&Marks), file);
//    fclose(file);
//    printf("End to write\n");
//
//    for (size_t i = 0; i < array_size(&Users); ++i) {
//        struct User* user = array_get(&Users, i);
//        array_remove(user->marked_obj_ids);
//        free(user->marked_obj_ids);
//    }
//    array_remove(&Users);
//    array_remove(&Objects);
//    array_remove(&Marks);
//    printf("End delete memory\n");
