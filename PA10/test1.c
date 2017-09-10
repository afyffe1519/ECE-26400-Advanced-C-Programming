#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main()
{
	PathLL * paths;
	paths -> head = NULL;
	char * path = "nw";
	addNode(paths, path);
	PathNode * temp = paths -> head;
	while(temp != NULL)
	{
		printf("%s\n", temp -> path);
		temp = temp -> next;
	}
}
