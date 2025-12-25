#include "runic.h"
#include <stdlib.h>
#include <string.h>

Runic* creeaza_program()
{
    Runic* r = (Runic*)malloc(sizeof(Runic));
    r->input = NULL;
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
    for(int i = 0; i < p->imag.nrRanduri; i++)
    { 
        free(p->imag.pixeli[i]);
    }
    free(p->imag.pixeli);
    free(p);
}

void copiaza_program(Runic* dest, Runic* source)
{ 
    dest->input = source->input;
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