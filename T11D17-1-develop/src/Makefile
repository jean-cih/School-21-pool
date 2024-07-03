CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: door_struct list_test clean

door_struct: dmanager_module.o
	$(CC) $(CFLAGS) dmanager_module.o -o ../build/Quest_1

list_test: list.o list_test.o
	$(CC) $(CFLAGS) list.o list_test.o -o ../build/Quest_2

clean:
	rm -rf *.o

test:
	clang-format -n *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem list_test.c dmanager_module.c
	leaks -atExit -- ./../build/Quest_1
	leaks -atExit -- ./../build/Quest_2