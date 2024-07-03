#ifndef DB_MODULES_H
#define DB_MODULES_H

#include <stdio.h>

typedef struct modules {
    int id;
    char name[30];
    int mem_n;
    int item_n;
    int flag_del;
} MODULE;

MODULE read_record_from_file_m(FILE *pfile, int index);
void write_record_in_file_m(FILE *pfile, MODULE *record_to_write, int index);
void swap_records_in_file_m(FILE *pfile, int record_index1, int record_index2);
int get_file_size_in_bytes_m(FILE *pfile);
int get_records_count_in_file_m(FILE *pfile);
int delete_id_m(FILE *db, int id, char *path);

#endif