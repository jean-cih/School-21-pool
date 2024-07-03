#include <stdio.h>
#include <stdlib.h>

#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"

#if Macro
#include "../data_libs/data_io_macro.h"
#else
#include "../data_libs/data_io.h"
#endif

int main() {
#if Macro
    int n;
    scanf("%d", &n);
    double *data;
    data = malloc(n * sizeof(double));
#else
    const int n = 5;
    double data[n];
#endif

    printf("LOAD DATA...\n");
    input(data, n);

    printf("RAW DATA:\n\t");
    output(data, n);

    printf("\nNORMALIZED DATA:\n\t");
    normalization(data, n);
    output(data, n);

    printf("\nSORTED NORMALIZED DATA:\n\t");
    sort(data, n);
    output(data, n);

    printf("\nFINAL DECISION:\n\t");
    make_decision(data, n);
    output(data, n);

#if Macro
    free(data);
#endif

    return 0;
}
