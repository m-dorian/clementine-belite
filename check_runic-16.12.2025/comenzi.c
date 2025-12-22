#include "comenzi.h"
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
    int capacitate = strlen(str) * 2;
    for(int i = 0; i < nrDerivari; i++)
    {   
        int len = 0;
        char* temp = (char*)malloc(sizeof(char) * capacitate);
        temp[0] = '\0';
        for(size_t j = 0; j < strlen(str); j++)
        {   
            int gasit = 0;
            for(int k = 0; k < program->nrLegi; k++)
            { 
                if(str[j] == program->legi[k]->elem)
                {   
                    if(strlen(program->legi[k]->rez) + len + 1 > capacitate)
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
                if(1 + len + 1 > capacitate)
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
    }
    printf("%s\n", str);
    free(str);
    return;
}
