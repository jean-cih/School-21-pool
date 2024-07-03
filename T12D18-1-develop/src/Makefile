CC = gcc

CFLAGS = -Wall -Werror -Wextra

C = -c

all: print_module documentation_module clean

print_module: print_module_test.o print_module.o
	$(CC) $(CFLAGS) main_module_entry_point.o print_module.o -o ../build/Quest_1

print_module_test.o: main_module_entry_point.c
	$(CC) $(CFLAGS) $(C) main_module_entry_point.c -D Quest_1

documentation_module: documentation_module_test.o documentation_module.o
	$(CC) $(CFLAGS) main_module_entry_point.o documentation_module.o -o ../build/Quest_2

documentation_module_test.o: main_module_entry_point.c
	$(CC) $(CFLAGS) $(C) main_module_entry_point.c -D Quest_2

clean:
	rm -rf *.o

rebuild: clean all

test: 
	clang-format -n *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c 
	leaks -atExit -- ./../build/Quest_1