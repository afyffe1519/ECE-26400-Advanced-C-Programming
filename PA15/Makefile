CFLAGS = -g -Wall -Wshadow
GCC = gcc $(CFLAGS)

OBJS = pa15.c tree.c huffman.c list.c bit.c
VALGRIND = valgrind --leak-check=full --tool=memcheck

all: pa15 test1 test2 test3 test4 test5

pa15: $(OBJS)
		$(GCC) $(OBJS) -o pa15

test1: pa15	
	./pa15 inputs/basic basic_sorted basic_huffman basic_header
	
	$(VALGRIND) ./pa15 inputs/basic basic_sorted basic_huffman basic_header

	diff basic_sorted expected/basic_sorted
	diff basic_huffman expected/basic_huffman
	#diff basic_header expected/basic_header

test2: pa15	
	./pa15 inputs/gophers gophers_sorted gophers_huffman gophers_header
	
	$(VALGRIND) ./pa15 inputs/gophers gophers_sorted gophers_huffman gophers_header
	
	diff gophers_sorted expected/gophers_sorted
	diff gophers_huffman expected/gophers_huffman
	#diff gophers_header expected/gophers_header

test3: pa15
	./pa15 inputs/para para_sorted para_huffman para_header
	
	$(VALGRIND) ./pa15 inputs/para para_sorted para_huffman para_header
	
	diff para_sorted expected/para_sorted
	diff para_huffman expected/para_huffman
	#diff para_header expected/para_header

test4: pa15
	./pa15 inputs/prideandprejudice prideandprejudice_sorted prideandprejudice_huffman prideandprejudice_header
	
	$(VALGRIND) ./pa15 inputs/prideandprejudice prideandprejudice_sorted prideandprejudice_huffman prideandprejudice_header
	
	diff prideandprejudice_sorted expected/prideandprejudice_sorted
	diff prideandprejudice_huffman expected/prideandprejudice_huffman
	#diff prideandprejudice_header expected/prideandprejudice_header

test5: pa15
	./pa15 inputs/woods woods_sorted woods_huffman woods_header
	$(VALGRIND) ./pa15 inputs/woods woods_sorted woods_huffman woods_header

	diff woods_sorted expected/woods_sorted
	diff woods_huffman expected/woods_huffman
	#diff woods_header expected/woods_header
.c.o:
		$(GCC) $(CFLAGS) -c $* .c

clean:
		/bin/rm -f *.o
		/bin/rm -f testgen
		/bin/rm -f *.gcda *gcno gmon.out *gcov
		/bin/rm -f pa15 pa15.prof
