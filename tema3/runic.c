#include "runic.h"
#include <stdlib.h>
#include <string.h>

Runic* creeaza_program()
{
    Runic* r = (Runic*)malloc(sizeof(Runic));
    r->legi = NULL;
    r->nrLegi = 0;
    r->imag.pixeli = NULL;
    return r;
}

void sterge_program(Runic* p)
{   
    if(p->legi != NULL)
    { 
        for(int i = 0; i < p->nrLegi; i++)
        { 
            free(p->legi[i]);
        }
        free(p->legi);
    }
    if(p->imag.pixeli != NULL)
    {
        for(int i = 0; i < p->imag.nrRanduri; i++)
        { 
            free(p->imag.pixeli[i]);
        }
        free(p->imag.pixeli);
    }
    free(p);
    return;
}

void copiaza_program(Runic* dest, Runic* source)
{ 
    dest->nrLegi = source->nrLegi;
    if(dest->legi == NULL)
    { 
        dest->legi = (Lege**)malloc(sizeof(Lege*) * dest->nrLegi);
    }
    strcpy(dest->axioma, source->axioma);
    for(int i = 0; i < dest->nrLegi; i++)
    { 
        dest->legi[i] = constructor_lege(source->legi[i]->elem, source->legi[i]->rez);
    }
    return;
}