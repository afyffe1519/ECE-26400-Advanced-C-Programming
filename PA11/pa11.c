#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments.\n");
		fprintf(stderr, "Usage: ./pa11 <input file>\n");		
		return EXIT_FAILURE;
	}
	
	float result; //store the result of your calculation here.
	Stack * stack = buildStack();
	int flag = 0;
	int flag2 = 0;
	result = readInput(argv[1], stack, &flag, &flag2);
	/* Insert code here to perform the RPN calculation.
	Don't forget to free any memory you allocate once you're done with it! */
	if(!flag2)
	{
		printf("%f\n", result);
	}
	freeNodes(stack);
	if(flag == 1)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
