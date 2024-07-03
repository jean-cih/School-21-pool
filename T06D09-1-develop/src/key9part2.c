#include <stdio.h>

#define LEN 100

int input1(int *buff1);
int input2(int *buff1);
void output(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
// void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);

int main() {
    int buff1[LEN];
    int buff2[LEN];
    int result[LEN];
    int len1, len2, result_length = 0;
    len1 = input1(buff1);
    len2 = input2(buff2);
    sum(buff1, len1, buff2, len2, result, &result_length);
    // sub(buff1, len1, buff2, len2, result, &result_length);
    output(buff1, len1, buff2, len2, result, &result_length);
}

int input1(int *buff1) {
    char x;
    int len1 = 0;
    for (int *p = buff1; p - buff1 < LEN; p++) {
        scanf("%d%c", p, &x);
        if (x == '\n') break;
        len1++;
    }
    return len1;
}
int input2(int *buff2) {
    char y;
    int len2 = 0;
    for (int *b = buff2; b - buff2 < LEN; b++) {
        scanf("%d%c", b, &y);
        if (y == '\n') break;
        len2++;
    }
    return len2;
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int count = 0;

    for (int i = len1, j = len2; j >= 0; i--, j--) {
        if (buff1[i] + buff2[j] >= 10) {
            result[i] += (buff1[i] + buff2[j]) % 10;
            result[i - 1] += 1;
        } else
            result[i] = buff1[i] + buff2[j];
        count++;
        len1--;
        if (len2 > 0) len2--;
    }
    *result_length = count;

    for (int i = len1; i >= 0; i--) {
        printf("%d ", result[i]);
    }
}
/*
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length){

}
*/

void output(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    for (int *p = buff1; p - buff1 <= len1; p++) {
        printf("%d ", *p);
    }
    printf("\n");
    for (int *b = buff2; b - buff2 <= len2; b++) {
        printf("%d ", *b);
    }
    printf("\n");
    for (int *c = result; c - result <= *result_length; c++) {
        printf("%d ", *c);
    }
}