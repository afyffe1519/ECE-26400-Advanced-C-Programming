#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"
//typedef struct StackNode
//{
//	float number;
//	struct StackNode * next;
//} StackNode;

//typedef struct Stack
//{
//	StackNode * top;
//}Stack;

//Stack* buildStack();
//float readInput(char *);
//void push(Stack **, float);
//float pop(Stack **);
//float calc(char, Stack **);
//bool checkNumber(char *);
//int numbers_required(char);


Stack * buildStack()
{
	Stack * stack = malloc(sizeof(Stack));
	stack -> top = NULL;
	return stack;
}

float readInput(char * filename, Stack * stack, int * flag, int * flag2)
{
	FILE * fptr = fopen(filename, "r");
	float number1 = 0;
	int size = 0;
	char operation;
	//float result = 0;
	char number[256];
	int i = 0;
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen fail\n");
		*flag = 1;
		return 0;
	}
	fseek(fptr, 0, SEEK_END);
	long len = ftell(fptr);
	if(len <= 0)
	{
		fclose(fptr);
		*flag2 = 1;
		return 0;
	}
	else
	{
		rewind(fptr);
	}
	while(!feof(fptr))
	{
		fscanf(fptr, "%s ", number);
		i++;
		if(checkNumber(number))
		{
			number1 = atof(number);
			push(&(stack -> top), number1);
			++size;
		}
		else
		{
			operation = number[0];
			if(size < numbers_required(operation))
			{
				fprintf(stderr, "Too few arguments\n");
				*flag = 1;
				fclose(fptr);
				return 0;
			}
			push(&(stack -> top), calc(operation, &(stack -> top)));
			size -= numbers_required(operation) - 1;
		}
	}
	if(size != 1)
	{
		fprintf(stderr, "too many arguments\n");
		*flag = 1;
		fclose(fptr);
		return 0;
	}
	fclose(fptr);
	return stack -> top -> number;
}

void push(StackNode ** top, float value)
{
	StackNode * node = malloc(sizeof(StackNode));
	if(node != NULL)
	{
		node -> number = value;
		node -> next = *top;
		*top = node;
	}
	return;
}

float pop(StackNode ** top)
{
	if(*top != NULL)
	{
		StackNode * beginning = *top;
		float value = beginning -> number;
		*top = beginning -> next;
		free(beginning);
		return value;
	}
	return 0;
}


float calc(char operator, StackNode ** top)
{
	float temp;
	if(operator == '+')
	{
		return pop(top) + pop(top);
	}
	else if(operator == '*')
	{
		return pop(top) * pop(top);
	}
	else if(operator == '-')
	{
		temp = pop(top);
		return pop(top) - temp;
	}
	else
	{
		temp = pop(top);
		return pop(top) / temp;
	}
}

int numbers_required(char operator)
{
	switch(operator)
	{
		case '+': return 2;
		case '*': return 2;
		case '-': return 2;
		case '/': return 2;
		default: return 0;
	}
}

int checkNumber(char * number)
{
	for( ; *number; number++)
	{
		if(*number < '0' || *number > '9')
		{
			if(!strcmp(number, "-0") || (!strcmp(number, "+0")))
			{
				return 1;
			}
			if(*number != '.')
			{
				return 0;
			}
		}
	}

	return 1;
}

void freeNodes(Stack * stack)
{
	StackNode * temp;
	while(stack -> top != NULL)
	{
		temp = stack -> top;
		stack -> top = stack -> top -> next;
		free(temp);
	}
	free(stack);
}
