#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "database.h"
#include "db_levels.h"
#include "db_modules.h"
#include "db_status_events.h"

MODULE select_m(FILE *db, int id) { return read_record_from_file_m(db, id); }

LEVEL select_l(FILE *db, int id) { return read_record_from_file_l(db, id); }

STATUS_EVENT select_s(FILE *db, int id) { return read_record_from_file_s(db, id); }

int insert_m(FILE *db, MODULE *entity) {
    int index = get_records_count_in_file_m(db);
    char a, b, c, d, e;
    if (scanf("%d%c%s%c%d%c%d%c%d%c", &entity->id, &a, entity->name, &b, &entity->mem_n, &c, &entity->item_n,
              &d, &entity->flag_del, &e) == 10 &&
        e == '\n' && a == ' ' && b == ' ' && c == ' ' && d == ' ')
        write_record_in_file_m(db, entity, index);
    else
        printf("Incorrect input data:\n");

    return 0;
}

int insert_l(FILE *db, LEVEL *entity) {
    int index = get_records_count_in_file_l(db);
    char a, b, c;
    if (scanf("%d%c%d%c%d%c", &entity->level_n, &a, &entity->item_q, &b, &entity->flag_def, &c) == 6 &&
        c == '\n' && a == ' ' && b == ' ')
        write_record_in_file_l(db, entity, index);
    else
        printf("Incorrect input data:\n");

    return 0;
}

int insert_s(FILE *db, STATUS_EVENT *entity) {
    int index = get_records_count_in_file_s(db);
    char a, b, e;
    if (scanf("%d%c%d%c%d%c", &entity->id_hap, &a, &entity->id_mod, &b, &entity->new_status, &e) == 6 && e == '\n' && a == ' ' && b == ' '){
        time_t mytime = time(NULL);
        struct tm *now = localtime(&mytime);
        char str_t[9];
        char str_d[11];
        strftime(str_t, sizeof(str_t), "%T", now);
        strftime(str_d, sizeof(str_d), "%D", now);
        for(int i = 0; i < 8; i++){
        	entity->time_stat[i] = str_t[i];
        }
        int k = 0;
        for(int j = 0; j < 10; j++){
        	if(j == 2 || j == 5)
        		entity->date_stat[j] = '.';
        	else if(j == 6){
        		entity->date_stat[j] = '2';
        		k++;
        	}
        	else if(j == 7){
        		entity->date_stat[j] = '0';
        		k++;
        	}
        	else
        		entity->date_stat[j] = str_d[j - k];
        }
        write_record_in_file_s(db, entity, index);
 
    }
    else
        printf("Incorrect input data:\n");

    return 0;
}

int update_m(FILE *db, int id, MODULE *entity) {
    char a, b, c, d, e;
    if (scanf("%d%c%s%c%d%c%d%c%d%c", &entity->id, &a, entity->name, &b, &entity->mem_n, &c, &entity->item_n,
              &d, &entity->flag_del, &e) == 10 &&
        e == '\n' && a == ' ' && b == ' ' && c == ' ' && d == ' ')
        write_record_in_file_m(db, entity, id);
    else
        printf("Incorrect input data:\n");
    return 0;
}

int update_l(FILE *db, int id, LEVEL *entity) {
    char a, b, c;
    if (scanf("%d%c%d%c%d%c", &entity->level_n, &a, &entity->item_q, &b, &entity->flag_def, &c) == 6 &&
        c == '\n' && a == ' ' && b == ' ')
        write_record_in_file_l(db, entity, id);
    else
        printf("Incorrect input data:\n");

    return 0;
}

int update_s(FILE *db, int id, STATUS_EVENT *entity) {
    char a, b, c, d, e;
    if (scanf("%d%c%d%c%d%c%s%c%s%c", &entity->id_hap, &a, &entity->id_mod, &b, &entity->new_status, &c,
              entity->date_stat, &d, entity->time_stat, &e) == 10 &&
        e == '\n' && a == ' ' && b == ' ' && c == ' ' && d == ' ')
        write_record_in_file_s(db, entity, id);
    else
        printf("Incorrect input data:\n");

    return 0;
}

int delete_m(int id, char *path) {
    truncate(path, id * sizeof(MODULE));

    return 0;
}
int delete_l(int id, char *path) {
    truncate(path, id * sizeof(LEVEL));

    return 0;
}

int delete_s(int id, char *path) {
    truncate(path, id * sizeof(STATUS_EVENT));

    return 0;
}

int delete_id_m(FILE *db, int id, char *path) {
    int index = get_records_count_in_file_m(db);
    int count = 0;
    for (int j = 0; j < index; j++) {
        MODULE count1 = read_record_from_file_m(db, j);
        count++;
        if (count1.id == id) break;
    }
    for (int i = count; i < index; i++) swap_records_in_file_m(db, i, i + 1);

    truncate(path, (index - 1) * sizeof(MODULE));

    return 0;
}

int delete_id_s(FILE *db, int id, char *path) {
    int index = get_records_count_in_file_s(db);
    int count = 0;
    for (int j = 0; j < index; j++) {
        STATUS_EVENT count1 = read_record_from_file_s(db, j);
        count++;
        if (count1.id_mod == id) break;
    }
    for (int i = count; i < index; i++) swap_records_in_file_s(db, i, i + 1);

    truncate(path, (index - 1) * sizeof(STATUS_EVENT));

    return 0;
}

void menu() {
    printf("\x1b[38;2;138;43;226m");
    printf("\nPlease choose one operation:\n");
    printf("\x1b[38;2;0;255;255m");
    printf("1. SELECT\n");
    printf("2. INSERT\n");
    printf("3. UPDATE\n");
    printf("4. DELETE\n");
    printf("5. Get all active additional modules (last module status is 1)\n");
    printf("6. Delete modules by ids\n");
    printf("7. Set protected mode for module by id\n");
    printf("8. Move module by id to specified memory level and cell\n");
    printf("9. Set protection flag of the specified memory level\n");
    printf("10. To exit the program\n");
    printf("\x1b[38;2;138;43;226m");
}

void instruction(int operation) {
    printf("\x1b[38;2;138;43;226m");
    if(operation != 5 && operation != 6){
        printf("Please choose a table:\n");
        printf("\x1b[38;2;0;255;255m");
        printf("1. Modules\n");
        printf("2. Levels\n");
        printf("3. Status events\n");
    }
    else if(operation == 5){
        printf("Please choose a table:\n");
        printf("\x1b[38;2;0;255;255m");
        printf("1. Modules\n");
    }
    else if(operation == 6){
        printf("Please choose a table:\n");
        printf("\x1b[38;2;0;255;255m");
        printf("1. Modules\n");
        printf("3. Status events\n");
    }
    printf("\x1b[38;2;138;43;226m");
}

void drawing(int n){
    printf("\x1b[38;2;205;92;92m");
    for(int i = 0; i < n; i++)
        printf("-");
    printf("\n");
}

