/*DRAGU Diana-Valentina*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sateliti.h"
#define maxsize 1000

// Functie alocare pentru un stelit
Satelit aloc_init_satelit(int f, char nume[], Satelit left, Satelit right) {
    Satelit satelit = malloc(sizeof(struct satelit));
    if (satelit == NULL) {
        printf("Eroare la alocare\n");
        return NULL;
    }
    satelit->frecv = f;
    strcpy(satelit->nume, nume);
    // setam nodurile copii
    satelit->left = left;
    satelit->right = right;
    return satelit;
}

// Functie alocare pentru un min-heap
MinHeap aloc_heap(int nr_sateliti) {
    MinHeap mheap = malloc(sizeof(struct minheap));
    if (mheap == NULL) {
        printf("Eroare la alocare\n");
        return NULL;
    }
    mheap->elem = malloc(nr_sateliti * sizeof(Satelit));
    if (mheap->elem == NULL) {
        printf("Eroare la alocare\n");
        free(mheap);
        return NULL;
    }
    mheap->size = 0;
    mheap->capacity = nr_sateliti;
    return mheap;
}

/* Functie de comparatie a satelitilor, respectand conditiia ca
atunci cand satelitii sau frecvente egale sa se compare numele in
ordine alfabetica */
int comp(Satelit A, Satelit B) {
    if (A->frecv < B->frecv)
        return -1;  // A este mai mic
    else if (A->frecv == B->frecv)
        return strcmp(A->nume, B->nume);  // egale, analizam numele
    else
        return 1;   // A este mai mare
}

MinHeap siftDown(MinHeap mheap, int i) {
    // calculam indexii fiilor din stg si din dreapta
    int mini = i, l = i * 2 + 1, r = i * 2 + 2;
    // verificam daca exista un fiu stang mai mic
    if (l < mheap->size && comp(mheap->elem[l], mheap->elem[mini]) < 0)
        mini = l;
    // asemenea pentru un fiul drept
    if (r < mheap->size && comp(mheap->elem[r], mheap->elem[mini]) < 0)
        mini = r;
    // daca mini este diferit de i, inseamna ca am gasit un altfel de
    // fiu mai mic si interschimbam elementele
    if (i != mini) {
        Satelit aux = mheap->elem[i];
        mheap->elem[i] = mheap->elem[mini];
        mheap->elem[mini] = aux;
        mheap = siftDown(mheap, mini);
    }
    return mheap;
}

MinHeap siftUp(MinHeap mheap, int i) {
    // cat timp elementul de pe poz i, nu e radacina si
    // e mai mic decat parintele
    while (i > 0 && comp(mheap->elem[i], mheap->elem[(i - 1) / 2]) < 0) {
        // le interschimbam
        Satelit aux = mheap->elem[(i - 1) / 2];
        mheap->elem[(i - 1) / 2] = mheap->elem[i];
        mheap->elem[i] = aux;
        // actualizam indexul cu cel al parintelui
        i = (i - 1) / 2;
    }
    return mheap;
}

// Functie care extrage elementul minim din minheap
Satelit extractMin(MinHeap mheap) {
    if (mheap != NULL && mheap->size > 0) {
        Satelit min = mheap->elem[0];  // elem minim e chiar radacina
        mheap->elem[0] = mheap->elem[mheap->size-1];  // inlocuim cu ultimulelem
        mheap->size--;
        if (mheap->size > 0)  // daca mai exista elemente in minheap
            mheap = siftDown(mheap, 0);  // refacem minheap-ul
        return min;
    }
    return NULL;
}

// Functie care dezaloca arborele recursiv
void free_arbore(Satelit root) {
    if (root == NULL)
        return;
    free_arbore(root->left);
    free_arbore(root->right);
    free(root);
    root = NULL;
}

// Functie pentru afisarea pe niveluri
void bfs(Satelit root, FILE *fout) {
    if (root == NULL) {  // daca nodul nu exista, ne intarocem
        return;
    }

    // am initializat dinam o coada;
    Satelit *coada = malloc(maxsize * sizeof(Satelit));
    if (coada == NULL) {
        printf("Eroare la alocare\n");
        return;
    }

    // implementam LIFO pentru coada, folosind un index pentru
    // elementele scoase front, si rear pentru elementele adaugate
    int front = 0, rear = 0;

    coada[rear] = root;  // punem radacina in coada
    rear++;

    while (front < rear) {  // cat timp nu am scos toate elementele
        int nr_noduri_nivel = rear - front;  // cate noduri sunt pe nivel

        while (nr_noduri_nivel) {
            // extragem un nod din coadă
            Satelit nod_curent = coada[front];
            front++;  // actualizam front, astfel incat sa treaca la urm poz

            fprintf(fout, "%d-%s ", nod_curent->frecv, nod_curent->nume);

            // daca exista fiul stang, il bagam in coada
            if (nod_curent->left != NULL) {
                coada[rear++] = nod_curent->left;
            }

            // la fel pentru un nod drept
            if (nod_curent->right != NULL) {
                coada[rear++] = nod_curent->right;
            }
            nr_noduri_nivel--;  // decrementam nr de noduri din nivel, pentru
                                // nodul deja prelucrat
        }
        fprintf(fout, "\n");
    }
    free(coada);
}
