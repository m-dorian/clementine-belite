#ifndef joc
#define joc

typedef struct joc { 
    int lovituriNimerite[2];
    int lovituriTotale[2];
    int nrNave;
} Joc;

Joc* ruleaza_joc();
Joc* init_joc();
int creeaza_numar(char s[3]);
#endif