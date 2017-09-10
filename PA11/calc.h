typedef struct StackNode
{
	float number;
	struct StackNode * next;
} StackNode;

typedef struct Stack
{
	StackNode * top;
} Stack;

Stack * buildStack();
float readInput(char * filename, Stack * stack, int * flag, int * flag2);
void push(StackNode** top, float value);
float pop(StackNode** top);
float calc(char operator, StackNode** top);
int checkNumber(char * number);
int numbers_required(char);
void freeNodes(Stack * stack);
