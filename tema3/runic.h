#ifndef RUNIC
#define RUNIC
#include <stdio.h>
#include "lege.h"
#include "imagine.h"
typedef struct runic { 
    FILE* input;
    Imagine imag;
    char ultimaComanda[100];
    Lege** legi;
    int nrLegi;
    char axioma[100];
} Runic;

Runic* creeaza_program();
void sterge_program(Runic* p);
void copiaza_program(Runic* dest, Runic* source);
#endif