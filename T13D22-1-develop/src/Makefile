CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: cipher logging_cipher

cipher:
	$(CC) $(CFLAGS) cipher.c -o ../build/cipher

logging_cipher:
	$(CC) $(CFLAGS) cipher.c logger.c -D logging_cipher -o ../build/logging_cipher

rebuild: clean all

clean_quest:
	rm ../build/cipher
	rm ../build/logging_cipher

test:
	clang-format -n *.c *.h
	leaks -atExit -- ./../build/cipher
	leaks -atExit -- ./../build/logging_cipher

