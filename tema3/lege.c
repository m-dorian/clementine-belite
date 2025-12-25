#include "lege.h"
#include <string.h>
#include <stdlib.h>
Lege* constructor_lege(char e, char* r)
{ 
    Lege* l = (Lege*)malloc(sizeof(Lege));
    l->elem = e;
    strcpy(l->rez, r);
    return l;
}