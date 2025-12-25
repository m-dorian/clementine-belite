#ifndef COMENZI
#define COMENZI
#include "lege.h"
#include "runic.h"
#include <stdio.h>

void lsystem(Runic* program, char fisierInput[100]);
char* derive(int nrDerivari, Runic* program);
void load(Runic* program, char numeImagine[100]);
void save(Runic* program, char numeImagine[100]);
void turtle(Runic* program, int xInit, int yInit, int pasDeplasare, int orientare, int pasUnghiular, int nrDerivari, int r, int g, int b);
void undo(Runic* program);
#endif