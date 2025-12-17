#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lege.h"

int main()
{ 
    char comanda[100];
    fgets(comanda, 100, stdin);
    FILE* fisierIntrare = NULL;
    comanda[strcspn(comanda, "\n")] = 0;
    while(strcmp(comanda, "EXIT") != 0)
    {   
        char* cuv = strtok(comanda, " ");
        if(strcmp(cuv, "LSYSTEM") == 0)
        { 
            cuv = strtok(NULL, " ");
            fisierIntrare = fopen(cuv, "r");
            if(fisierIntrare == NULL)
            { 
                printf("Failed to load %s.\n", cuv);
            }
            else 
            {  
                char axioma[100];
                fgets(axioma, 100, fisierIntrare);
                char temp[100];
                fgets(temp, 100, fisierIntrare);
                int nrLegi = strtol(temp, NULL, 10);
                printf("Loaded %s (L-system with %d rules)\n", cuv, nrLegi);
                Lege** legi = (Lege**)malloc(sizeof(Lege*) * nrLegi);
                for(int i = 0; i < nrLegi; i++)
                { 
                    char buff[100];
                    fgets(buff, 100, fisierIntrare);
                    char* cuvant = strtok(buff, " ");
                    char c = cuvant[0];
                    cuvant = strtok(NULL, " ");
                    Lege* l = constructor_lege(c, cuvant);
                    legi[i] = l;
                }
                for(int i = 0; i < nrLegi; i++)
                { 
                    free(legi[i]);
                }
                free(legi);
            }
        }
        else if(strcmp(cuv, "DERIVE") == 0)
        { 
            cuv = strtok(NULL, " ");
            int nrDerivari = strtol(cuv, NULL, 10);
            if(nrDerivari == 0
            for(int i = 0; i < nrDerivari; i++)
        }
        fgets(comanda, 100, stdin);
        comanda[strcspn(comanda, "\n")] = 0;
    }
    return 0;
}