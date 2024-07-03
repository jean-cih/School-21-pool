CC = gcc

CFLAGS = -Wall -Werror -Wextra

C = -c

all: build data_stat.a build_with_static data_process.so build_with_macro build_with_dynamic clean

build: data_io.o data_stat.o data_process.o decision.o main_executable_module.o
	$(CC) ../data_libs/data_io.o ../data_libs/data_stat.o ../data_module/data_process.o ../yet_another_decision_module/decision.o main_executable_module.o -o ../../build/Quest_3

data_io.o: ../data_libs/data_io.c 
	$(CC) $(CFLAGS) $(C) ../data_libs/data_io.c -o ../data_libs/data_io.o

data_stat.o: ../data_libs/data_stat.c
	$(CC) $(CFLAGS) $(C)  ../data_libs/data_stat.c -o ../data_libs/data_stat.o

data_process.o: ../data_module/data_process.c
	$(CC) $(CFLAGS) $(C)  ../data_module/data_process.c  -o ../data_module/data_process.o

decision.o: ../yet_another_decision_module/decision.c 
	$(CC) $(CFLAGS) $(C)  ../yet_another_decision_module/decision.c -o ../yet_another_decision_module/decision.o

main_executable_module.o: main_executable_module.c 
	$(CC) $(CFLAGS) $(C)  main_executable_module.c -o main_executable_module.o

build_with_macro: data_io.o data_stat.o data_process.o decision.o data_io_macro.o
	$(CC) ../data_libs/data_io.o ../data_libs/data_stat.o ../data_module/data_process.o ../yet_another_decision_module/decision.o main_executable_module.o -o ../../build/Quest_4

data_io_macro.o: main_executable_module.c
	$(CC) $(CFLAGS) $(C)  main_executable_module.c -D Macro

data_stat.a:
	ar cr ../data_libs/data_stat.a ../data_libs/data_stat.o
	rm ../data_libs/data_stat.o

build_with_static: data_io.o data_stat.a data_process.o decision.o main_executable_module.o
	$(CC) ../data_libs/data_io.o ../data_libs/data_stat.a ../data_module/data_process.o ../yet_another_decision_module/decision.o main_executable_module.o -o ../../build/Quest_5

data_process.so:
	$(CC) -fPIC $(C) ../data_module/data_process.c -o ../data_module/process.o
	$(CC) -fPIC  $(C)  ../data_libs/data_stat.c -o ../data_libs/data_stat.o
	$(CC) -shared -o ../data_module/data_process.so ../data_module/data_process.o ../data_libs/data_stat.o

build_with_dynamic: data_io.o data_stat.o data_process.so decision.o main_executable_module.o
	$(CC) ../data_libs/data_io.o ../data_libs/data_stat.a ../data_module/data_process.so ../yet_another_decision_module/decision.o main_executable_module.o -o ../../build/Quest_6 -L../data_module -data_process -Wl,-rpath,../data_module/

clean:
	rm -rf *.o
	rm -rf ../data_libs/*.o
	rm -rf ../data_module/*.o
	rm -rf ../yet_another_decision_module/*.o

