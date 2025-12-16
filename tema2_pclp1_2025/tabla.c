#include "tabla.h"
#include "joc.h"
#include <stdio.h>
Tabla* init_tabla(int nrLinii, int nrColoane)
{ 
    Tabla* t = (Tabla*) malloc(sizeof(Tabla));
    t->nrNave = (nrLinii * nrColoane)/20 + (nrLinii * nrColoane)/30 + (nrLinii * nrColoane)/40 + (nrLinii * nrColoane)/55 + (nrLinii * nrColoane)/70;
    t->navePeTabla = (Nava*) malloc(sizeof(Nava) * t->nrNave);
    t->spatii = init_matrice(nrLinii, nrColoane);
    t->naveExistente = 0;
    return t;
}

int adauga_nava(Tabla* t, Nava n)
{ 
    int ok = 1;
    int linie = n.xCap - 1;
    int col = n.yCap - 1;
    if(linie < 0 || linie >= t->spatii->numarLinii || col < 0 || col >= t->spatii->numarColoane)
    { 
        if(n.orientare == 'H')
            printf("Nava %s nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", n.nume, n.xCap, n.yCap);
        else printf("Nava %s nu poate fi amplasata vertical la coordonatele (%d, %d).\n", n.nume, n.xCap, n.yCap);
        return 0;
    }
    if(n.orientare == 'V')
    {   
        if(linie - n.lungime + 1 < 0)
            { 
                ok = 0;
            }
        else
        {
            for(int i = 0; i < n.lungime; i++)
            { 
                if(get_valoare(linie - i, col, t->spatii) != 0)
                { 
                    ok = 0;
                    break;
                }
            }
        }
        if(!ok)
        {
            printf("Nava %s nu poate fi amplasata vertical la coordonatele (%d, %d).\n", n.nume, n.xCap, n.yCap);
            return 0;
        }
    }
    else 
    { 
        if(col + n.lungime > t->spatii->numarColoane)
            { 
                ok = 0;
            }
        else
        {
            for(int i = 0; i < n.lungime; i++)
            { 
                if(get_valoare(linie, col + i, t->spatii) != 0)
                { 
                    ok = 0;
                    break;
                }
            }
        }
        if(!ok)
        {
            printf("Nava %s nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", n.nume, n.xCap, n.yCap);
            return 0;
        }
    
    }
    if(n.orientare == 'V')
    { 
        for(int i = 0; i < n.lungime; i++)
            { 
                set_valoare(linie - i, col, n.lungime, t->spatii);
                
            }
    }
    else 
    { 
        for(int i = 0; i < n.lungime; i++)
        { 
            set_valoare(linie, col + i, n.lungime, t->spatii);
        }
    }
    t->navePeTabla[t->naveExistente] = n;
    t->naveExistente++;
    return 1;
}


void loveste_nava(Tabla* t, int xAtac, int yAtac, int idJucator, Joc* jocCurent)
{   
    if(xAtac < 0 || xAtac > t->spatii->numarLinii || yAtac < 0 || yAtac > t->spatii->numarColoane)
    { 
        printf("Jucatorul %d a ratat o lovitura la coordonatele (%d, %d).\n", idJucator, xAtac, yAtac);
        return;
    }
    int val = get_valoare(xAtac - 1, yAtac - 1, t->spatii);
    switch(val)
    { 
        case -1:
        {
            printf("Coordonatele (%d, %d) au fost deja atacate de jucatorul %d.\n", xAtac, yAtac, idJucator);
            break;
        }
        case 0:
        {
            printf("Jucatorul %d a ratat o lovitura la coordonatele (%d, %d).\n", idJucator, xAtac, yAtac);
            set_valoare(xAtac - 1, yAtac - 1, -1, t->spatii);
            break;
        }
        default:
        {      
            set_valoare(xAtac - 1, yAtac - 1, -1, t->spatii);
            jocCurent->lovituriNimerite[idJucator - 1]++;
            for(int i = 0; i < t->nrNave; i++)  //Verific daca am lovit capul unei nave
            {   
                if(t->navePeTabla[i].traieste)
                {
                    if(xAtac == t->navePeTabla[i].xCap && yAtac == t->navePeTabla[i].yCap)
                    { 
                        t->navePeTabla[i].traieste = 0;
                        if(t->navePeTabla[i].orientare == 'H')
                        {
                            printf("Jucatorul %d a distrus o nava %s plasata intre coordonatele (%d, %d) si (%d, %d).\n", idJucator, t->navePeTabla[i].nume, t->navePeTabla[i].xCap, t->navePeTabla[i].yCap, t->navePeTabla[i].xCap, t->navePeTabla[i].yCap + (val - 1));
                        } else printf("Jucatorul %d a distrus o nava %s plasata intre coordonatele (%d, %d) si (%d, %d).\n", idJucator, t->navePeTabla[i].nume, t->navePeTabla[i].xCap, t->navePeTabla[i].yCap, t->navePeTabla[i].xCap - val + 1, t->navePeTabla[i].yCap);
                        sterge_nava_de_pe_tabla(t, i);
                        set_valoare(xAtac - 1, yAtac - 1, -1, t->spatii);
                        t->naveExistente--;
                        return;
                    }
                }   
            }
            for(int i = 0; i < t->nrNave; i++) //Daca n-am lovit capul unei nave, verificam daca lovitura noastra a distrus sau nu o nava, uitandu-ma la fiecare nava si vazand daca spatiul lovit apartine uneia. Vreau clementine belite.
            {   
                if(t->navePeTabla[i].traieste)
                {
                    if(t->navePeTabla[i].orientare == 'H')
                    { 
                        for(int j = 0; j < val; j++)
                        {    
                            if(xAtac == t->navePeTabla[i].xCap && yAtac == t->navePeTabla[i].yCap + j)
                            {   
                                int distrusa = 1;
                                for(int k = 0; k < val; k++)
                                {
                                    if(get_valoare(t->navePeTabla[i].xCap - 1, t->navePeTabla[i].yCap + k - 1, t->spatii) != -1)
                                        distrusa = 0;
                                }      
                                if(distrusa)
                                { 
                                    t->navePeTabla[i].traieste = 0;
                                    printf("Jucatorul %d a distrus o nava %s plasata intre coordonatele (%d, %d) si (%d, %d).\n", idJucator, t->navePeTabla[i].nume, t->navePeTabla[i].xCap, t->navePeTabla[i].yCap, t->navePeTabla[i].xCap, t->navePeTabla[i].yCap + val - 1);
                                    sterge_nava_de_pe_tabla(t, i);
                                    t->naveExistente--;
                                    return;
                                }
                                else 
                                { 
                                    printf("Jucatorul %d a lovit o nava %s la coordonatele (%d, %d).\n", idJucator, t->navePeTabla[i].nume, xAtac, yAtac);
                                    set_valoare(xAtac - 1, yAtac - 1, -1, t->spatii);
                                    return;
                                }
                            }
                        }
                    }
                    else 
                    {
                        for(int j = 0; j < val; j++)
                        { 
                            if(xAtac == t->navePeTabla[i].xCap - j && yAtac == t->navePeTabla[i].yCap)
                            {   
                                int distrusa = 1;
                                for(int k = 0; k < val; k++)
                                {
                                    if(get_valoare(t->navePeTabla[i].xCap - k - 1, t->navePeTabla[i].yCap - 1, t->spatii) != -1)
                                        distrusa = 0;
                                }      
                                if(distrusa)
                                { 
                                    t->navePeTabla[i].traieste = 0;
                                    printf("Jucatorul %d a distrus o nava %s plasata intre coordonatele (%d, %d) si (%d, %d).\n", idJucator, t->navePeTabla[i].nume, t->navePeTabla[i].xCap, t->navePeTabla[i].yCap, t->navePeTabla[i].xCap - val - 1, t->navePeTabla[i].yCap);
                                    sterge_nava_de_pe_tabla(t, i);
                                    t->naveExistente--;
                                    return;
                                }
                                else 
                                { 
                                    printf("Jucatorul %d a lovit o nava %s la coordonatele (%d, %d).\n", idJucator, t->navePeTabla[i].nume, xAtac, yAtac);
                                    set_valoare(xAtac - 1, yAtac - 1, -1, t->spatii);
                                    return;
                                }
                            }
                        }
                    } 
                }
                }
            }
    }
    return;
}

void sterge_nava_de_pe_tabla(Tabla* t, int idNava)
{ 
    if(t->navePeTabla[idNava].orientare == 'H')
    { 
        for(int i = 0; i < t->navePeTabla[idNava].lungime; i++)
        { 
            if(get_valoare(t->navePeTabla[idNava].xCap - 1, t->navePeTabla[idNava].yCap + i - 1, t->spatii) != -1)
                set_valoare(t->navePeTabla[idNava].xCap - 1, t->navePeTabla[idNava].yCap + i - 1, 0, t->spatii);
        }
    }
    else 
    { 
        for(int i = 0; i < t->navePeTabla[idNava].lungime; i++)
        {   
            if(get_valoare(t->navePeTabla[idNava].xCap - i - 1, t->navePeTabla[idNava].yCap - 1, t->spatii) != -1)
                set_valoare(t->navePeTabla[idNava].xCap - i - 1, t->navePeTabla[idNava].yCap - 1, 0, t->spatii);
        }
    }
}
void delete_tabla(Tabla* t)
{ 
    delete_matrice(t->spatii);
    free(t->navePeTabla);
    free(t);
}