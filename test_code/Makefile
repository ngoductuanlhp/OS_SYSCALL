all: test.o get_proc_info.o
	gcc -o syscall get_proc_info.o test.o
test.o: test.c get_proc_info.h
	gcc -c test.c
get_proc_info.o: get_proc_info.h get_proc_info.c
	gcc -c get_proc_info.c
