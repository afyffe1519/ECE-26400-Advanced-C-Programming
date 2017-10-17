#include "list.h"
#include "tree.h"
#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>

int compare(const void * a, const void * b)
{
	const Count * c = (const Count *) a;
	const Count * d = (const Count *) b;
	const int e = c -> occur;
	const int f = d -> occur;
	return(e - f);
}

void sortCount(Count * count)
{
	qsort(count, ASCII_SIZE, sizeof(Count), compare);
}

ListNode * create_LNode(TreeNode * t)
{
	ListNode * l = malloc(sizeof(ListNode));
	l -> next = NULL;
	l -> ptr = t;
	return l;
}

ListNode * build(Count * count)
{
	int i = 0;
	while(count[i].occur == 0)
	{
		i++;
	}
	if(i == ASCII_SIZE)
	{
		return NULL;
	}
	ListNode * head = NULL;
	while(i < ASCII_SIZE)
	{
		TreeNode * t = create_TNode(count[i].character, count[i].occur);
		ListNode * l = create_LNode(t);
		head = insert_LNode(head, l, 0);
		i++;
	}
	return head;
}


ListNode * insert_LNode(ListNode * head, ListNode * l, int type)
{
	if(head == NULL)
	{
		return l;
	}
	if(type == 1)
	{
		l -> next = head;
		return l;
	}
	if(type == 2)
	{
		head -> next = insert_LNode(head -> next, l, type);
		return head;
	}

	int count1 = head -> ptr -> occur;
	int count2 = l -> ptr -> occur;
	if(count1 > count2)
	{
		l -> next = head;
		return l;
	}

	head -> next = insert_LNode(head -> next, l, type);
	return head;
}

void l_print(ListNode * head, FILE * fptr)
{
	if(head == NULL)
	{
		return;
	}
	t_print(head -> ptr, 0, fptr);
	l_print(head -> next, fptr);
}
