#include "print_module.h"

#include <stdio.h>
#include <time.h>

char print_char(char ch) { return putchar(ch); }

void print_log(char (*print)(char), char *message) {
    time_t nowTime = time(NULL);
    char *time_string = ctime(&nowTime);
    time_string[s21_strlen(time_string) - 1] = '\0';

    for (int i = 5; i < 20; i++) {
        if (i < 10)
            print(Log_prefix[i - 5]);
        else if (i == 10 || i == 19)
            print(' ');
        else if (i == 13 || i == 16)
            print(':');
        else
            print(time_string[i]);
    }
    int i = 0;
    while (message[i] != '\0') {
        print(message[i]);
        i++;
    }
}

int s21_strlen(const char *string) {
    int i = 0;
    while (*string != '\0') {
        string++;
        i++;
    }

    return i;
}