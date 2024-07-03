#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
    } else
        printf("n/a");

    return 0;
}

int input(int *a, int *n) {
    char x, y;
    int count = 0;
    if (scanf("%d%c", n, &x) == 2 && x == '\n' && *n <= NMAX) {
        for (int *p = a; p - a < *n; p++) {
            scanf("%d%c", p, &y);

            if ((y == '\n' && p - a < *n - 1) || (y != '\n' && p - a == *n - 1) || (y != '\n' && y != ' ')) {
                count = 0;
                break;
            } else
                count = 1;
        }
    }
    return count;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        if (p - a == n - 1)
            printf("%d", *p);
        else
            printf("%d ", *p);
    }
}
int max(int *a, int n) {
    int max = *a;
    for (int *p = a; p - a < n; p++) {
        if (max < *p) max = *p;
    }

    return max;
}

int min(int *a, int n) {
    int min = *a;
    for (int *p = a; p - a < n; p++) {
        if (min > *p) min = *p;
    }

    return min;
}

double mean(int *a, int n) {
    double mean = 0.0;
    for (int *p = a; p - a < n; p++) {
        mean += *p;
    }
    mean /= n;
    return mean;
}

double variance(int *a, int n) {
    double variance = 0;
    for (int *p = a; p - a < n; p++) {
        variance += (*p - mean(a, n)) * (*p - mean(a, n));
    }
    variance /= n;
    return variance;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}
