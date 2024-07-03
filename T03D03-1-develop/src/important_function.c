#include <math.h>
#include <stdio.h>

float function(float x);

int main(void) {
    float x;
    char y;

    if (scanf("%f%c", &x, &y) == 2 && x / 1 == x && (y == '\n' || y == ' '))
        printf("%.1f", function(x));
    else
        printf("n/a");

    return 0;
}

float function(float x) {
    return 7.0 * pow(10, -3) * powl(x, 4) + ((22.8 * powl(x, 1.0 / 3) - pow(10, 3)) * x + 3) / (x * x / 2) -
           x * powl(10 + x, 2.0 / x) - 1.01;
}