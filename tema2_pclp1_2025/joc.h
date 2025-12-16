#ifndef joc
#define joc

typedef struct joc { 
    int lovituriNimerite[2];
    int lovituriTotale[2];
    int nrNave;
    float acc_joc[2];
    float pondereJoc[2];
} Joc;

Joc* ruleaza_joc();
Joc* init_joc();
int creeaza_numar(char s[3]);
float calc_acc_totala(Joc** jocuri, int nrJocuri, int idJucator);
float calc_pondereJoc(Joc j, int idJucator);
void print_ponderi(Joc** jocuri, int nrJocuri, int idJucator);
#endif