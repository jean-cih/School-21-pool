CC = gcc

CFLAGS = -Wall -Werror -Wextra

C = -c

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests clean

strlen_tests: s21_string.o s21_strlen_tests.o
	$(CC) $(CFLAGS) s21_string.o s21_string_test.o -o ../build/Quest_1

s21_strlen_tests.o: s21_string_test.c
	$(CC) $(CFLAGS) $(C) s21_string_test.c -D Quest_1

strcmp_tests: s21_string.o s21_strcmp_tests.o
	$(CC) $(CFLAGS) s21_string.o s21_string_test.o -o ../build/Quest_2

s21_strcmp_tests.o: s21_string_test.c
	$(CC) $(CFLAGS) $(C) s21_string_test.c -D Quest_2

strcpy_tests: s21_string.o s21_strcpy_tests.o
	$(CC) $(CFLAGS) s21_string.o s21_string_test.o -o ../build/Quest_3

s21_strcpy_tests.o: s21_string_test.c
	$(CC) $(CFLAGS) $(C) s21_string_test.c -D Quest_3

strcat_tests: s21_string.o s21_strcat_tests.o
	$(CC) $(CFLAGS) s21_string.o s21_string_test.o -o ../build/Quest_4

s21_strcat_tests.o: s21_string_test.c
	$(CC) $(CFLAGS) $(C) s21_string_test.c -D Quest_4

strchr_tests: s21_string.o s21_strchr_tests.o
	$(CC) $(CFLAGS) s21_string.o s21_string_test.o -o ../build/Quest_5

s21_strchr_tests.o: s21_string_test.c
	$(CC) $(CFLAGS) $(C) s21_string_test.c -D Quest_5

strstr_tests: s21_string.o s21_strstr_tests.o
	$(CC) $(CFLAGS) s21_string.o s21_string_test.o -o ../build/Quest_6

s21_strstr_tests.o: s21_string_test.c
	$(CC) $(CFLAGS) $(C) s21_string_test.c -D Quest_6

s21_string.o: s21_string.c 
	$(CC) $(CFLAGS) -c s21_string.c

clean:
	rm -rf *.o

clean_quest:
	rm ../build/Quest_1
	rm ../build/Quest_2
	rm ../build/Quest_3
	rm ../build/Quest_4
	rm ../build/Quest_5
	rm ../build/Quest_6
