CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
GCC = gcc $(CFLAGS) $(COVFLAGS)
OBJS = pa10.o solver.o path.o maze.o mazehelper.o list.o

pa10: $(OBJS)
	$(GCC) $(OBJS) -o pa10
pa10.o: pa10.c list.h path.h maze.h solver.h mazehelper.h
	$(GCC) -c pa10.c -o pa10.o
solver.o: solver.c list.h path.h maze.h solver.h mazehelper.h
	$(GCC) -c solver.c -o solver.o
path.o: path.c list.h path.h maze.h solver.h mazehelper.h
	$(GCC) -c path.c -o path.o
maze.o: maze.c list.h path.h maze.h solver.h mazehelper.h
	$(GCC) -c maze.c -o maze.o
mazehelper.o: mazehelper.c list.h path.h maze.h solver.h mazehelper.h
	$(GCC) -c mazehelper.c -o mazehelper.o
list.o: list.c list.h path.h maze.h solver.h mazehelper.h
	$(GCC) -c list.c -o list.o

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

test: pa10
	./pa10 inputs/maze1 inputs/path1
	./pa10 inputs/maze2 inputs/path2
	./pa10 inputs/maze3 inputs/path3

memory: pa10
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa10 inputs/maze1 inputs/path1
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa10 inputs/maze2 inputs/path2
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa10 inputs/maze3 inputs/path3

clean:
	/bin/rm -f *.o
	/bin/rm -f testgen
	/bin/rm -f *.gcda *gcno gmon.out *gcov
	/bin/rm -f pa10 pa10.prof
