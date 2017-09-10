# You need to write this file so that
#
# "make" will create an executable called pa06
# 
# "make test" will run the three input files 
# 
# input: inputs/testinput1; output: id1, first1, last1
# input: inputs/testinput2; output: id2, first2, last2
# input: inputs/testinput3; output: id3, first3, last3
# 
# compare your program's output with the expected ouputs by
# using the "diff" command in Linux
#
# "make memory" calls valgrind to check memory errors
#
# "make clean" remove .o and all output files

CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
GCC = gcc $(CFLAGS) $(COVFLAGS)
OBJS = pa06.o msort.o student.o

pa06: $(OBJS)
	$(GCC) $(OBJS) -o pa06

pa06.o: pa06.c student.h constant.h msort.h
	$(GCC) -c -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME -DOMIT_MSORT pa06.c -o pa06.o

student.o: student.c student.h msort.h constant.h
	$(GCC) -c -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME -DOMIT_MSORT student.c -o student.o

msort.o: msort.c msort.h student.h constant.h
	$(GCC) -c -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME -DOMIT_MSORT msort.c -o msort.o

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

test: pa06
	./pa06 inputs/testinput1 id1 first1 last1
	./pa06 inputs/testinput2 id2 first2 last2
	./pa06 inputs/testinput3 id3 first3 last3

memory: pa06
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa06 inputs/testinput1 id1 first1 last1
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa06 inputs/testinput2 id2 first2 last2
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./pa06 inputs/testinput3 id3 first3 last3

clean:
	/bin/rm -f *.o
	/bin/rm -f testgen
	/bin/rm -f *.gcda *gcno gmon.out *gcov
	/bin/rm -f pa06 pa06.prof
