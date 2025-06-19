/*DRAGU Diana-Valentina*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sateliti.h"
#define NumeCarac 256
#define Codif 1000

Satelit cerinta1(MinHeap minheap) {
    while (minheap->size >= 2) {
        // extragem in A si B primii doi sateliti minimi,
        // dpdv al frecventei si a numelui
        Satelit A = extractMin(minheap);
        Satelit B = extractMin(minheap);

        char nume_nou[NumeCarac];  // concatenam numele celor 2
        strcpy(nume_nou, A->nume);
        strcat(nume_nou, B->nume);
        int frecv_nou = A->frecv + B->frecv;  // adunam frecventele

        /* initializam satelitul de legatura cu noile valori si
        cu legaturile la copii A si B */
        Satelit sleg = aloc_init_satelit(frecv_nou, nume_nou, A, B);

        // adaugam la finalul heap-ului satelitul de leg
        minheap->elem[minheap->size] = sleg;
        minheap->size++;
        // refacem minheap-ul prin cernerea in sus a elementelor
        // pana ajunge la forma corecta
        minheap = siftUp(minheap, minheap->size - 1);
    }
    return minheap->elem[0];  // rădăcina arborelui
}

void cerinta2(Satelit original, Satelit current,
            int *index, char binar[], FILE *fout) {
    // verificam daca valoarea indexului sare de lungimea sirului binar
    if ((*index) > strlen(binar))
        return;

    // daca am gasit frunza
    if (current->left == NULL && current->right == NULL) {
        fprintf(fout, "%s ", current->nume);  // afisam numele
        // ne reintoarcem inapoi la radacina pentru a cauta urmatoarea
        // frunza daca se poate
        cerinta2(original, original, index, binar, fout);
        return;  // oreturnez functia pentru a nu continua in cazul unei frunze
    }
    char b = binar[*index];  // extragem bitul de la pozitia index
    (*index)++;  // marim valoarea lui index
    if (b == '0')  // daca e 0 ne mutam in subarborele stg
        cerinta2(original, current->left, index, binar, fout);
    // in caz contrar, in cel drept
    cerinta2(original, current->right, index, binar, fout);
}

int valid(char nume[], char satelit[]) {
    char *aux = nume;
    aux = strstr(aux, satelit);

    // verificam fiecare aparitie a satelit in nume
    while (aux) {
        //  dacă dupa aparitie nu urmeaza o cifra, sau e final de sir, e valid
        if (aux[strlen(satelit)] == '\0' ||
        !(aux[strlen(satelit)] >= '0' && aux[strlen(satelit)] <= '9')) {
            return 1;
        }
       aux = strstr(aux+1, satelit);
    }

    return 0;
}

void cerinta3(Satelit root, char satelit[], FILE *fout, int *gasit) {
    // verificam daca am ajuns la nodul corect si returnam functia
    if (strcmp(root->nume, satelit) == 0) {
        return;
    }
    // verificam daca am ajuns la frunza si returnam
    if (root->left == NULL && root->right == NULL) {
        (*gasit) = 1;
        return;
    }
    /* verificam daca exista fiu la stg si contine in numele sau,
    obtinut prin concatenarea copiilor numele nodului salvat in
    satelit */
    if (!(*gasit) && root->left && valid(root->left->nume, satelit)) {
        fprintf(fout, "%d", 0);
        cerinta3(root->left, satelit, fout, gasit);  // cautam arborele stang
        return;
    }
    // identic pentru dreapta
    if (!(*gasit) && root->right && valid(root->right->nume, satelit)) {
        fprintf(fout, "%d", 1);
        cerinta3(root->right, satelit, fout, gasit);  // cautam arborele drept
        return;
    }
}

Satelit lca(Satelit root, char val1[], char val2[]) {
    if (root == NULL)  // verificam daca nodul exista
        return NULL;
    /* daca gasim un nod cu indicatorul egal cu una din valorile date
    returnam nodul */
    if (strcmp(root->nume, val1) == 0 || strcmp(root->nume, val2) == 0)
        return root;
    // retinem in st rezultatul cautarii in subarborele stang
    Satelit st = lca(root->left, val1, val2);
    // retinem in dr rezultatul cautarii in subarborele drept
    Satelit dr = lca(root->right, val1, val2);
    /* daca si arborele stang si arborele drept sunt nenule
    returnam nodul curent, adica s-au gasit ambele valori, 
    dar in cei doi subarbori diferiti */
    if (st && dr)
        return root;
    // daca sunt nule ambele, nu s-au gasit satelitii
    else if (!st && !dr)
        return NULL;
    // daca in subarborele stg nu s-a gasit nimic, returnam
    // rezultatul din dr, si invers pentru caz contrar
    if (!st)
        return dr;
    return st;
}

int main(int argc, char* argv[]) {
    FILE *fin = fopen(argv[2], "r");
    FILE *fout = fopen(argv[3], "w");

    if (fin == NULL || fout == NULL) {
        printf("Eroare la deschiderea fișierelor\n");
        return 1;
    }

    int nr_sateliti, nr_codificari, nr_aux;
    char nume_aux[NumeCarac];

    fscanf(fin, "%d", &nr_sateliti);  // citim nr satelitilor

    /* alocam minheap-ul cu dublul nr_satelitilor pentru a include
    si satelitii de legatura, care pot fi maxim nr_sateliti - 1 */
    MinHeap minheap = aloc_heap(2 * nr_sateliti);

    // Citire sateliți
    for (int i = 0; i < nr_sateliti; i++) {
        fscanf(fin, "%d", &nr_aux);  // citim frecventaa
        fscanf(fin, "%s", nume_aux);  // citim numele
        minheap->elem[i] = aloc_init_satelit(nr_aux, nume_aux, NULL, NULL);
        minheap->size++;
        /*
            refacem minheap-ul prin cernere in sus pentru cei i sateliti adaugati,
            cum noi citim datele pentru un element pe rand, il adaugam in heap, si
            refacem heap-ul astfel incat sa nu existe frunze copii mai mici decat 
            parintele
        */
        minheap = siftUp(minheap, i);
    }

    Satelit root = cerinta1(minheap);  // retinem radacina

    if (strcmp(argv[1], "-c1") == 0) {
        bfs(root, fout);
    }
    if (strcmp(argv[1], "-c2") == 0) {
        // citim nr de codificari
        fscanf(fin, "%d", &nr_codificari);
        char binar[Codif];
        for (int j = 0; j < nr_codificari; j++) {
            // citim codificarea
            fscanf(fin, "%s", binar);
            /* initializam variabila index cu 0 si dam functiei
            adresa ca parametru, pentru a parcurge sirul */
            int index = 0;
            cerinta2(root, root, &index, binar, fout);
            fprintf(fout, "\n");
        }
    }
    if (strcmp(argv[1], "-c3") == 0) {
        fscanf(fin, "%d", &nr_sateliti);
        char satelit[NumeCarac];
        int gasit = 0;
        for (int j = 0; j < nr_sateliti; j++) {
            fscanf(fin, "%s", satelit);
            cerinta3(root, satelit, fout, &gasit);
        }
    }
    if (strcmp(argv[1], "-c4") == 0) {
        fscanf(fin, "%d", &nr_sateliti);
        char satelit1[NumeCarac];
        char satelit2[NumeCarac];
        fscanf(fin, "%s", satelit1);  // citimi primul satelit
        fscanf(fin, "%s", satelit2);  // citim al doilea satelit
        // retinem in s parintele celor doua
        Satelit s = lca(root, satelit1, satelit2);
        nr_sateliti -= 2;  // scadem din nr total 2, echivalentul
                            // celor 2 sateliti deja prelucrati
        for (int j = 0; j < nr_sateliti; j++) {
            // citim urmatorul satelit
            fscanf(fin, "%s", satelit2);
            /* apelam functia pentru rezultatul obtinut anterior si
            numele satelitului citit, totodata actualizam s */
            s = lca(root, s->nume, satelit2);
        }
        fprintf(fout, "%s\n", s->nume);
    }

    // Dezalocari si inchideri fisiere
    free_arbore(root);  // dezaloc arborele plecand de la radacina
    free(minheap->elem);
    free(minheap);
    minheap = NULL;

    fclose(fin);
    fclose(fout);

    return 0;
}
