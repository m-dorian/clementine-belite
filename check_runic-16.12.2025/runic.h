#ifndef RUNIC
#define RUNIC
#include <stdio.h>
#include "lege.h"
typedef struct runic { 
    FILE* input;
    char ultimaComanda[100];
    int terminat;
    Lege** legi;
    int nrLegi;
    char axioma[100];
} Runic;

Runic* creeaza_program();
void sterge_program(Runic* p);
#endif