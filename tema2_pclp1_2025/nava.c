#include "nava.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
Nava* init_nava(int x, int y, char orientare, char tip)
{ 
    Nava* n = (Nava*) malloc(sizeof(Nava));
    n->xCap = x;
    n->yCap = y;
    n->orientare = orientare;
    n->traieste = 1;
    switch(tip)
    { 
        case 'S':
            n->lungime = 5;
            strcpy(n->nume, "Shinano");
            break;
        case 'Y':
            n->lungime = 4;
            strcpy(n->nume, "Yamato");
            break;
        case 'B':
            n->lungime = 3;
            strcpy(n->nume, "Belfast");
            break;
        case 'L':
            n->lungime = 2;
            strcpy(n->nume, "Laffey");
            break;
        case 'A':
            n->lungime = 1;
            strcpy(n->nume, "Albacore");
            break;
    }
    return n;
}
