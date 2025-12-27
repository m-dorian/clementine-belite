#include "comenzi.h"
#include "imagine.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
void lsystem(Runic* program, char fisierInput[100])
{ 
    FILE* f = fopen(fisierInput, "r");
    if(f == NULL)
    { 
        printf("Failed to load %s\n", fisierInput);
        return;
    }
    else 
    {   
        char axioma[100];
        fgets(axioma, 100, f);
        axioma[strcspn(axioma, "\r\n")] = 0;
        strcpy(program->axioma, axioma);
        char temp[100];
        fgets(temp, 100, f);
        int nrLegi = strtol(temp, NULL, 10);
        printf("Loaded %s (L-system with %d rules)\n", fisierInput, nrLegi);
        program->nrLegi = nrLegi;
        if(program->legi == NULL)
            program->legi = (Lege**)malloc(sizeof(Lege*) * nrLegi);
        else 
        { 
            for(int i = 0; i < program->nrLegi; i++)
            { 
                free(program->legi[i]);
            }
            free(program->legi);
            program->legi = (Lege**)malloc(sizeof(Lege*) * nrLegi);
        }
        for(int i = 0; i < nrLegi; i++)
        { 
            char buff[100];
            fgets(buff, 100, f);
            char* cuvant = strtok(buff, " \r\n");
            char c = cuvant[0];
            cuvant = strtok(NULL, " \r\n");
            Lege* l = constructor_lege(c, cuvant);
            program->legi[i] = l;
        }
    }
    fclose(f);
    return;
}

char* derive(int nrDerivari, Runic* program)
{   
    char* str = (char*)malloc(sizeof(char) * 100);
    str[0] = '\0';
    if(program->nrLegi == 0)
    { 
        strcpy(str, "No L-system loaded");
        return str;
    }
    strcpy(str, program->axioma);
    if(nrDerivari == 0)
    { 
        return str;
    }
    int currLen = strlen(str);
    unsigned capacitate = currLen * 2;
    for(int i = 0; i < nrDerivari; i++)
    {   
        unsigned len = 0;
        char* temp = (char*)malloc(sizeof(char) * capacitate);
        temp[0] = '\0';
        for(int j = 0; j < currLen; j++)
        {   
            int gasit = 0;
            for(int k = 0; k < program->nrLegi; k++)
            { 
                if(str[j] == program->legi[k]->elem)
                {   
                    while(strlen(program->legi[k]->rez) + len + 1 > capacitate)
                    {   
                        capacitate *= 2;
                        temp = realloc(temp, sizeof(char) * capacitate);
                    }
                    strcpy(temp + len, program->legi[k]->rez);
                    len += strlen(program->legi[k]->rez);
                    gasit = 1;
                    break;
                }
            }
            if(gasit == 0)
            { 
                while(1 + len + 1 > capacitate)
                { 
                    capacitate *= 2;
                    temp = realloc(temp, sizeof(char) * capacitate);
                }
                temp[len] = str[j];
                len++;
            
        }
    }
        temp[len] = '\0';
        free(str);
        str = temp;
        currLen = len;
    
    }
    return str;
}


void load(Runic* program, char numeImagine[100])
{ 
    FILE* fptr = fopen(numeImagine, "rb");
    if(fptr == NULL)
    { 
        printf("Failed to load %s\n", numeImagine);
        return;
    }
    char buff[3];
    fscanf(fptr, "%s", buff);
    fscanf(fptr, "%d %d", &program->imag.nrColoane, &program->imag.nrRanduri);
    fscanf(fptr, "%d", &program->imag.maxVal);
    fgetc(fptr);
    program->imag.pixeli = (Pixel**)malloc(sizeof(Pixel*) * program->imag.nrRanduri);
    for(int i = 0; i < program->imag.nrRanduri; i++)
    { 
        program->imag.pixeli[i] = (Pixel*)malloc(sizeof(Pixel) * program->imag.nrColoane);
    }
    for(int i = 0; i < program->imag.nrRanduri; i++)
    { 
        for(int j = 0; j < program->imag.nrColoane; j++)
        { 
            fread(&program->imag.pixeli[i][j].r, sizeof(char), 1, fptr);
            fread(&program->imag.pixeli[i][j].g, sizeof(char), 1, fptr);
            fread(&program->imag.pixeli[i][j].b, sizeof(char), 1, fptr);
        }
    }
    printf("Loaded %s (PPM image %dx%d)\n", numeImagine, program->imag.nrRanduri, program->imag.nrColoane);
    fclose(fptr);
    return;
}

void save(Runic* program, char numeImagine[100])
{   
    if(program->imag.pixeli == NULL)
    { 
        printf("No image loaded\n");
        return;
    }
    FILE* fptr = fopen(numeImagine, "wb");
    fprintf(fptr, "P6\n%d %d\n%d\n", program->imag.nrColoane, program->imag.nrRanduri, program->imag.maxVal);
    for(int i = 0; i < program->imag.nrRanduri; i++)
    { 
        for(int j = 0; j < program->imag.nrColoane; j++)
        { 
            fwrite(&program->imag.pixeli[i][j].r, sizeof(char), 1, fptr);
            fwrite(&program->imag.pixeli[i][j].g, sizeof(char), 1, fptr);
            fwrite(&program->imag.pixeli[i][j].b, sizeof(char), 1, fptr);
        }
    }
    fclose(fptr);
    printf("Saved %s\n", numeImagine);
    return;
}

void deseneaza_pixel(Runic* program, int x, int y, int r, int g, int b)
{   
    program->imag.pixeli[(program->imag.nrRanduri - 1) - y][x].r = r;
    program->imag.pixeli[(program->imag.nrRanduri - 1) - y][x].g = g;
    program->imag.pixeli[(program->imag.nrRanduri - 1) - y][x].b = b;
}
void deseneaza_linie(Runic* program, int x0, int y0, int x1, int y1, int r, int g, int b)
{ 
    int dx = abs(x1 - x0);
    int sx;
    if(x0 < x1)
        sx = 1;
    else sx = -1;
    int dy = -1 * abs(y1 - y0);
    int sy;
    if(y0 < y1)
         sy = 1;
    else sy = -1;
    int err = dx + dy;
    while(1)
    { 
        deseneaza_pixel(program, x0, y0, r, g, b);
        if(x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if(e2 >= dy)
        { 
            err = err + dy;
            x0 = x0 + sx;
        }
        if(e2 <= dx)
        { 
            err = err + dx;
            y0 = y0 + sy;
        }
    }
    return;
}
void turtle(Runic* program, int xInit, int yInit, int pasDeplasare, int orientare, int pasUnghiular, int nrDerivari, int r, int g, int b)
{ 
    if(program->legi == NULL)
    { 
        printf("No L-system loaded\n");
        return;
    }
    if(program->imag.pixeli == NULL)
    { 
        printf("No image loaded\n");
        return;
    }
    char* derivare = derive(nrDerivari, program);
    int len = strlen(derivare);
    StareTestoasa stareCurenta = {(double)xInit, (double)yInit, (double)orientare};
    StareTestoasa stackStari[100];
    int topStack = -1;
    for(int i = 0; i < len; i++)
    { 
        switch(derivare[i])
        { 
            case 'F':
            { 
                double xNou = (double)stareCurenta.x + (double)pasDeplasare * cos(stareCurenta.orientare * (acos(-1)/180.0));
                double yNou = (double)stareCurenta.y + (double)pasDeplasare * sin(stareCurenta.orientare * (acos(-1)/180.0));
                deseneaza_linie(program, (int)stareCurenta.x, (int)stareCurenta.y, (int)xNou, (int)yNou, r, g, b);
                stareCurenta.x = xNou;
                stareCurenta.y = yNou;
                break;
            }
            case '+':
            { 
                stareCurenta.orientare += pasUnghiular;
                break;
            }
            case '-':
            { 
                stareCurenta.orientare -= pasUnghiular;
                break;
            }
            case '[':
            { 
                stackStari[++topStack] = stareCurenta;
                break;
            }
            case ']':
            {
                 stareCurenta = stackStari[topStack];
                 topStack--;
                 break;
            }
            default:
            break;
        }
    }
    free(derivare);
    printf("Drawing done\n");
    return;
}

void undo(Runic* program)
{ 
    char copie[100];
    strcpy(copie, program->ultimaComanda);
    char* cuv = strtok(copie, " ");
    if(strcmp(cuv, "LSYSTEM") == 0)
    { 
      
    }
    else
    {
        printf("Nothing to undo\n");
    }
    return;
}
