#ifndef LEGE
#define LEGE

typedef struct lege { 
    char elem;
    char rez[100];
} Lege;

Lege* constructor_lege(char e, char* r);

#endif