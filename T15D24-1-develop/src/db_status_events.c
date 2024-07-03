#include "db_status_events.h"

#include <stdio.h>

STATUS_EVENT read_record_from_file_s(FILE *pfile, int index) {
    int offset = index * sizeof(STATUS_EVENT);
    fseek(pfile, offset, SEEK_SET);

    STATUS_EVENT record;
    fread(&record, sizeof(STATUS_EVENT), 1, pfile);
    rewind(pfile);

    return record;
}

void write_record_in_file_s(FILE *pfile, STATUS_EVENT *record_to_write, int index) {
    int offset = index * sizeof(STATUS_EVENT);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(STATUS_EVENT), 1, pfile);

    fflush(pfile);
    rewind(pfile);
}

void swap_records_in_file_s(FILE *pfile, int record_index1, int record_index2) {
    STATUS_EVENT record1 = read_record_from_file_s(pfile, record_index1);
    STATUS_EVENT record2 = read_record_from_file_s(pfile, record_index2);

    write_record_in_file_s(pfile, &record1, record_index2);
    write_record_in_file_s(pfile, &record2, record_index1);
}

int get_records_count_in_file_s(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size / sizeof(STATUS_EVENT);
}
