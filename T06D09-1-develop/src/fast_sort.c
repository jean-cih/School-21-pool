#include <stdio.h>

#define N 10

int input(int *a);
void quickSort(int *a, int b, int e);
void pyramidal_sort(int *a, int root, int bottom);
void heapSort(int *a, int n);
void output(int *a);
void swap(int *a, int *b);

int main() {
    int data[N];
    if (input(data)) {
        quickSort(data, 0, N - 1);
        output(data);
        printf("\n");
        heapSort(data, N);
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

void quickSort(int *a, int b, int e) {
    int l = b, r = e;
    int piv = *(a + (l + r) / 2);
    while (l <= r) {
        while (a[l] < piv) l++;
        while (a[r] > piv) r--;
        if (l <= r) swap(&a[l++], &a[r--]);
    }
    if (b < r) quickSort(a, b, r);
    if (e > l) quickSort(a, l, e);
}

void pyramidal_sort(int *a, int root, int bottom) {
    int maxChild;
    int done = 0;

    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)
            maxChild = root * 2;

        else if (a[root * 2] > a[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;

        if (a[root] < a[maxChild]) {
            int temp = *(a + root);
            *(a + root) = *(a + maxChild);
            *(a + maxChild) = temp;
            root = maxChild;
        } else
            done = 1;
    }
}

void heapSort(int *a, int n) {
    for (int i = (n / 2); i >= 0; i--) pyramidal_sort(a, i, n - 1);
    for (int i = n - 1; i >= 1; i--) {
        swap(a, (a + i));
        pyramidal_sort(a, 0, i - 1);
    }
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
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
