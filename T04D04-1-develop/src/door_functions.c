#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define DIF 0.1532484

double v_a(double x);
double l_b(double x);
double gip(double x);

int main(void) {
    FILE *file = fopen("data/door_data.txt", "w");

    for (double i = -PI; i <= PI; i += DIF)
        if (sqrt(1 + 4 * i * i) >= i * i + 1)
            fprintf(file, "%.7lf | %.7lf | %.7lf | %.7lf\n", i, v_a(i), l_b(i), gip(i));
        else
            fprintf(file, "%.7lf | %.7lf | - | %.7lf\n", i, v_a(i), gip(i));
    fclose(file);

    return 0;
}

double v_a(double x) { return 1 / (1 + x * x); }
double l_b(double x) { return sqrt(sqrt(1 + 4 * x * x) - x * x - 1); }
double gip(double x) { return 1 / x / x; }