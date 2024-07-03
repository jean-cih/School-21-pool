CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: build_db

build_db:
	$(CC) $(CFLAGS) shared.c modules_db.c db_levels.c db_modules.c db_status_events.c -o ../build/Quest_1

clean:
	rm -rf ../build/Quest_1
