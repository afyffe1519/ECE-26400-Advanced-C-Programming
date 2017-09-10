CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
GCC = gcc $(CFLAGS) $(COVFLAGS)
OBJS = pa11.o calc.o

all: pa11 test

pa11: $(OBJS)
	$(GCC) $(OBJS) -o pa11
pa11.o: pa11.c calc.h
	$(GCC) -c pa11.c -o pa11.o
calc.o: calc.c calc.h
	$(GCC) -c calc.c -o calc.o

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

test: pa11
	./pa11 inputs/test1
	./pa11 inputs/test2
	./pa11 inputs/test3
	-./pa11 inputs/test4
	-./pa11 inputs/test5
memory: pa11
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa11 inputs/test1
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa11 inputs/test2
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa11 inputs/test3
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa11 inputs/test4
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa11 inputs/test5

clean:
	/bin/rm -f *.o
	/bin/rm -f testgen
	/bin/rm -f *.gcda *gcno gmon.out *gcov
	/bin/rm -f pa11 pa11.prof
