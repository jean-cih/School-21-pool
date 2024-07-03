CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: state_sort state_search clear_state

state_sort:
	$(CC) $(GFLAGS) state_sort.c -o ../build/Quest_1

state_search:
	$(CC) $(GFLAGS) state_search.c -o ../build/Quest_2

clear_state:
	$(CC) $(GFLAGS) clear_state.c -o ../build/Quest_3

rebuild: all

clear:
	rm ../build/Quest_1
	rm ../build/Quest_2
	rm ../build/Quest_3