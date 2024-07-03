#include <stdio.h>
#include <stdlib.h>

#define NMAX 100

void instruction();
int input_operation(int *n);
int input_size(int *line, int *column);
void stat_declaration(int line, int column);
void dynamic1_declaration(int line, int column);
void dynamic2_declaration(int line, int column);
void dynamic3_declaration(int line, int column);
int input_array(int **a, int line, int column);
void output(int **a, int line, int column);
void cleaning(int **a, int size);
void instruction();

int main() {
    int n;
    int line, column;
    instruction();
    if (input_operation(&n)) {
        if (input_size(&line, &column)) {
            if (n == 1) {
                stat_declaration(line, column);
            } else if (n == 2) {
                dynamic1_declaration(line, column);
            } else if (n == 3) {
                dynamic2_declaration(line, column);
            } else if (n == 4) {
                dynamic3_declaration(line, column);
            }

        } else
            printf("n/a");
    } else
        printf("n/a");

    return 0;
}

void instruction() {
    printf("Enter the way of the memory allocation\n");
    printf("1 - static\n");
    printf("2 - the first dynamic\n");
    printf("3 - the second dynamic\n");
    printf("4 - the third dynamic\n");
}

int input_operation(int *n) {
    char x;
    int count = 0;
    if (scanf("%d%c", n, &x) == 2 && x == '\n' && *n >= 1 && *n <= 4) count = 1;

    return count;
}

int input_size(int *line, int *column) {
    char x;
    int count = 0;
    if (scanf("%d%d%c", line, column, &x) == 3 && x == '\n' && *line > 0 && *column > 0) count = 1;

    return count;
}

int input_array(int **a, int line, int column) {
    char x;
    int count = 0;
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            scanf("%d%c", &a[i][j], &x);
            if ((x != ' ' && j < column - 1) || (x != '\n' && j == column - 1) || (x != ' ' && x != '\n')) {
                count = 0;
                break;
            } else
                count = 1;
        }
    }
    return count;
}

void stat_declaration(int line, int column) {
    int data[NMAX][NMAX];
    int *p[NMAX];
    for (int n = 0; n < line; n++) {
        p[n] = data[n];
    }
    if (input_array(p, line, column))
        output(p, line, column);
    else
        printf("n/a");
}

void dynamic1_declaration(int line, int column) {
    int **data1 = malloc(line * column * sizeof(int) + line * sizeof(int *));
    int *p = (int *)(data1 + line);
    for (int i = 0; i < line; i++) data1[i] = p + column * i;

    if (input_array(data1, line, column)) {
        output(data1, line, column);
        free(data1);
    } else
        printf("n/a");
}

void dynamic2_declaration(int line, int column) {
    int **data2 = malloc(line * sizeof(int *));

    for (int i = 0; i < line; i++) data2[i] = malloc(column * sizeof(int));

    if (input_array(data2, line, column)) {
        output(data2, line, column);
        cleaning(data2, line);
    } else
        printf("n/a");
}

void dynamic3_declaration(int line, int column) {
    int **data3 = malloc(line * sizeof(int *));
    int *values_data3 = malloc(line * column * sizeof(int));

    for (int i = 0; i < line; i++) {
        data3[i] = values_data3 + column * i;
    }

    if (input_array(data3, line, column)) {
        output(data3, line, column);
        free(values_data3);
        free(data3);
    } else
        printf("n/a");
}

void output(int **a, int line, int column) {
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            if (i == line - 1 && j == column - 1)
                printf("%d", a[i][j]);
            else
                printf("%d ", a[i][j]);
        }
        if (i != line - 1) printf("\n");
    }
}

void cleaning(int **a, int size) {
    for (int i = 0; i < size; i++) {
        free(a[i]);
    }
    free(a);
}
