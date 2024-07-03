#include "db_modules.h"

#include <stdio.h>

MODULE read_record_from_file_m(FILE *pfile, int index) {
    int offset = index * sizeof(MODULE);
    fseek(pfile, offset, SEEK_SET);

    MODULE record;
    fread(&record, sizeof(MODULE), 1, pfile);
    rewind(pfile);

    return record;
}

void write_record_in_file_m(FILE *pfile, MODULE *record_to_write, int index) {
    int offset = index * sizeof(MODULE);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(MODULE), 1, pfile);

    fflush(pfile);
    rewind(pfile);
}

void swap_records_in_file_m(FILE *pfile, int record_index1, int record_index2) {
    MODULE record1 = read_record_from_file_m(pfile, record_index1);
    MODULE record2 = read_record_from_file_m(pfile, record_index2);

    write_record_in_file_m(pfile, &record1, record_index2);
    write_record_in_file_m(pfile, &record2, record_index1);
}

int get_records_count_in_file_m(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size / sizeof(MODULE);
}
