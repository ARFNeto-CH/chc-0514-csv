#pragma once
#include "info.h"

typedef Musica Info;

typedef struct node_
{
    Info*         info;
    struct node_* prev;
    struct node_* prox;

} Node;

typedef struct
{
    Node*  ini;
    Node*  fim;
    size_t size;
    size_t lim;

} Lista;

Lista*  apagar(Lista*);
Lista*  criar(size_t);
int     inserir(Info*, Lista*);
int     listar(Lista*, const char*);
int     remover(size_t, Lista*);

int listar_item(Info*, const char*);
