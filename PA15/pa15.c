#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "huffman.h"
#include "list.h"
#include "tree.h"
#include "bit.h"
/* count the occurrences in a file */

int countLetters(FILE *fp, Count * asciiCount)
{
   int temp = 0;
   int ch;
   fseek(fp, 0, SEEK_SET);
   while ((ch = fgetc(fp)) != EOF) {
   	  temp++;
      asciiCount[ch].character = (char) ch;
	  (asciiCount[ch].occur)++;
   }
   return temp;
}

static ListNode * combine_LNodes(ListNode * head, int num)
{
	ListNode * head2 = head -> next;
	ListNode * head3 = head2 -> next;
	
	TreeNode * t1 = head -> ptr;
	TreeNode * t2 = head2 -> ptr;
	TreeNode * merge;
	free(head);
	free(head2);
	head = head3;
	if(num == 0)
	{
		merge = combine_TNodes(t1, t2);
	}
	else
	{
		merge = combine_TNodes(t2,t1);
	}
	ListNode * l = create_LNode(merge);
	head = insert_LNode(head, l, 0);
	return head;
}

static TreeNode * convert(ListNode * head)
{
	while((head -> next) != NULL)
	{
		head = combine_LNodes(head, 0);
	}
	TreeNode * root = head -> ptr;
	free(head);
	return root;
}

//static ListNode * combine_LNodes(ListNode * head)
//{
//	ListNode * head2 = head -> next;
//	ListNode * head3 = head2 -> next;
//	
//	TreeNode * t1 = head -> ptr;
//	TreeNode * t2 = head2 -> ptr;
//
//	free(head);
//	free(head2);
//	head = head3;
//	merge = combine_TNodes(t1, t2);
//	ListNode * l = create_LNode(merge);
//	head = insert_LNode(head, l, 2);
//	return head;
//}

int main(int argc, char **argv)
{
   if (argc != 5) {
    printf("Not enough arguments");
    return EXIT_FAILURE;
   }
   FILE * inFile = fopen(argv[1], "r");
   FILE * Sort = fopen(argv[2], "w");
   FILE * Huff = fopen(argv[3], "w");
   if (inFile == NULL) {
      fprintf(stderr, "can't open the input file.  Quit.\n");
      return EXIT_FAILURE;
   }
   Count asciiCount[ASCII_SIZE];
   bzero(asciiCount, sizeof(Count) * ASCII_SIZE);
   /* read and count the occurrences of characters */
   unsigned int number = countLetters(inFile, asciiCount);
   //countLetters(inFile, asciiCount);
   fclose(inFile);

   if (asciiCount == NULL) {
      fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");

      return EXIT_FAILURE;
   }
   sortCount(asciiCount);
   ListNode * head = build(asciiCount);
   l_print(head, Sort);
   fclose(Sort);
   if(head == NULL)
   {
   	 return EXIT_FAILURE;
   }
   TreeNode * root = convert(head);
   int row = t_leaf(root);
   int column = t_length(root);
   column++;
   int * * huffman = malloc(sizeof(int*) * row);
   int i;
   for(i = 0; i < row; i++)
   {
   	 huffman[i] = malloc(sizeof(int) * column);
	 int j;
	 for(j = 0; j < column; j++)
	 {
	 	huffman[i][j] = -1;
	 }
   }
   buildHuffman(root, huffman);
   printHuffman(huffman, row, Huff);
   fclose(Huff);
   //t_header(root, argv[4]); 
   int map[ASCII_SIZE];
   int i2;
   for(i2 = 0; i2 < ASCII_SIZE; i2++)
   {
   	 map[i2] = -1;
	 int j2;
	 for(j2 = 0; j2 < row; j2++)
	 {
	 	if(huffman[j2][0] == i2)
		{
			map[i2] = j2;
		}
	 }
   }
   t_header(root, number, argv[4]);
   //t_header(root, argv[4]);
   //compress(argv[1], argv[4], huffman, map);
   for(i2 = 0; i2 < row; i2++)
   {
   	 free(huffman[i2]);
   }
   free(huffman);

   t_destroy(root);
   return EXIT_SUCCESS;
}

//static TreeNode * convert(ListNode * head)
//{
//	while((head -> next) != NULL)
//	{
//		l_print(head);
//		head = combine_TNodes(head, 0);
//	}
//	l_print(head);
//	TreeNode * root = head -> ptr;
//	free(head);
//	return root;
//}
