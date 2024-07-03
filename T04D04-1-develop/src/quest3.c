#include <stdio.h>

int fub(int n);

int main(void) {
    int n;
    char x;
    if (scanf("%d%c", &n, &x) == 2 && (x == ' ' || x == '\n'))
        printf("%d", fub(n));
    else
        printf("n/a");

    return 0;
}

int fub(int n) { return n < 2 ? n : fub(n - 1) + fub(n - 2); }