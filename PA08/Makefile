CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
GCC = gcc $(CFLAGS) $(COVFLAGS)
OBJS = pa08.o solver.o path.o maze.o

pa08: $(OBJS)
	$(GCC) $(OBJS) -o pa08
pa08.o: pa08.c path.h maze.h solver.h
	$(GCC) -c -DREADMAZE_OFF -DFREEMAZE_OFF -DREADPATH_OFF -DCHECKPATH_OFF pa08.c -o pa08.o
path.o: path.c path.h maze.h solver.h
	$(GCC) -c -DREADMAZE_OFF -DFREEMAZE_OFF -DREADPATH_OFF -DCHECKPATH_OFF path.c -o path.o
maze.o: maze.c maze.h
	$(GCC) -c -DREADMAZE_OFF -DFREEMAZE_OFF -DREADPATH_OFF -DCHECKPATH_OFF maze.c -o maze.o
solver.o: solver.c solver.h
	$(GCC) -c solver.c -o solver.o

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

test: pa08
#	./pa08 inputs/maze1
#	./pa07 inputs/maze1 inputs/path1-bad1
#	./pa07 inputs/maze1 inputs/path1-bad2
#	./pa08 inputs/maze2
#	./pa07 inputs/maze2 inputs/path2-bad1
#	./pa08 inputs/maze3
#	./pa07 inputs/maze3 inputs/path3-bad1
#	./pa08 inputs/maze4 
#	./pa07 inputs/maze4 inputs/path4-bad1
	./pa08 inputs/maze5
#
memory: pa08
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa08 inputs/maze1
#	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa07 inputs/maze5
clean:
	/bin/rm -f *.o
	/bin/rm -f testgen
	/bin/rm -f *.gcda *gcno gmon.out *gcov
	/bin/rm -f pa08 pa08.prof
