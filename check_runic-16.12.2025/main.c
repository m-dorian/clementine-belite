#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "runic.h"
#include "comenzi.h"


int main()
{   
    Runic* program = creeaza_program();
    char comanda[100];
    fgets(comanda, 100, stdin);
    comanda[strcspn(comanda, "\n")] = 0;
    strcpy(program->ultimaComanda, comanda);
    while(1)
    {   
        char* cuv = strtok(comanda, " ");
        if(strcmp(cuv, "LSYSTEM") == 0)
        { 
            cuv = strtok(NULL, " ");
            lsystem(program, cuv);
        }
        else if(strcmp(cuv, "DERIVE") == 0)
        { 
            cuv = strtok(NULL, " ");
            int nrDerivari = strtol(cuv, NULL, 10);
            derive(nrDerivari, program);
        }
        else if(strcmp(cuv, "LOAD") == 0)
        { 
            cuv = strtok(NULL, " ");
            load(program, cuv);
        }
        else if(strcmp(cuv, "SAVE") == 0)
        { 
            cuv = strtok(NULL, " ");
            save(program, cuv);
        }
        else if(strcmp(cuv, "EXIT") == 0)
        {
            sterge_program(program);
            return 0;
        }
        fgets(comanda, 100, stdin);
        comanda[strcspn(comanda, "\n")] = 0;
        strcpy(program->ultimaComanda, comanda);
    }
    return 0;
}