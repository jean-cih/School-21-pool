#include "s21_string.h"

#include <stdio.h>

int s21_strlen(const char *string) {
    int i = 0;
    while (*string != '\0') {
        string++;
        i++;
    }

    return i;
}

int s21_strcmp(const char *string1, const char *string2) {
    while (*string1 == *string2 && *string1 != '\0') {
        string1++;
        string2++;
    }

    if (*string1 == '\0' && *string2 == '\0') return 0;

    if (*string1 > *string2)
        return 1;
    else
        return -1;
}

char *s21_strcpy(char *string1, const char *string2) {
    int i = 0;
    while (string2[i] != '\0') {
        string1[i] = string2[i];
        i++;
    }

    string1[i] = '\0';

    return string1;
}

char *s21_strcat(char *string1, const char *string2) {
    int len = s21_strlen(string1);

    for (int i = 0; string2[i] != '\0'; i++) string1[len + i] = string2[i];

    string1[len + s21_strlen(string2)] = '\0';

    return string1;
}

char *s21_strchr(const char *string, char c) {
    int i = 0;
    while (string[i] != '\0' && string[i] != c) ++i;

    return c == string[i] ? (char *)string + i : 0;
}

char *s21_strstr(char *string1, const char *string2) {
    int len = s21_strlen(string2);
    int k = 0, b = 0;
    char *first;
    for (int i = 0; string1[i] != '\0'; i++) {
        if (string1[i] == string2[b]) {
            first = &string1[i];
            b++;
            for (int j = i; string2[k] != '\0'; j++) {
                if (string1[j] == string2[k])
                    k++;
                else
                    break;
            }
            b = 0;
        }
    }
    if (k != len) first = 0;

    return (char *)first;
}