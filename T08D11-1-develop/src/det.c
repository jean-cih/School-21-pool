#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n, int m);
int input_size(int *n, int *m);
int input(double **matrix, int *n, int *m);
void output(double det);
void swap(double *a, double *b);
void cleaning(double **a, int n);

int main() {
    int n, m;
    if (input_size(&n, &m)) {
        double **matrix = malloc(n * m * sizeof(double) + m * sizeof(double *));
        double *p = (double *)(matrix + n);
        for (int i = 0; i < n; i++) matrix[i] = p + m * i;
        if (input(matrix, &n, &m)) {
            double determin = det(matrix, n, m);
            output(determin);
        } else
            printf("n/a");

        free(matrix);
    } else
        printf("n/a");

    return 0;
}

double det(double **matrix, int n, int m) {
    if (n == 1)
        return matrix[0][0];
    else if (n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else {
        double determinate = 0;
        for (int k = 0; k < n; k++) {
            double **b = malloc((n - 1) * (n - 1) * sizeof(double) + (n - 1) * sizeof(double *));
            for (int i = 0; i < n - 1; i++) {
                b[i] = malloc((n - 1) * sizeof(int));
            }
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j == k)
                        continue;
                    else if (j < k)
                        b[i - 1][j] = matrix[i][j];
                    else
                        b[i - 1][j - 1] = matrix[i][j];
                }
            }
            determinate += pow(-1, k + 2) * matrix[0][k] * det(b, n - 1, m - 1);
            cleaning(b, n - 1);
        }
        return determinate;
    }
}

int input_size(int *n, int *m) {
    char x;
    int count = 0;
    if (scanf("%d%d%c", n, m, &x) == 3 && x == '\n' && *n > 0 && *m > 0) count = 1;

    return count;
}

int input(double **matrix, int *n, int *m) {
    char x;
    int count = 0;
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            scanf("%lf%c", &matrix[i][j], &x);

            if ((x != ' ' && j < *m - 1) || (x != '\n' && j == *m - 1) || (x != '\n' && x != ' ')) {
                count = 0;
                break;
            } else
                count = 1;
        }
    }

    return count;
}

void swap(double *a, double *b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

void output(double det) { printf("%.6lf", det); }

void cleaning(double **a, int n) {
    for (int i = 0; i < n; i++) free(a[i]);
    free(a);
}