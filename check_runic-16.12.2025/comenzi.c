#include "comenzi.h"
#include "imagine.h"
#include <string.h>
#include <stdlib.h>
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
        if(program->input != NULL)
        { 
            fclose(program->input);
        }
        program->input = f;
        char axioma[100];
        fgets(axioma, 100, program->input);
        axioma[strcspn(axioma, "\r\n")] = 0;
        strcpy(program->axioma, axioma);
        char temp[100];
        fgets(temp, 100, program->input);
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
            fgets(buff, 100, program->input);
            char* cuvant = strtok(buff, " \r\n");
            char c = cuvant[0];
            cuvant = strtok(NULL, " \r\n");
            Lege* l = constructor_lege(c, cuvant);
            program->legi[i] = l;
        }
    }
    return;
}

void derive(int nrDerivari, Runic* program)
{ 
    if(nrDerivari == 0)
    {
        printf("%s\n", program->axioma);
        return;
    }
    if(program->input == NULL)
    { 
        printf("No L-system loaded\n");
        return;
    }
    char* str = (char*)malloc(sizeof(char) * (strlen(program->axioma) + 1));
    str[0] = '\0';
    strcpy(str, program->axioma);
    int currLen = strlen(str);
    int capacitate = currLen * 2;
    for(int i = 0; i < nrDerivari; i++)
    {   
        int len = 0;
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
        temp[len] = '\0';
        free(str);
        str = temp;
        currLen = len;
    }
    printf("%s\n", str);
    free(str);
    return;
    }
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
    fscanf(fptr, "%d %d", &program->imag.nrRanduri, &program->imag.nrColoane);
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
    FILE* fptr = fopen(numeImagine, "wb");
    fprintf(fptr, "P6\n%d %d\n%d\n", program->imag.nrRanduri, program->imag.nrColoane, program->imag.maxVal);
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
    return;
}

void undo(Runic* program)
{ 
    char copie[100];
    strcpy(copie, program->ultimaComanda);
    char* cuv = strtok(copie, " ");
    if(strcmp(cuv, "LSYSTEM") == 0)
    { 
        program->input = NULL;
    }
    else
    {
        printf("Nothing to undo\n");
    }
    return;
}
