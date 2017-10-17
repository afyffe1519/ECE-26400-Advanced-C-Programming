#ifndef PA15_H
#define PA15_H		 

#define ASCII_SIZE 256
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
   char label;
   int occur;
   struct TreeNode *left;
   struct TreeNode *right;
} TreeNode;

typedef struct ListNode {
   TreeNode *ptr;
   struct ListNode *next;
} ListNode;

typedef struct
{
	char character;
	int occur;
} Count;

void buildHuffmanHelp(TreeNode * t, int * * huffman, int * row, int column);
void buildHuffman(TreeNode * root, int * * huffman);
void printHuffman(int * * huffman, int row, FILE * Huff);
void compress(char * in, char * out, int * * huffman, int * map);
//void try(TreeNode * root, FILE * ptr);
#endif
