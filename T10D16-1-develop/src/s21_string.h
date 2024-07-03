#ifndef S21_STRING_H
#define S21_STRING_H

int s21_strlen(const char *string);
int s21_strcmp(const char *string1, const char *string2);
char *s21_strcpy(char *string1, const char *string2);
char *s21_strcat(char *string1, const char *string2);
char *s21_strchr(const char *string, char c);
char *s21_strstr(char *string1, const char *string2);

#endif