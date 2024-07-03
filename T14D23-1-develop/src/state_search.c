#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state_sort.h"

#define N 10

void instruction();
char *input_string();
void input_search(FILE *file, int index);
int search(FILE *file, struct my_struct date, int i);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
struct my_struct read_record_from_file(FILE *pfile, int index);

int main() {
    char *path = input_string();
    FILE *file = fopen(path, "r+");
    if (file) {
        int index = get_records_count_in_file(file);
        if (index != 0)
            input_search(file, index);
        else
            printf("n/a");
    } else
        printf("n/a");

    free(path);
    fclose(file);

    return 0;
}

void input_search(FILE *file, int index) {
    struct my_struct date;
    char a, b, x;
    int code = 0;
    if (scanf("%d%c%d%c%d%c", &date.day, &a, &date.month, &b, &date.year, &x) == 6 &&
        (x == ' ' || x == '\n') && b == '.' && a == '.' && date.day > 0 && date.day < 32 && date.month > 0 &&
        date.month < 13) {
        for (int i = 0; i < index; i++) {
            code = search(file, date, i);
            if (code != 0) {
                printf("%d", code);
                break;
            }
        }
        if (code == 0) printf("n/a");
    } else
        printf("n/a");
}

int search(FILE *file, struct my_struct date, int i) {
    int code = 0;
    struct my_struct read = read_record_from_file(file, i);
    if (read.day == date.day && read.month == date.month && read.year == date.year) code = read.code;

    return code;
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
