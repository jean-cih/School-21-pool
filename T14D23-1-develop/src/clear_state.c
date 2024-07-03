#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state_sort.h"

#define N 10

void instruction();
char *input_string();
void input_search(FILE *file, int index, char *path);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
struct my_struct read_record_from_file(FILE *pfile, int index);
void delete_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index);
void output(FILE *file, int index);
void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index);

int main() {
    char *path = input_string();
    FILE *file = fopen(path, "r+");
    if (file) {
        int index = get_records_count_in_file(file);
        if (index != 0)
            input_search(file, index, path);
        else
            printf("n/a");
    } else
        printf("n/a");

    free(path);
    fclose(file);

    return 0;
}

void output(FILE *file, int index) {
    for (int i = 0; i < index; i++) {
        struct my_struct read = read_record_from_file(file, i);
        printf("%d %d %d %d %d %d %d %d\n", read.year, read.month, read.day, read.hour, read.minute,
               read.second, read.status, read.code);
    }
}

void input_search(FILE *file, int index, char *path) {
    struct my_struct date1;
    struct my_struct date2;
    struct my_struct array[index];
    char a, b, c, d, x;
    int count = 0;
    if (scanf("%d%c%d%c%d%d%c%d%c%d%c", &date1.day, &a, &date1.month, &b, &date1.year, &date2.day, &c,
              &date2.month, &d, &date2.year, &x) == 11 &&
        (x == ' ' || x == '\n') && b == '.' && a == '.' && date1.day > 0 && date1.day < 32 &&
        date1.month > 0 && date1.month < 13 && date1.year > 0 && c == '.' && d == '.' && date2.day > 0 &&
        date2.day < 32 && date2.month > 0 && date2.month < 13 && date2.year > 0) {
        for (int i = 0; i < index; i++) {
            struct my_struct read = read_record_from_file(file, i);
            if (((read.year < date1.year) ||
                 ((read.year == date1.year && read.month < date1.month) ||
                  (read.year == date1.year && read.month == date1.month && read.day < date1.day))) ||
                ((read.year > date2.year) ||
                 ((read.year == date2.year && read.month > date2.month) ||
                  (read.year == date2.year && read.month == date2.month && read.day > date2.day)))) {
                array[i] = read;
                count++;
            }
        }
        fclose(file);
        FILE *file_end;
        file_end = fopen(path, "w");

        for (int j = 0; j < count; j++) write_record_in_file(file_end, &array[j], j);

        fclose(file_end);
    } else
        printf("n/a");
}

void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index) {
    int offset = index * sizeof(struct my_struct);

    fseek(pfile, offset, SEEK_SET);

    fwrite(record_to_write, sizeof(struct my_struct), 1, pfile);

    fflush(pfile);

    rewind(pfile);
}

char *input_string() {
    char *string = (char *)malloc(N * sizeof(char));
    char sign;
    int i = 0, j = 1;
    while (1) {
        scanf("%c", &sign);
        if (sign == '\n') break;
        if (i >= j * N) {
            j++;
            string = (char *)realloc(string, j * N);
        }
        string[i] = sign;
        i++;
    }

    return string;
}

int input_key(int *key) {
    char x;
    int count = 0;
    if (scanf("%d%c", key, &x) && (x == ' ' || x == '\n')) count = 1;

    return count;
}

struct my_struct read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(struct my_struct);

    fseek(pfile, offset, SEEK_SET);

    struct my_struct record;
    fread(&record, sizeof(struct my_struct), 1, pfile);

    rewind(pfile);

    return record;
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(struct my_struct);
}

void delete_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index) {
    int offset = index * sizeof(struct my_struct);

    fseek(pfile, offset, SEEK_SET);

    fwrite(record_to_write, sizeof(struct my_struct), -1, pfile);

    fflush(pfile);

    rewind(pfile);
}
