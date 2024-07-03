#include "data_io.h"

#include <stdio.h>

#include "data_io_macro.h"

void input(double *data, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%lf", &data[i]);
    }
}
void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lf", data[i]);
        if (i < n - 1) printf(" ");
    }
}