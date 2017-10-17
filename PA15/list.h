#ifndef LIST_H
#define LIST_H
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>

ListNode * build(Count * count);
ListNode * create_LNode(TreeNode * t);
ListNode * insert_LNode(ListNode * head, ListNode * l, int type);
int compare(const void * a, const void * b);
void sortCount(Count * count);
void l_print(ListNode * head, FILE * fptr);
#endif
