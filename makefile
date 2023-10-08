CC = gcc
CFLAGS = -c
OFLAGS = -o
GFLAGS = -g

alt: my_prog

main.o body.o crash_tests.o: main.c body.c crash_tests.c
	$(CC) $(CFLAGS) $(GFLAGS) main.c body.c crash_tests.c

my_prog: main.o body.o crash_tests.o
	$(CC) main.o body.o crash_tests.o $(OFLAGS) my_prog


clean:
	rm -rf *.o my_prog
