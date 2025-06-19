/*DRAGU Diana-Valentina*/

#ifndef _SATELITI_H_
#define _SATELITI_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NumeCarac 256

typedef struct satelit {
    int frecv;
    char nume[NumeCarac];
    struct satelit *left, *right;
} *Satelit;

typedef struct minheap {
    int capacity;
    int size;
    Satelit *elem;
} *MinHeap;

Satelit aloc_init_satelit(int f, char nume[], Satelit left, Satelit right);
MinHeap aloc_heap(int nr_sateliti);
void free_arbore(Satelit root);
void bfs(Satelit root, FILE *fout);
int comp(Satelit A, Satelit B);
MinHeap siftDown(MinHeap mheap, int i);
MinHeap siftUp(MinHeap mheap, int i);
Satelit extractMin(MinHeap mheap);

#endif
