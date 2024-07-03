#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        squaring(data, n);
        output(data, n);
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
        if (p - a == n - 1) {
            printf("%d", *p);
            break;
        } else {
            printf("%d ", *p);
        }
    }
}

void squaring(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        *p = *p * *p;
    }
}
