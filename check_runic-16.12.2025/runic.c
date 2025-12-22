#include "runic.h"
#include <stdlib.h>
Runic* creeaza_program()
{
    Runic* r = (Runic*)malloc(sizeof(Runic));
    r->input = NULL;
    r->terminat = 0;
    r->legi = NULL;
    r->nrLegi = 0;
    return r;
}

void sterge_program(Runic* p)
{ 
    if(p->input != NULL)
    {
        fclose(p->input);
    }
    for(int i = 0; i < p->nrLegi; i++)
    { 
        free(p->legi[i]);
    }
    free(p->legi);
    free(p);
}