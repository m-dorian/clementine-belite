#ifndef tabla
#define tabla

#include "matrice.h"
#include "nava.h"
#include "joc.h"

typedef struct tabla { 
    Matrice* spatii;
    Nava* navePeTabla;
    int nrNave;
    int naveExistente;
} Tabla;

Tabla* init_tabla(int nrLinii, int nrColoane);
int adauga_nava(Tabla* t, Nava n);
void loveste_nava(Tabla* t, int xAtac, int yAtac, int idJucator, Joc* jocCurent);
void sterge_nava_de_pe_tabla(Tabla* t, int idNava);
void delete_tabla(Tabla* t);
#endif