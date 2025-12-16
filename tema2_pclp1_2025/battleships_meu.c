#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "matrice.h"
#include "nava.h"
#include "tabla.h"
#include "joc.h"
int main()
{   
    setbuf(stdout, NULL);
    int nrMeciuri;
    scanf("%d", &nrMeciuri);
    Joc** jocuri = (Joc**)malloc(sizeof(Joc*) * nrMeciuri);
    for(int i = 0; i < nrMeciuri; i++)
    { 
        jocuri[i] = ruleaza_joc();
    }
    char* cheie = (char*)malloc(sizeof(char) * 100);
    char* buff = (char*)malloc(sizeof(char) * 100);
    scanf("%s", cheie);
    while(scanf("%s", buff) == 1 &&  strcmp(buff, "Q") != 0)
    {   
        int jucatorStatistici;
        if(buff[0] == 'O')
             jucatorStatistici = 0;
        else jucatorStatistici = 1;
        char tip1 = buff[1];
        char idxMeci[4];
        idxMeci[0] = buff[2];
        idxMeci[1] = buff[3];
        idxMeci[2] = buff[4];
        idxMeci[3] = '\0';
        char targetChar[7]; 
        memcpy(targetChar, buff + 5, 6);
        targetChar[6] = '\0';
        float target = strtof(targetChar, NULL);
        char tip2[3];
        tip2[0] = buff[11];
        tip2[1] = buff[12];
        tip2[2] = buff[13];
        if(tip1 == 'U')
        { 
            int idMeci = strtol(idxMeci, NULL, 10) - 1;
            int rez;
            if(idMeci >= nrMeciuri)
                printf("Nu exista date pentru meciul cerut.\n");
            else 
            {  
                if(tip2[1] == 'A')
                    rez = jocuri[idMeci]->lovituriNimerite[jucatorStatistici] - ceil((float)(jocuri[idMeci]->lovituriTotale[jucatorStatistici]) * (target)/100);
                else rez = fmax(0, ceil((float)(jocuri[idMeci]->lovituriTotale[jucatorStatistici]) * (target)/100)) - jocuri[idMeci]->lovituriNimerite[jucatorStatistici];
                if(rez < 0)    
                    rez = 0;
                float procent = (int)(jocuri[idMeci]->acc_joc[jucatorStatistici] * 10000)/100.0;
                printf("%06.2f.%d\n", procent, rez);
            }
        }
        else if(tip1 == 'T')
        {
            int rez = 0;
            
            if(tip2[1] == 'I')
            {   
                while(calc_acc_totala(jocuri, nrMeciuri, jucatorStatistici) < target)
                {
                    float max = -100.0;
                    int idMax;
                    for(int i = 0; i < nrMeciuri; i++)
                    { 
                        if( 100 - jocuri[i]->pondereJoc[jucatorStatistici] > max && jocuri[i]->acc_joc[jucatorStatistici] < 100)
                        {   
                            max = 100 - jocuri[i]->pondereJoc[jucatorStatistici];
                            idMax = i;
                        }
                    }

                    print_ponderi(jocuri, nrMeciuri, jucatorStatistici);
                    jocuri[idMax]->acc_joc[jucatorStatistici] = 1.0;
                    jocuri[idMax]->pondereJoc[jucatorStatistici] = calc_pondereJoc(*jocuri[idMax], jucatorStatistici);
                    max = -100.0;
                    rez++;
                }
            }
            else 
            { 
                while(calc_acc_totala(jocuri, nrMeciuri, jucatorStatistici) >= target)
                {
                    int max = 200;
                    int idMax;
                    for(int i = 0; i < nrMeciuri; i++)
                    { 
                        if( 100 - jocuri[i]->pondereJoc[jucatorStatistici] < max && jocuri[i]->acc_joc[jucatorStatistici] > 0.0)
                        {   
                            max = 100 - jocuri[i]->pondereJoc[jucatorStatistici];
                            idMax = i;
                        }
                    }

                    print_ponderi(jocuri, nrMeciuri, jucatorStatistici);
                    jocuri[idMax]->acc_joc[jucatorStatistici] = 0.0;
                    jocuri[idMax]->pondereJoc[jucatorStatistici] = calc_pondereJoc(*jocuri[idMax], jucatorStatistici);
                    max = 200;
                    rez++;
                }
            }
            if(rez < 0)
                rez = 0;
            printf("%06.2f.%d\n", (int)(calc_acc_totala(jocuri, nrMeciuri, jucatorStatistici) * 10000)/100.0, rez);
        }
    }
    free(cheie);
        free(buff);
    for(int i = 0; i < nrMeciuri; i++)
    { 
        free(jocuri[i]);
    }
    free(jocuri);
    return 0;
}