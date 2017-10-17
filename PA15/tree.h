#ifndef TREE_H
#define TREE_H
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>

TreeNode * create_TNode(char character, int occur);
TreeNode * combine_TNodes(TreeNode * t1, TreeNode * t2);
int t_length(TreeNode * t);
//int t_lengthHelper(TreeNode * t, int length);
int t_leaf(TreeNode * t);
//int t_leafHelper(TreeNode * t, int * number);
//void convert(FILE * fptr, int character, unsigned char * bit1, unsigned char * bit2);
void t_header(TreeNode * t, unsigned int number, char * file);
//void t_header(TreeNode * t, char * file);
//void t_headerHelper(TreeNode * t, FILE * fptr, unsigned char * bit1, unsigned char * bit2);
void t_destroy(TreeNode * t);
void t_print(TreeNode * t, int  tier, FILE * fptr);

#endif
