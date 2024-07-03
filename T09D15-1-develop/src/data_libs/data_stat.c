#include "data_stat.h"

double max(double *data, int n) {
    double max;
    for (int i = 0; i < n; i++) {
        if (data[i] > max) max = data[i];
    }
    return max;
}
double min(double *data, int n) {
    double min;
    for (int i = 0; i < n; i++) {
        if (data[i] < min) min = data[i];
    }
    return min;
}
double mean(double *data, int n) {
    double mean = 0;
    for (int i = 0; i < n; i++) {
        mean += data[i];
    }
    mean = mean / (n);
    return mean;
}
double variance(double *data, int n) {
    double var;
    for (int i = 0; i < n; i++) {
        var += (data[i] - mean(data, n)) * (data[i] - mean(data, n)) / (n);
    }
    return var;
}