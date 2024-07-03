#include <stdio.h>

#define NMAX 10

int input(int *n, int *a, int *c);
void shift(int *a, int n);
void shift_left(int *a, int n, int c);
void shift_right(int *a, int n, int c);
void output(int *a, int n);

int main() {
    int n, c;
    int A[NMAX];
    if (input(&n, A, &c)) {
        if (c >= 0)
            shift_left(A, n, c);
        else
            shift_right(A, n, c);
        output(A, n);
    } else
        printf("n/a");
}

int input(int *n, int *a, int *c) {
    char x, y;
    int count = 0;
    if (scanf("%d%c", n, &x) == 2 && x == '\n' && n != 0) {
        count += 1;
        for (int *p = a; p - a < *n; p++) {
            scanf("%d", p);
        }
        if (scanf("%d%c", c, &y) == 2 && y == '\n') {
            count += 1;
        } else
            count = 0;
    } else
        count = 0;

    return count;
}

void shift(int *a, int n) {
    int first = a[0];

    for (int i = 1; i < n; ++i) a[i - 1] = a[i];

    a[n - 1] = first;
}

void shift_left(int *a, int n, int c) {
    c %= n;
    for (int i = 0; i < c; ++i) shift(a, n);
}

void shift_right(int *a, int n, int c) {
    c *= -1;
    c %= n;
    c = n - c;
    for (int i = 0; i < c; ++i) shift(a, n);
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        if (p - a == n - 1)
            printf("%d", *p);
        else
            printf("%d ", *p);
    }
}