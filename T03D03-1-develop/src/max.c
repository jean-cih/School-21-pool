#include <stdio.h>

int max(int a, int b);

int main(void) {
    int a, b;
    char y;

    if (scanf("%d%d%c", &a, &b, &y) == 3  && (y == ' ' || y == '\n'))
        printf("%d", max(a, b));
    else
        printf("n/a");

    return 0;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}