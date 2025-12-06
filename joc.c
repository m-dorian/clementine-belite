#include "joc.h"
#include "tabla.h"
#include "nava.h"
#include <stdio.h>
Joc* init_joc()
{
    Joc* j = (Joc*)malloc(sizeof(Joc));
    j->lovituriNimerite[0] = 0;
    j->lovituriNimerite[1] = 0;
    j->lovituriTotale[0] = 0;
    j->lovituriTotale[1] = 0;
    return j;
}
Joc* ruleaza_joc()
{ 
        int nrLinii, nrColoane;
        int JucatorLaRand = 0;
        Joc* jocCurent = init_joc();
        scanf("%d %d", &nrLinii, &nrColoane);
        Tabla** tableJoc = (Tabla**)malloc(sizeof(Tabla*) * 2);
        tableJoc[0] = init_tabla(nrLinii, nrColoane);
        tableJoc[1] = init_tabla(nrLinii, nrColoane);
        int nrNaveTotal = (nrLinii * nrColoane)/20 + (nrLinii * nrColoane)/30 + (nrLinii * nrColoane)/40 + (nrLinii * nrColoane)/55 + (nrLinii * nrColoane)/70;
        jocCurent->nrNave = nrNaveTotal;
        int naveRamase1 = nrNaveTotal;
        int naveRamase2 = nrNaveTotal;
        while(naveRamase1 > 0 || naveRamase2 > 0)
        { 
            int xCap, yCap;
            char tip, orientare;
            scanf(" %c %c %d %d", &tip, &orientare, &xCap, &yCap);
            Nava* n = init_nava(xCap, yCap, orientare, tip);
            if(adauga_nava(tableJoc[JucatorLaRand], *n) != 1)
            { 
                free(n);
                continue;
            }
            else 
            { 
                if(JucatorLaRand + 1 == 1)
                    naveRamase1--;
                else naveRamase2--;
                JucatorLaRand = !JucatorLaRand;
                free(n);
            }
        }
        print_matrice(tableJoc[JucatorLaRand]->spatii);
        printf("\n");
        print_matrice(tableJoc[!JucatorLaRand]->spatii);
        int jocTerminat = 0;
        JucatorLaRand = 0;
        tableJoc[0]->nrNave = tableJoc[0]->naveExistente;
        tableJoc[1]->nrNave = tableJoc[1]->naveExistente;
        while(!jocTerminat)
        { 
            int xAtac, yAtac;
            if(scanf("%d %d", &xAtac, &yAtac) != 2)
                break;
            jocCurent->lovituriTotale[JucatorLaRand]++6;
            loveste_nava(tableJoc[!JucatorLaRand], xAtac, yAtac, (JucatorLaRand) + 1, jocCurent);
            if(tableJoc[!JucatorLaRand]->naveExistente == 0)
            { 
                jocTerminat = 1;
                printf("Jucatorul %d a castigat.\n", JucatorLaRand + 1);
            }
            JucatorLaRand = !JucatorLaRand;
        }
        delete_tabla(tableJoc[0]);
        delete_tabla(tableJoc[1]);
        free(tableJoc);
        return jocCurent;
}

int creeaza_numar(char s[3])
{ 
    if(s[0] == '0')
            { 
                if(s[1] == '0')
                { 
                    return strtol(s + 2, NULL, 10);
                }
                else return strtol(s + 1, NULL, 10);
            }
            else return strtol(s, NULL, 10);
    return 0;
}