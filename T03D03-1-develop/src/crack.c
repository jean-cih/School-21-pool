#include <stdio.h>

int main(void) {
    double a, b;
    if (scanf("%lf%lf", &a, &b) == 2 && a / 1 == a && b / 1 == b) {
        if (a * a + b * b <= 25)
            printf("GOTCHA");
        else
            printf("MISS");
    } else
        printf("n/a");

    return 0;
}