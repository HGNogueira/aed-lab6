#include"queue.h"
#include"tree.h"
#include<stdlib.h>

Queue *QueueNew(){
    Queue *Q;
    Q = (Queue*) malloc(sizeof(Queue));
    Q->first = NULL;
    Q->last = NULL;
    return Q;
}

Element *GetFirst(Queue *Q){
    Element *t;
    if(Q->first == NULL)
        return NULL;
    if(Q->first == Q->last)
        Q->last = NULL;
    t = Q->first;
    Q->first = Q->first->next;
    
    return t;
}

void InsertLast(Queue *Q, Node *t, int n){
    Element *last;

    last = (Element *) malloc(sizeof(Element));
    last->node = t;
    last->level = n;
    last->next = NULL;

    if(Q->last != NULL){
        (Q->last)->next = last;
        Q->last = last;
    }
    else if(Q->first != NULL){
        (Q->first)->next = last;
        Q->last = last;
    }
    else{
    Q->first = last;
    }
}

void QueuePrint(Queue *Q){
    Element *t;
    t = Q->first;
    while(t != NULL){
        fprintf(stdout, "%d ", t->level);
        t = t->next;
    }
}

/*void QueueFree(Queue *Q){
    Element* t, aux;
    if((t = Q->first) == NULL){
        free(Q);
        return;
    }
    
    FreeTree(t->node);
    while(t != NULL){
        aux = t->next;
        free(t);
        t = aux;
    }
    free(Q);
}*/
