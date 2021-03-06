#ifndef __tree__h
#define __tree__h 1
/******************************************************************************
 *
 * File Name: tree.h
 *	      (c) 2009 AED
 * Author:    AED team
 * Revision:  v2.2 ACR
 *            v3.0 AED Team Out 2013
 *
 * NAME
 *     tree  - prototypes
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

#include <stdio.h>
#include <stdlib.h>
#if !defined(__APPLE__)
#include <malloc.h>
#endif

#define MAX(X,Y) ((X) < (Y) ? (Y) : (X))

typedef enum
{
    FALSE=0,
    TRUE=1
} Boolean;


typedef struct _Node Node;

Node *AllocNode ();
Node *NewNode (int num);
Node *Construct (FILE *fp, char * filename);
void FreeTree(Node *root);
void espaco (int n);
void PreFixed (Node *root, int n);
void InFixed (Node *root, int n);
void PosFixed (Node *root, int n);
void sweepDepth (Node *root, int n);
void sweepBreadth (Node *root);
Boolean isTreeOrdered(Node *root);
int TreeHeight(Node *, int);
Boolean isTreeBalanced(Node *root);
#endif
