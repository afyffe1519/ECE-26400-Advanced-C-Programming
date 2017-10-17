#include "tree.h"
#include "bit.h"
#include <stdio.h>
#include <stdlib.h>

TreeNode * create_TNode(char character, int occur)
{
	TreeNode * t = malloc(sizeof(TreeNode));
	t -> left = NULL;
	t -> right = NULL;
	t -> label = character;
	t -> occur = occur;

	return t;
}

TreeNode * combine_TNodes(TreeNode * t1, TreeNode * t2)
{
	TreeNode * t = malloc(sizeof(TreeNode));
	t -> left = t1;
	t -> right = t2;
	t -> label = 0;
	t -> occur = (t1 -> occur) + (t2 -> occur);
	return t;
}

static int t_lengthHelper(TreeNode * t, int length)
{
	if(t == 0)
	{
		return length;
	}
	int left = t_lengthHelper(t -> left, length + 1);
	int right = t_lengthHelper(t -> right, length + 1);
	if(left < right)
	{
		return right;
	}
	return left;
}

int t_length(TreeNode * t)
{
	return t_lengthHelper(t,0);
}

static void t_leafHelper(TreeNode * t, int * number)
{
	if(t == 0)
	{
		return;
	}
	TreeNode * left = t -> left;
	TreeNode * right = t -> right;
	if((left == NULL) && (right == NULL))
	{
		(*number)++;
		return;
	}
	t_leafHelper(left, number);
	t_leafHelper(right, number);
}

int t_leaf(TreeNode * t)
{
	int number = 0;
	t_leafHelper(t, &number);
	return number;
}

static void convert1(FILE * fptr, int character, unsigned char * bit1, unsigned char * bit2)
{
	unsigned char mask = 0x80;
	while(mask > 0)
	{
		write(fptr, (character & mask) == mask, bit1, bit2);
		mask >>= 1;
	}
}

static void t_headerHelper(TreeNode * t, FILE * fptr, unsigned char * bit1, unsigned char * bit2)
{
	if(t == NULL)
	{
		return;
	}
	TreeNode * left = t -> left;
	TreeNode * right = t -> right;
	if((left == NULL) && (right == NULL))
	{
		write(fptr, 1, bit1, bit2);
		convert1(fptr, t -> label, bit1, bit2);
		return;
	}
	else
	{
		write(fptr, 0, bit1, bit2);
	}
	t_headerHelper(left, fptr, bit1, bit2);
	t_headerHelper(right, fptr, bit1, bit2);
}
//static void t_headerHelper(TreeNode * t, FILE * fptr)
//{
//	if(t == NULL)
//	{
//		return;
//	}
//	TreeNode * left = t -> left;
//	TreeNode * right = t -> right;
//	if((left == NULL) && (right == NULL))
//	{
//		fprintf(fptr, "1%c", t -> label);
//		return;
//	}
//	fprintf(fptr, "0");
//	t_headerHelper(left, fptr);
//	t_headerHelper(right, fptr);
//}

//void t_header(TreeNode * t, char * file)
//{
//	FILE * fptr = fopen(file, "w");
//	if(fptr == NULL)
//	{
//		return;
//	}
//	t_headerHelper(t, fptr);
//	fclose(fptr);
//}
void t_header(TreeNode * t, unsigned int number, char * file)
{
	FILE * fptr = fopen(file, "w");
	if(fptr == NULL)
	{
		return;
	}
	unsigned char bit1 = 0;
	unsigned char bit2 = 0;

	t_headerHelper(t, fptr, &bit1, &bit2);
	write(fptr, 0, &bit1, &bit2);
	pad(fptr, &bit1, &bit2);
	//fwrite(&number, sizeof(unsigned int), 1, fptr);
	unsigned char new = '\n';
	fwrite(&new, sizeof(unsigned char), 1, fptr);
	fclose(fptr);
}

void t_destroy(TreeNode * t)
{
	if(t == NULL)
	{
		return;
	}
	t_destroy(t -> left);
	t_destroy(t -> right);
	free(t);
}

void t_print(TreeNode * t, int tier, FILE * fptr)
{
	if(t == NULL)
	{
		return;
	}
	TreeNode * left = t -> left;
	TreeNode * right = t -> right;
	t_print(left, tier + 1, fptr);
	t_print(right, tier + 1, fptr);
	if((left == NULL) && (right == NULL))
	{
		fprintf(fptr, "%c:%d", t -> label, t -> occur);
	}
	fprintf(fptr,"\n");
}
