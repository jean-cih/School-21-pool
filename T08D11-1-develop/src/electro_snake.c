#include <stdio.h>
#include <stdlib.h>

int input_size(int *n, int *m);
int input(int **matrix, int *n, int *m);
int** declaration(int line, int column);
void sort_vertical(int **matrix, int n, int m, int **result_matrix);
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);
void quick_sort(int *a, int left, int right);
void swap(int *a, int *b);
void output(int **matrix, int n, int m);


int main() {
    int n, m;

    if (input_size(&n, &m)) {
        int **matrix = declaration(n, m);
        int **result = declaration(n, m);
        if (input(matrix, &n, &m)) {
            sort_vertical(matrix, n, m, result);
            output(result, n, m);
            printf("\n\n");
            sort_horizontal(matrix, n, m, result);
            output(result, n, m);
        } else
            printf("n/a");

        free(matrix);
        free(result);
    } else
        printf("n/a");

    return 0;
}

int input_size(int *n, int *m) {
    char x;
    int count = 0;
    if (scanf("%d%d%c", n, m, &x) == 3 && x == '\n' && *n > 0 && *m > 0) count = 1;

    return count;
}

int input(int **matrix, int *n, int *m) {
    char x;
    int count = 0;
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            scanf("%d%c", &matrix[i][j], &x);

            if ((x != ' ' && j < *m - 1) || (x != '\n' && j == *m - 1) || (x != '\n' && x != ' ')) {
                count = 0;
                break;
            } else
                count = 1;
        }
    }

    return count;
}

int** declaration(int line, int column){
    int **matrix = malloc(line * column * sizeof(int) + column * sizeof(int *));
    int *pointer = (int *)(matrix + line);
    for (int i = 0; i < line; i++) matrix[i] = pointer + column * i;

    return matrix;
}

void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int *array = (int *)malloc(n * m * sizeof(int));

    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            array[k] = matrix[i][j];
            k++;
        }
    }

    quick_sort(array, 0, k - 1);

    int g = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i % 2 == 0)
                result_matrix[j][i] = array[g];
            else
                result_matrix[n - j - 1][i] = array[g];
            g++;
        }
    }

    free(array);
}

void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    int *array = (int *)malloc(n * m * sizeof(int));

    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            array[k] = matrix[i][j];
            k++;
        }
    }

    quick_sort(array, 0, k - 1);

    int g = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i % 2 == 0)
                result_matrix[i][j] = array[g];
            else
                result_matrix[i][m - j - 1] = array[g];
            g++;
        }
    }

    free(array);
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == m - 1)
                printf("%d", matrix[i][j]);
            else
                printf("%d ", matrix[i][j]);
        }
        if (i != n - 1) printf("\n");
    }
}

void quick_sort(int *a, int left, int right) {
    int l = left, r = right;
    int pivot = *(a + (l + r) / 2);
    while (l <= r) {
        while (a[l] < pivot) l++;
        while (a[r] > pivot) r--;
        if (l <= r) swap(&a[l++], &a[r--]);
    }
    if (left < r) quick_sort(a, left, r);
    if (right > l) quick_sort(a, l, right);
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}