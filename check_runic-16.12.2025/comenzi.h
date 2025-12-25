#ifndef COMENZI
#define COMENZI
#include "lege.h"
#include "runic.h"
#include <stdio.h>

void lsystem(Runic* program, char fisierInput[100]);
void derive(int nrDerivari, Runic* program);
void load(Runic* program, char numeImagine[100]);
void save(Runic* program, char numeImagine[100]);
void undo(Runic* program);
#endif