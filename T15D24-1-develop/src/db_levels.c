#include "db_levels.h"

#include <stdio.h>

LEVEL read_record_from_file_l(FILE *pfile, int index) {
    int offset = index * sizeof(LEVEL);
    fseek(pfile, offset, SEEK_SET);

    LEVEL record;
    fread(&record, sizeof(LEVEL), 1, pfile);
    rewind(pfile);

    return record;
}

void write_record_in_file_l(FILE *pfile, LEVEL *record_to_write, int index) {
    int offset = index * sizeof(LEVEL);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(LEVEL), 1, pfile);

    fflush(pfile);
    rewind(pfile);
}

void swap_records_in_file_l(FILE *pfile, int record_index1, int record_index2) {
    LEVEL record1 = read_record_from_file_l(pfile, record_index1);
    LEVEL record2 = read_record_from_file_l(pfile, record_index2);

    write_record_in_file_l(pfile, &record1, record_index2);
    write_record_in_file_l(pfile, &record2, record_index1);
}

int get_records_count_in_file_l(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size / sizeof(LEVEL);
}