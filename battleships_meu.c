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
        int jucatorStatistici = (buff[0] == 'T');
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
                    rez = floor((float)(jocuri[idMeci]->lovituriTotale[jucatorStatistici]) * (1 - target/100));
                else rez = fmax(0, floor((float)(jocuri[idMeci]->lovituriTotale[jucatorStatistici]) * (target)/100)) - jocuri[idMeci]->lovituriNimerite[jucatorStatistici];
                float acurateteMeci = (float)jocuri[idMeci]->lovituriNimerite[jucatorStatistici]/jocuri[idMeci]->lovituriTotale[jucatorStatistici];
                if(rez < 0)
                    rez = 0;
                printf("%06.2f.%d %d\n", acurateteMeci * 100, rez, rez);
            }
        }
        else if(tip1 == 'T')
        {
            float sumaPonderata = 0;
            int sumaPonderi = 0;
            float numarator, numitor;
            int rez;
            for(int i = 0; i < nrMeciuri; i++)
            { 
                sumaPonderata += (float) jocuri[i]->lovituriNimerite[jucatorStatistici]/jocuri[i]->lovituriTotale[jucatorStatistici] * jocuri[i]->nrNave;
                sumaPonderi += jocuri[i]->nrNave;
            }
            if(tip2[1] == 'A')
            {
                numarator = (float) target/100 * sumaPonderi - sumaPonderata;
                numitor = (float) sumaPonderi/nrMeciuri * (1 - (target)/100);
                rez = (int)ceil(numarator/numitor);
            }
            else 
            { 
                numarator = (float) sumaPonderata/(target/100) - sumaPonderi;
                numitor = (float) sumaPonderi/nrMeciuri;
                rez = (int)floor(numarator/numitor);
            }
            float accTotala = sumaPonderata/sumaPonderi;
            if(rez < 0)
                rez = 0;
            printf("%06.2f.%d\n", accTotala * 100, rez);
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