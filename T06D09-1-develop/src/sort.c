#include <stdio.h>

#define N 10

int input(int *a);
void sort(int *a, int b, int e);
void output(int *a);
void swap(int *a, int *b);

int main() {
    int data[N];
    if (input(data)) {
        sort(data, 0, N - 1);
        output(data);
    } else
        printf("n/a");
    return 0;
}

int input(int *a) {
    char y;
    int count = 0;
    for (int *p = a; p - a < N; p++) {
        scanf("%d%c", p, &y);

        if ((y == '\n' && p - a < N - 1) || (y != '\n' && p - a == N - 1) || (y != '\n' && y != ' ')) {
            count = 0;
            break;
        } else
            count = 1;
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

void output(int *a) {
    for (int *p = a; p - a < N; p++) {
        if (p - a == N - 1)
            printf("%d", *p);
        else
            printf("%d ", *p);
    }
}

void swap(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
