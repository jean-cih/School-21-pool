#include <math.h>
#include <stdio.h>

#define NMAX 30

int input(int *a, int *n);
int even(int a);
double mean(int *a, int n);
double variance(int *a, int n);
void finging(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        finging(data, n);
    } else
        printf("n/a");

    return 0;
}

int input(int *a, int *n) {
    char x, y;
    int count = 0;
    if (scanf("%d%c", n, &x) == 2 && (x == ' ' || x == '\n') && *n <= NMAX) {
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

int even(int a) {
    int count = 0;
    if (a % 2 == 0) {
        count++;
    }
    return count;
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

void finging(int *a, int n) {
    int count = 0;
    for (int *p = a; p - a < n; p++) {
        if (even(*p) && *p >= mean(a, n) && *p <= mean(a, n) + 3 * sqrt(variance(a, n)) && *p != 0) {
            printf("%d", *p);
            break;
        }
        count++;
    }
    if (count == n) printf("0");
}
