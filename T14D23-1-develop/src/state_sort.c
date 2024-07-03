#include "state_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

void instruction();
char *input_string();
int input_key(int *key);
struct my_struct read_record_from_file(FILE *pfile, int index);
void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
void status_0(FILE *file, int index);
void status_1(FILE *file, int index);
int status_2(FILE *file, int index);
void sort(FILE *file, int i);

int main() {
    instruction();
    FILE *file;
    char *path = input_string();
    file = fopen(path, "r+");
    if (file) {
        int key;
        int status = input_key(&key);
        int index = get_records_count_in_file(file);
        if (index != 0 && status && key == 0) {
            status_0(file, index);
        } else if (index != 0 && status && key == 1) {
            status_1(file, index);
            status_0(file, index);
        } else if (status && key == 2) {
            if (status_2(file, index)) {
                status_1(file, index + 1);
                status_0(file, index + 1);
            } else
                printf("n/a");
        } else
            printf("n/a");
    } else
        printf("n/a");

    free(path);
    fclose(file);

    return 0;
}

void instruction() {
    printf("\n        Сначала введите путь до файла\n");
    printf("      После ввдедите действие: 0 1 или 2\n");
    printf("0 - вывод содержимого файла в консоль\n");
    printf("1 - сортировка содержимого файла и вывод на экран\n");
    printf("2 - добавление записи, сортировка и вывод на экран\n");
}

void status_0(FILE *file, int index) {
    for (int i = 0; i < index; i++) {
        struct my_struct read = read_record_from_file(file, i);
        printf("%d %d %d %d %d %d %d %d\n", read.year, read.month, read.day, read.hour, read.minute,
               read.second, read.status, read.code);
    }
}

int status_2(FILE *file, int index) {
    struct my_struct write;
    char g;
    int count = 0;
    if (scanf("%d%d%d%d%d%d%d%d%c", &write.year, &write.month, &write.day, &write.hour, &write.minute,
              &write.second, &write.status, &write.code, &g) == 9 &&
        (g == ' ' || g == '\n') && write.year > 0 && write.month > 0 && write.month < 13 && write.day > 0 &&
        write.day < 32 && write.hour >= 0 && write.hour < 25 && write.minute >= 0 && write.minute < 61 &&
        write.second >= 0 && write.second < 61 && (write.status == 1 || write.status == 0)) {
        write_record_in_file(file, &write, index);
        count = 1;
    } else
        count = 0;

    return count;
}

void status_1(FILE *file, int index) {
    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - 1; j++) sort(file, j);
    }
}

void sort(FILE *file, int i) {
    struct my_struct upper = read_record_from_file(file, i);
    struct my_struct lower = read_record_from_file(file, i + 1);

    if ((upper.year > lower.year) ||
        ((upper.year == lower.year && upper.month > lower.month) ||
         ((upper.year == lower.year && upper.month == lower.month && upper.day > lower.day) ||
          ((upper.year == lower.year && upper.month == lower.month && upper.day == lower.day &&
            upper.hour > lower.hour) ||
           ((upper.year == lower.year && upper.month == lower.month && upper.day == lower.day &&
             upper.hour == lower.hour && upper.minute > lower.minute) ||
            (upper.year == lower.year && upper.month == lower.month && upper.day == lower.day &&
             upper.hour == lower.hour && upper.minute == lower.minute && upper.second > lower.second))))))
        swap_records_in_file(file, i, i + 1);
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

void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index) {
    int offset = index * sizeof(struct my_struct);

    fseek(pfile, offset, SEEK_SET);

    fwrite(record_to_write, sizeof(struct my_struct), 1, pfile);

    fflush(pfile);

    rewind(pfile);
}

void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    struct my_struct record1 = read_record_from_file(pfile, record_index1);
    struct my_struct record2 = read_record_from_file(pfile, record_index2);

    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
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
