#include "huffman.h"
#include "tree.h"
#include "list.h"
#include "bit.h"
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <values.h>

void buildHuffmanHelp(TreeNode * t, int * * huffman, int * row, int column)
{
	if(t == NULL)
	{
		return;
	}
	TreeNode * left = t -> left;
	TreeNode * right = t -> right;
	if((left == NULL) && (right == NULL))
	{
		huffman[*row][0] = t -> label;
		(* row) ++;
		return;
	}
	if(left != NULL)
	{
		int temp = t_leaf(left);
		int i;
		for(i = *row; i < (*row) + temp; i++)
		{
			huffman[i][column] = 0;
		}
		buildHuffmanHelp(left, huffman, row, column + 1);
	}
	if(right != NULL)
	{
		int temp = t_leaf(right);
		int i;
		for(i = *row; i < (*row) + temp; i++)
		{
			huffman[i][column] = 1;
		}
		buildHuffmanHelp(right, huffman, row, column + 1);
	}
}

void buildHuffman(TreeNode * root, int * * huffman)
{
	int row = 0;
	buildHuffmanHelp(root, huffman, &row, 1);
}

void printHuffman(int * * huffman, int row, FILE * Huff)
{
	int i;
	for(i = 0; i < row; i++)
	{
		fprintf(Huff, "%c:", huffman[i][0]);
		int j = 1;
		while(huffman[i][j] != -1)
		{
			fprintf(Huff, "%d", huffman[i][j]);
			j++;
		}
		fprintf(Huff, "\n");
	}
}

//void compress(char * in, char * out, int * * huffman, int * map)
//{
//	FILE * inptr = fopen(in, "r");
//	if(inptr == NULL)
//	{
//		return;
//	}
//	FILE * outptr = fopen(out, "a");
//	if(outptr == NULL)
//	{
//		fclose(outptr);
//		return;
//	}
//	unsigned char bit1 = 0;
//	unsigned char bit2 = 0;
//	while(! feof(inptr))
//	{
//		int ch = fgetc(inptr);
//		if(ch != EOF)
//		{
//			int i = map[ch];
//			int j = 1;
//			while(huffman[i][j] != -1)
//			{
//			//	fprintf(outptr, "%d", huffman[i][j]);
//			//	write(outptr, (huffman[i][j] == 1), &bit1, &bit2);
//				j++;
//			}
//		}
//	}
//	pad(outptr, &bit1, &bit2);
//	fclose(inptr);
//	fclose(outptr);
//	return;
//}

//void try(TreeNode * root, FILE * ptr)
//{
//	if(ptr == NULL);
//	{
//		fclose(ptr);
//		return;
//	}
//	if(root == NULL)
//	{
//		return;
//	}
//	if((root -> right == NULL) && (root -> left == NULL))
//	{
//		fprintf(ptr, "1");
//		fprintf(ptr, "%c", root -> label);
//	}
//	else
//	{
//		fprintf("0");
//	}
//	try(root -> left, ptr);
//	try(root -> right, ptr);
//}
