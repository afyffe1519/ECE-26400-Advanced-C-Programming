#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

//#ifndef BUILDTREE_OFF
TreeNode * buildExpressionTree(Scanner * s) {

	Token token = nextToken(s);
	TreeNode * temp;
	if(token.type == T_VAL)
	{
		temp = buildTreeNode(token);
		return temp;
	}
	else if(token.type == T_LPAREN)
	{
		temp = buildTreeNode(token);
		temp -> left = buildExpressionTree(s);
		token = nextToken(s);
		temp -> t = token;
		temp -> right = buildExpressionTree(s);
		token = nextToken(s);
		return temp;
	}
	else if(token.type == T_ADD)
	{
		temp = buildTreeNode(token);
		temp -> t.type = T_ADD;
		temp -> right = buildExpressionTree(s);
	}
	else if(token.type == T_SUB)
	{
		temp = buildTreeNode(token);
		return temp;
	}
	else if(token.type == T_MUL)
	{
		temp = buildTreeNode(token);
		return temp;
	}
	else if(token.type == T_DIV)
	{
		temp = buildTreeNode(token);
		return temp;
	}
	else if(token.type == T_RPAREN)
	{
		temp = buildTreeNode(token);
		return temp;
	}

	return NULL;
}
//#endif

//#ifndef POSTFIX_OFF
void makePostFix(TreeNode * t, FILE * fptr) {
	if(t != NULL)
	{
		makePostFix(t -> left, fptr);
		makePostFix(t -> right, fptr);
		if(t -> t.type == T_VAL)
		{
			fprintf(fptr, "%f ", t -> t.value);
		}
		else
		{
			fprintf(fptr, "%c ", t -> t.type);
		}
	}
}
//#endif
