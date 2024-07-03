#ifndef DB_LEVELS_H
#define DB_LEVELS_H

#include <stdio.h>

typedef struct levels {
    int level_n;
    int item_q;
    int flag_def;
} LEVEL;

LEVEL read_record_from_file_l(FILE *pfile, int index);
void write_record_in_file_l(FILE *pfile, LEVEL *record_to_write, int index);
void swap_records_in_file_l(FILE *pfile, int record_index1, int record_index2);
int get_file_size_in_bytes_l(FILE *pfile);
int get_records_count_in_file_l(FILE *pfile);

#endif