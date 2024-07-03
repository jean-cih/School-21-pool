#ifndef DB_STATUS_EVENTS_H
#define DB_STATUS_EVENTS_H

#include <stdio.h>

typedef struct status_events {
    int id_hap;
    int id_mod;
    int new_status;
    char date_stat[11];
    char time_stat[9];
} STATUS_EVENT;

STATUS_EVENT read_record_from_file_s(FILE *pfile, int index);
void write_record_in_file_s(FILE *pfile, STATUS_EVENT *record_to_write, int index);
void swap_records_in_file_s(FILE *pfile, int record_index1, int record_index2);
int get_file_size_in_bytes_s(FILE *pfile);
int get_records_count_in_file_s(FILE *pfile);
int delete_id_s(FILE *db, int id, char *path);

#endif