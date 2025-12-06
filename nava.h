#ifndef nava
#define nava

typedef struct nava {
    int xCap;
    int yCap;
    int lungime;
    char nume[15];
    char orientare;
    int traieste;
} Nava;

Nava* init_nava(int x, int y, char orientare, char tip);
#endif 