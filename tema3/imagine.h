#ifndef IMAGINE
#define IMAGINE


typedef struct pixel { 
    char r;
    char g;
    char b;
} Pixel;

typedef struct imagine { 
    int nrRanduri;
    int nrColoane;
    int maxVal;
    Pixel** pixeli;
} Imagine;

#endif