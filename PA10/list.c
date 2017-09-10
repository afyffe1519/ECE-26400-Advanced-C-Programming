#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/
int countTurns(char *);
bool Add(char *, char *);

PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {
	PathNode * temp = p -> head;
	while(p -> head != NULL)
	{
		temp = p -> head;
		p -> head = p -> head -> next;
		freeNode(temp);
	}
	free(p);
}

PathNode * buildNode(char * path) {
	
	PathNode * new = malloc(sizeof(PathNode));
	new -> next = NULL;
	new -> path = malloc((strlen(path) + 1) * sizeof(char));
	strcpy(new -> path, path);
	return new;
	
	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
}

void freeNode(PathNode * p) {
	if(p != NULL)
	{
		free(p -> path);
		free(p); 
	}
}

bool addNode(PathLL * paths, char * path) {
	
	bool exist = containsNode(paths, path);
	if(exist == true)
	{
		return false;
	}
	PathNode * new = buildNode(path);
	if(paths -> head == NULL)
	{
		paths -> head = new;
		new -> next = NULL;
		return true;
	}
	PathNode * temp = paths -> head;
	if(Add(path, temp -> path))
	{
		new -> next = temp;
		paths -> head = new;
		return true;
	}
	while((temp -> next) != NULL)
	{
		if(Add(path, temp -> next -> path))
		{
			new -> next = temp -> next;
			temp -> next = new;
			return true;
		}
		temp = temp -> next;
	}
	temp -> next = new;
	new -> next = NULL;
	return true;
}

bool removeNode(PathLL * paths, char * path) {
	bool exist = containsNode(paths, path);
	if(exist == false)
	{
		return false;
	}
	PathNode * temp = paths -> head;
	PathNode * prev;

	while(!strcmp(temp -> path, path) && temp != NULL)
	{
		paths -> head = temp -> next;
		free(temp);
		temp = paths -> head;
	}
	while(temp != NULL)
	{
		while(temp != NULL && (!strcmp(temp -> path, path)))
		{
			prev = temp;
			temp = temp -> next;
		}
		prev -> next = temp -> next;
		freeNode(prev);
		temp = prev -> next;
	}
	return true;
}

bool containsNode(PathLL * paths, char * path) {
	
	PathNode * temp = paths -> head;
	while(temp != NULL)
	{
		if(!strcmp(temp -> path, path))
		{
			return true;
		}
		temp = temp -> next;
	}
	return false;
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}

int countTurns(char * path)
{
	int count = 0;
	int i = 0;

	while(path[i + 1] != '\0')
	{
		if(path[i] != path[i + 1])
		{
			count++;
		}
		i++;
	}
	return count;
}

bool Add(char * path1, char * path2)
{
	bool first = false;
	bool second = false;
	bool third = false;

	first = (strlen(path2) > strlen(path1));
	second = (strlen(path1) == strlen(path2) && (countTurns(path1) < countTurns(path2)));
	third = (strlen(path1) == strlen(path2) && (countTurns(path1) == countTurns(path2)) && ((strcmp(path1, path2) < 0)));
	
	return(first || second || third);
}
