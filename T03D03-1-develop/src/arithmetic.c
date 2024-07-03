#include <stdio.h>

int sum(int a, int b);
int dif(int a, int b);
int mul(int a, int b);
int div(int a, int b);

int main() {
    int a, b;
    char y;
    if (scanf("%d%d%c", &a, &b, &y) == 3 && (y == ' ' || y == '\n')) {
        if (b == 0)
            printf("%d %d %d n/a", sum(a, b), dif(a, b), mul(a, b));
        else
            printf("%d %d %d %d", sum(a, b), dif(a, b), mul(a, b), div(a, b));
    } else
        printf("n/a");

    return 0;
}

int sum(int a, int b) { return a + b; }
int dif(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div(int a, int b) { return a / b; }