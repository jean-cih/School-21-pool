#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log_levels.h"
#include "logger.h"

#define N 10
#define NMAX 100
#define SIZEOFBLOCK 128
#define SIZEOFCHAR 16
#define ROUNDS 16
#define SHIFTKEY 2

int input_key(int *key);
char *input_string();
void cipher_Caesar(int shift_key);
void recording(struct dirent *entry, int shift_key);
void cipher_DES(char *key);
void recording_des(struct dirent *entry, char *key);
char *binary_string(char *key);
char *cipher_xor(char *xor_string, char *string, char key);

int main(void) {
    int key = 0;
#ifdef logging_cipher
    FILE *log_file = log_init("../src/cipher.txt");
#endif
    while (1) {
        fflush(stdin);
        char *name_file;
#ifdef logging_cipher
        logcat(log_file, "Terminal input of integer", info);
#endif
        int keys = input_key(&key);
        if (keys && key == 1) {
#ifdef logging_cipher
            logcat(log_file, "Terminal input of string", info);
#endif
            char *files = input_string();
            name_file = files;
            FILE *file1 = fopen(files, "r");
            if (file1) {
#ifdef logging_cipher
                logcat(log_file, "Output content of the file", info);
#endif
                char sign;
                while ((sign = getc(file1)) != EOF) printf("%c", sign);
                printf("\n");

                fclose(file1);
            } else {
#ifdef logging_cipher
                logcat(log_file, "Incorrect input data", error);
#endif
                printf("n/a\n");
            }
        } else if (keys && key == 2) {
#ifdef logging_cipher
            logcat(log_file, "Terminal input of string", info);
#endif
            fflush(stdin);
            char *string = input_string();
            FILE *file1 = fopen(name_file, "r");
            if (file1) {
#ifdef logging_cipher
                logcat(log_file, "Recording in the file", info);
#endif
                fclose(file1);
                FILE *file2 = fopen(name_file, "a");
                putc('\n', file2);
                for (int i = 0; i < (int)strlen(string); i++) putc(string[i], file2);
#ifdef logging_cipher
                fclose(file2);
#endif
            } else {
#ifdef logging_cipher
                logcat(log_file, "Incorrect input data", error);
#endif
                printf("n/a\n");
            }

        } else if (keys && key == 3) {
#ifdef logging_cipher
            logcat(log_file, "The program needs integer", warning);
            logcat(log_file, "Output on terminal", info);
#endif
            printf("Shift key: ");
            int shift_key;
            char x;
            if (scanf("%d%c", &shift_key, &x) && (x == ' ' || x == '\n')) {
#ifdef logging_cipher
                logcat(log_file, "The file is encrypted cipher Caesar", debug);
#endif
                cipher_Caesar(shift_key);
            } else {
#ifdef logging_cipher
                logcat(log_file, "Incorrect input data", error);
#endif
                printf("n/a\n");
            }
        } else if (keys && key == 4) {
#ifdef logging_cipher
            logcat(log_file, "The program needs 1 - 4 letters", warning);
            logcat(log_file, "Output on terminal", info);
#endif
            printf("Shift key: ");
            char *key = input_string();
#ifdef logging_cipher
            logcat(log_file, "The file is encrypted DES", debug);
#endif
            cipher_DES(key);

            free(key);
        } else if (keys && key == -1) {
#ifdef logging_cipher
            logcat(log_file, "The program finished", info);
#endif
            break;
        } else {
#ifdef logging_cipher
            logcat(log_file, "Incorrect input data", error);
#endif
            printf("n/a\n");
        }
    }
#ifdef logging_cipher
    log_close(log_file);
#endif

    return 0;
}

int input_key(int *key) {
    char x;
    int count = 0;
    if (scanf("%d%c", key, &x) && (x == ' ' || x == '\n')) count = 1;

    return count;
}

char *input_string() {
    char *string = (char *)malloc(N * sizeof(char));
    char sign;
    int i = 0, j = 1;
    while (1) {
        scanf("%c", &sign);
        if (sign == '\n') break;
        if (i >= j * N) {
            j++;
            string = (char *)realloc(string, j * N);
        }
        string[i] = sign;
        i++;
    }

    return string;
}

void cipher_Caesar(int shift_key) {
    DIR *dir;
    struct dirent *entry;
    dir = opendir("../src/ai_modules/");
    if (!dir)
        perror("Directory is empty");
    else {
        while ((entry = readdir(dir)) != NULL) {
            recording(entry, shift_key);
        }
        closedir(dir);
    }
}

void recording(struct dirent *entry, int shift_key) {
    int k = 0;
    char path[NMAX] = "../src/ai_modules/";
    strcat(path, entry->d_name);
    int i = strlen(entry->d_name);
    if (entry->d_name[i - 2] == '.' && entry->d_name[i - 1] == 'c') {
        FILE *file_c1 = fopen(path, "r");

        char *sentence = (char *)malloc(sizeof(char));
        char sign;
        while ((sign = getc(file_c1)) != EOF) {
            if (sign != '\n') sign = (sign + shift_key) % 159;
            sentence[k] = sign;
            k++;
            sentence = (char *)realloc(sentence, k + 1);
        }
        fclose(file_c1);
        FILE *file_c2 = fopen(path, "w");

        for (int i = 0; i < k; i++) fputc(sentence[i], file_c2);

        free(sentence);
        fclose(file_c2);
    }
    if (entry->d_name[i - 2] == '.' && entry->d_name[i - 1] == 'h') {
        FILE *file_h = fopen(path, "w");
        fclose(file_h);
    }
}

void cipher_DES(char *key) {
    DIR *dir;
    struct dirent *entry;
    dir = opendir("../src/ai_modules/");
    if (!dir)
        perror("Directory is empty");
    else {
        while ((entry = readdir(dir)) != NULL) {
            recording_des(entry, key);
        }
        closedir(dir);
    }
}

void recording_des(struct dirent *entry, char *key) {
    int k = 0;
    char path[NMAX] = "../src/ai_modules/";
    strcat(path, entry->d_name);
    int i = strlen(entry->d_name);
    if (entry->d_name[i - 2] == '.' && entry->d_name[i - 1] == 'c') {
        FILE *file_c1 = fopen(path, "r");

        char *sentence = (char *)malloc(sizeof(char));
        char sign;
        while ((sign = getc(file_c1)) != EOF) {
            sentence[k] = sign;
            k++;
            sentence = (char *)realloc(sentence, k + 1);
        }
        fclose(file_c1);

        while ((k * sizeof(char)) % SIZEOFBLOCK != 0) {
            sentence[k] = '#';
            k++;
            sentence = (char *)realloc(sentence, k);
        }
        int blocks = (k * SIZEOFCHAR) / SIZEOFBLOCK;
        int length_block = k / blocks;
        char block_des[blocks][length_block];
        int h = 0;
        for (int i = 0; i < blocks; i++) {
            for (int j = 0; j < length_block; j++) {
                block_des[i][j] = sentence[h];
                h++;
            }
        }

        free(sentence);

        int key_size = strlen(key);
        while (length_block / 2 > (int)strlen(key)) {
            key_size++;
            key = (char *)realloc(key, key_size);
            key[key_size - 1] = '0';
        }
        char *binary_key = binary_string(key);

        char *str_l = (char *)malloc((length_block / 2) * sizeof(char));
        char *str_r = (char *)malloc((length_block / 2) * sizeof(char));

        FILE *file_c2 = fopen(path, "w");
        char xor_string[100];
        for (int j = 0; j < blocks; j++) {
            for (int i = 0; i < length_block / 2; i++) {
                str_l[i] = block_des[j][i];
                str_r[i + length_block / 2] = block_des[j][i + length_block / 2];
            }
            for (int i = 0; i < ROUNDS; i++) {
                fprintf(file_c2, "%s", cipher_xor(xor_string, str_l, binary_key[i]));
                fprintf(file_c2, "%s", cipher_xor(xor_string, str_r, binary_key[i]));
            }
            fputc('\n', file_c2);
        }
        free(str_l);
        free(str_r);
        free(binary_key);
        fclose(file_c2);
    }
    if (entry->d_name[i - 2] == '.' && entry->d_name[i - 1] == 'h') {
        FILE *file_h = fopen(path, "w");
        fclose(file_h);
    }
}

char *binary_string(char *key) {
    int code;
    char *binary_key = (char *)malloc(4 * 7 * sizeof(char));
    char *binary_buf = (char *)malloc(7 * sizeof(char));
    for (int j = 0; j < 4; j++) {
        int count = 6;
        code = (int)key[j];
        for (int i = 0; i < 7; i++) {
            binary_buf[count] = code % 2 + '0';
            code /= 2;
            count--;
        }
        strcat(binary_key, binary_buf);
    }

    free(binary_buf);

    return binary_key;
}

char *cipher_xor(char *xor_string, char *string, char key) {
    for (int i = 0; i < (int)strlen(string); i++) xor_string[i] = string[i] ^ key;

    return xor_string;
}
