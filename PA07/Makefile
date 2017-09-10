CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
GCC = gcc $(CFLAGS) $(COVFLAGS)
OBJS = pa07.o path.o maze.o

pa07: $(OBJS)
	$(GCC) $(OBJS) -o pa07
pa07.o: pa07.c path.h maze.h
	$(GCC) -c -DREADMAZE_OFF -DFREEMAZE_OFF -DREADPATH_OFF -DCHECKPATH_OFF pa07.c -o pa07.o
path.o: path.c path.h maze.h
	$(GCC) -c -DREADMAZE_OFF -DFREEMAZE_OFF -DREADPATH_OFF -DCHECKPATH_OFF path.c -o path.o
maze.o: maze.c maze.h
	$(GCC) -c -DREADMAZE_OFF -DFREEMAZE_OFF -DREADPATH_OFF -DCHECKPATH_OFF maze.c -o maze.o

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

test: pa07
	./pa07 inputs/maze1 inputs/path1
	./pa07 inputs/maze1 inputs/path1-bad1
	./pa07 inputs/maze1 inputs/path1-bad2
	./pa07 inputs/maze2 inputs/path2
	./pa07 inputs/maze2 inputs/path2-bad1
	./pa07 inputs/maze3 inputs/path3
	./pa07 inputs/maze3 inputs/path3-bad1
	./pa07 inputs/maze4 inputs/path4
	./pa07 inputs/maze4 inputs/path4-bad1
	./pa07 inputs/maze5 inputs/path5
#
memory: pa07
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa07 inputs/maze1 inputs/path1
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa07 inputs/maze5 inputs/path5
clean:
	/bin/rm -f *.o
	/bin/rm -f testgen
	/bin/rm -f *.gcda *gcno gmon.out *gcov
	/bin/rm -f pa07 pa07.prof
