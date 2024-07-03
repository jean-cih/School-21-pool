#include <stdio.h>

#define NMAX 10

int input(int *buffer, int *length);
void output(int *buffer, int length, int number);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

int main() {
    int data[NMAX];
    int second_data[NMAX];
    int n;
    char x;
    int number, count = 0;
    if (scanf("%d%c", &n, &x) == 2 && x == '\n' && n <= NMAX) {
        if (input(data, &n)) {
            number = sum_numbers(data, n);
            count = find_numbers(data, n, number, second_data);
        }
        if (count == 0)
            printf("n/a");
        else {
            output(second_data, count, number);
        }
    } else
        printf("n/a");

    return 0;
}

int input(int *buffer, int *lenght) {
    char y;
    int count = 0;
    for (int *p = buffer; p - buffer < *lenght; p++) {
        scanf("%d%c", p, &y);

        if ((y == '\n' && p - buffer < *lenght - 1) || (y != '\n' && p - buffer == *lenght - 1) ||
            (y != '\n' && y != ' ')) {
            count = 0;
            break;
        } else
            count = 1;
    }

    return count;
}

int sum_numbers(int *buffer, int length) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum += buffer[i];
        }
    }

    return sum;
}

int find_numbers(int *buffer, int length, int number, int *numbers) {
    int count = 0;
    for (int *p = buffer; p - buffer < length; p++) {
        if (*p != 0 && number % *p == 0) {
            *numbers = *p;
            numbers++;
            count++;
        }
    }
    return count;
}

void output(int *buffer, int length, int number) {
    printf("%d\n", number);
    for (int *p = buffer; p - buffer < length; p++) {
        if (p - buffer == length - 1)
            printf("%d", *p);
        else
            printf("%d ", *p);
    }
}