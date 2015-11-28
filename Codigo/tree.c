/******************************************************************************
 *
 * File Name: tree.c
 *	      (c) 2010 AED
 * Author:    AED team
 * Revision:  v2.3 ACR
 *            v3.0 AED Team Out 2013
 *
 * NAME
 *     Tree - different forms of tree sweep
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <malloc.h>
 *
 * DESCRIPTION
 *		implements tree auxiliary functions
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include "tree.h"
#include "queue.h"

struct _Node{
  int value;
  struct _Node *left, *right;
};

/******************************************************************************
 * AllocNode()
 *
 * Arguments: (none)
 * Returns: new node
 * Side-Effects: none
 *
 * Description: allocates space for a new node
 *
 *****************************************************************************/


Node *AllocNode() {
  return ((Node *) malloc(sizeof(Node)));
}


/******************************************************************************
 * NewNode()
 *
 * Arguments: integer
 * Returns: new node
 * Side-Effects: none
 *
 * Description: creates a new node with a integer value
 *
 *****************************************************************************/

Node *NewNode(int num)
{
    Node *aux;
    
    if (num==-1)
        return NULL;
    
    aux = AllocNode();
    aux->value = num;
    aux->right = aux->left = NULL;
    
    return aux;
}

/******************************************************************************
 * Construct()
 *
 * Arguments: input file and filename
 * Returns: pointer to root node of the tree
 * Side-Effects: none
 *
 * Description: constructs a tree reading integer numbers from file
 *
 *****************************************************************************/

Node *Construct(FILE *fp, char * filename)
{
    Node *nodeRoot;
    int num;
    
    if (fscanf(fp,"%d", &num) == EOF)
    {
        fprintf(stderr, "File %s has an insufficient number of values.  Please correct.\n", filename);
        exit(0);
    }
    
    if ((nodeRoot = NewNode(num)) != NULL)
    {
        /* links to child */
        nodeRoot->left  = Construct(fp, filename);
        nodeRoot->right = Construct(fp, filename);
    }
    
    return nodeRoot;
}

/******************************************************************************
 * FreeTree()
 *
 * Arguments: node - a tree root
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: frees the tree
 *
 *****************************************************************************/

void FreeTree(Node * root)
{
    if (root != NULL) {
	FreeTree(root->left);
	FreeTree(root->right);
	free(root);
    }
}


/******************************************************************************
 * spaces()
 *
 * Arguments: n - number of spaces
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints n spaces
 *
 *****************************************************************************/

void spaces(int n)
{
  int i;

  for (i = 0; i < n; i++)
    printf("  ");
  return;
}


/******************************************************************************
 * PreFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the PreFix format
 *
 *****************************************************************************/

void PreFixed(Node *root, int n)
{
  if (root != NULL) {
    spaces(n);
    printf("%d\n", root->value);
    PreFixed(root->left, n + 1);
    PreFixed(root->right, n + 1);
  }

  return;
}


/******************************************************************************
 * InFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the InFix format
 *
 *****************************************************************************/

void InFixed(Node *root, int n)
{

  if (root != NULL) {
    spaces(n);
    InFixed(root->left, n + 1);
    printf("%d\n", root->value);
    InFixed(root->right, n + 1);
  }

  return;
}


/******************************************************************************
 * PosFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the PosFix format
 *
 *****************************************************************************/

void PosFixed(Node *root, int n)
{

  if (root != NULL) {
    spaces(n);
    PosFixed(root->left, n + 1);
    PosFixed(root->right, n + 1);
    printf("%d\n", root->value);
  }

  return;
}


/******************************************************************************
 * sweepDepth()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the depthfirst format
 *
 *****************************************************************************/

void sweepDepth(Node *root, int n)
{
  PreFixed(root, 0);

  return;
}


/******************************************************************************
 * sweepBreadth()
 *
 * Arguments: root - root of the tree
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the Breathfirst format
 *
 *****************************************************************************/

void sweepBreadth(Node *root)
{
    Queue *Q;
    Element *t;

    Q = QueueNew();
    InsertLast(Q, root, 0);   /* inserir na fila o primeiro nó, a origem */

    t = GetFirst(Q);
    while(t != NULL){
        spaces(t->level);
        fprintf(stdout,"%d\n", (t->node)->value);
        if((t->node)->left != NULL)
            InsertLast(Q, (t->node)->left, t->level + 1);
        if((t->node)->right != NULL)
            InsertLast(Q, (t->node)->right, t->level + 1);
        t = GetFirst(Q);
    }
    
    return;
}

/******************************************************************************
 * IsTreeOrdered()
 *
 * Arguments: node - a tree root
 *            
 *
 * Returns: Boolean (TRUE or FALSE)
 * Side-Effects: none
 *
 * Description: checks if a tree is ordered
 *
 *****************************************************************************/

Boolean isTreeOrdered(Node * root)
{
    if(root == NULL) return TRUE;
    if(isTreeOrdered(root->left) == FALSE)
        return FALSE;
    if(isTreeOrdered(root->right) == FALSE)
        return FALSE;

    if( root->right != NULL)
        if( root->right->value <= root->value)
            return FALSE;

    if( root->left != NULL)
        if( root->left->value >= root->value)
            return FALSE;

    return TRUE;
}


/******************************************************************************
 * IsTreeBalanced()
 *
 * Arguments: node - a tree root
 *
 *
 * Returns: Boolean (TRUE or FALSE)
 * Side-Effects: none
 *
 * Description: checks if a tree is AVL balanced
 *
 *****************************************************************************/
int TreeHeight(Node *root, int level){
    int hR, hL;
    if(root == NULL)
        return level;
    if((hR = TreeHeight(root->right, level + 1)) >= (hL = TreeHeight(root->left, level + 1)))
        return hR;
    else
        return hL;
}

Boolean isTreeBalanced(Node * root)
{
    int hR = 1, hL = 1;
    if(root == NULL) return TRUE;
    if(isTreeBalanced(root->left) == FALSE)
        return FALSE;
    if(isTreeBalanced(root->right) == FALSE)
        return FALSE;

    if(root->right != NULL)
        hR = TreeHeight(root->right, 0);
    if(root->left != NULL)
        hL = TreeHeight(root->left, 0);

    if( (hR-hL)*(hR-hL) <= 1)
        return TRUE;

    return FALSE;
}




