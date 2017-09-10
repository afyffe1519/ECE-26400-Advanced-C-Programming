#include "linkedlist.h"
#include "answer09.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * * argv)
{

	//THIS IS JUST SAMPLE CODE FOR TESTING. YOU WILL HAVE TO BUILD YOUR OWN
	//TEST CASES

	//Build one or more linked lists here
	node_t * head = NULL;
	node_t * tail = NULL;
	int i;
	for(i = 0; i < 4; i++)
	{
		tail = insert(&head, i, i);
	}
	//head -> next -> next -> next -> next = head;
	bool circular = false;
	circular = isCircular(head);
	if (circular == true)
	{
		printf("Loop found");
	}
	else
	{
		printf("No loop");
	}
	//Check to see if the lists you have built are circular
	//bool result = isCircular(head);
	
	/* More testing ... */
	return EXIT_SUCCESS;
}
