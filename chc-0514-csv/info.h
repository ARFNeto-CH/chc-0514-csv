#pragma once
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int  id;
    char nome[20];
    char banda[20];
    int  duracao[2];

} Musica;

Musica* criar_musica(char[4][256]);
Musica* criar_musica_fake(char[4][256]);
