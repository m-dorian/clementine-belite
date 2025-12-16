#ifndef matrice
#define matrice
#include <stdlib.h>
typedef struct matrice { 
    int* valori;
    int numarLinii;
    int numarColoane;
} Matrice;

Matrice* init_matrice(int nrLinii, int nrColoane);
int get_valoare(int i, int j, Matrice* m);
void set_valoare(int i, int j, int val, Matrice* m);
void print_matrice(Matrice* m);
void delete_matrice(Matrice* m);

#endif