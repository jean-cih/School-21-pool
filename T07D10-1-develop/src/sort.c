#include <stdio.h>
#include <stdlib.h>

int input_first(int *n);
int input(int *a, int n);
void sort(int *a, int left, int right);
void output(int *a, int n);
void swap(int *a, int *b);

int main() {
    int n;
    if (input_first(&n)) {
        int *data = (int *)malloc(n * sizeof(int));
        if (input(data, n)) {
            sort(data, 0, n - 1);
            output(data, n);
        } else
            printf("n/a");

        free(data);
    } else
        printf("n/a");

    return 0;
}

int input_first(int *n) {
    char x;
    int count = 0;
    if (scanf("%d%c", n, &x) == 2 && x == '\n' && x != ' ') count = 1;

    return count;
}

int input(int *a, int n) {
    char x;
    int count = 0;
    for (int *p = a; p - a < n; p++) {
        if (scanf("%d%c", p, &x) == 2) {
            count = 1;

            if ((x != ' ' && p - a < n - 1) || (x != '\n' && p - a == n - 1) || (x != ' ' && x != '\n')) {
                count = 0;
                break;
            } else
                count = 1;
        }
    }
    return count;
}

void sort(int *a, int b, int e) {
    int l = b, r = e;
    int piv = *(a + (l + r) / 2);
    while (l <= r) {
        while (a[l] < piv) l++;
        while (a[r] > piv) r--;
        if (l <= r) swap(&a[l++], &a[r--]);
    }
    if (b < r) sort(a, b, r);
    if (e > l) sort(a, l, e);
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        if (p - a == n - 1)
            printf("%d", *p);
        else
            printf("%d ", *p);
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}