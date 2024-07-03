#include "s21_string.h"

#include <stdio.h>

void s21_strlen_test(char *a);
void s21_strcmp_test(char *a, char *b);
void s21_strcpy_test(char *a, char *b);
void s21_strcat_test(char *a, char *b);
void s21_strchr_test(char *a, char c);
void s21_strstr_test(char *a, char *b);

int main() {
#ifdef Quest_1
    s21_strlen_test("What are you up to?");
    s21_strlen_test("123");
    s21_strlen_test("\0");
#endif

#ifdef Quest_2
    s21_strcmp_test("What do you like", "What do you like");
    s21_strcmp_test("00", "\0");
    s21_strcmp_test("123", "321");
#endif

#ifdef Quest_3
    char a[100];
    char b[100];
    char c[100];
    char *a1 = "What do you like";
    char *b1 = "\0";
    char *c1 = "321";
    s21_strcpy_test(a, a1);
    s21_strcpy_test(b, b1);
    s21_strcpy_test(c, c1);
#endif

#ifdef Quest_4
    char *a2 = "What do you like";
    char *b2 = "\0";
    char *c2 = "321";
    char a22[100] = "What do you like ";
    char b22[100] = "b11 ";
    char c22[100] = "0000 ";
    s21_strcat_test(a22, a2);
    s21_strcat_test(b22, b2);
    s21_strcat_test(c22, c2);
#endif

#ifdef Quest_5
    s21_strchr_test("What is going on, bro?", 'i');
    s21_strchr_test("Let me get this straigh", '9');
    s21_strchr_test("", '0');
#endif

#ifdef Quest_6
    s21_strstr_test("What is going on, bro?", "going");
    s21_strstr_test("Let me get this straigh", "get");
    s21_strstr_test("Hello", "Hi");
#endif

    return 0;
}

void s21_strlen_test(char *a) {
    if (s21_strlen(a))
        printf("%s %d %s\n", a, s21_strlen(a), "SUCCESS");
    else
        printf("%s %d %s\n", a, s21_strlen(a), "FAIL");
}

void s21_strcmp_test(char *a, char *b) {
    if (s21_strcmp(a, b) == 0)
        printf("%s %s %d %s\n", a, b, s21_strcmp(a, b), "SUCCESS");
    else
        printf("%s %s %d %s\n", a, b, s21_strcmp(a, b), "FAIL");
}

void s21_strcpy_test(char *a, char *b) {
    s21_strcpy(a, b);
    if (*a == *b)
        printf("%s %s %s\n", a, b, "SUCCESS");
    else
        printf("%s %s %s\n", a, b, "FAIL");
}

void s21_strcat_test(char *a, char *b) {
    if (s21_strcat(a, b))
        printf("%s %s %s\n", a, b, "SUCCESS");
    else
        printf("%s %s %s\n", a, b, "FAIL");
}

void s21_strchr_test(char *a, char c) {
    if (s21_strchr(a, c))
        printf("%s %c %s\n", a, c, "SUCCESS");
    else
        printf("%s %c %s\n", a, c, "FAIL");
}

void s21_strstr_test(char *a, char *b) {
    if (s21_strstr(a, b))
        printf("%s %s %s\n", a, b, "SUCCESS");
    else
        printf("%s %s %s\n", a, b, "FAIL");
}
