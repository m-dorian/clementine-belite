#include "matrice.h"
#include <stdio.h>
Matrice* init_matrice(int nrLinii, int nrColoane)
{ 
    Matrice* rez = (Matrice*) malloc(sizeof(Matrice));
    rez->numarLinii = nrLinii;
    rez->numarColoane = nrColoane;
    rez->valori = (int*) calloc(nrLinii * nrColoane, sizeof(int));
    return rez;
}

int get_valoare(int x, int y, Matrice* m)
{   
    if(x < 0 || x >= m->numarLinii || y < 0 || y >= m->numarColoane)
        return 0;
    unsigned long long idx = x + x * (m->numarColoane - 1) + y;
    return m->valori[idx];
}

void set_valoare(int x, int y, int val, Matrice* m)
{   
    if(x < 0 || x >= m->numarLinii || y < 0 || y >= m->numarColoane)
        return;
    unsigned long long idx = x + x * (m->numarColoane - 1) + y;
    m->valori[idx] = val;
}

void print_matrice(Matrice* m)
{ 
    for(int i = 0; i < m->numarLinii; i++)
    { 
        for(int j = 0; j < m->numarColoane; j++)
        { 
            printf("%d ", get_valoare(i, j, m));
        }
        printf("\n");
    }
}
void delete_matrice(Matrice* m)
{ 
    free(m->valori);
    free(m);
}