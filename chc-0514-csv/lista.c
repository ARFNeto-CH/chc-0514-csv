#include "lista.h"

Lista* apagar(Lista* l)
{
    if (l == NULL) return NULL;
    if (l->size == 0)  // vazia
    {
        free(l);
        return NULL;
    };  // if()
    // tem alguma coisa: apaga todo mundo
    Node* node = l->ini;
    do {
        Node* p = node->prox;  // salva esse ponteiro
        free(node);
        node = p;
    } while (node != NULL);
    return NULL;
};  // apagar()

Lista* criar(size_t limite)
{
    Lista* nova = (Lista*)malloc(sizeof(Lista));
    if (nova == NULL) return NULL;
    nova->size = 0;
    nova->lim  = limite;
    nova->ini  = NULL;
    nova->fim  = NULL;
    return nova;
}


int inserir(Info* item, Lista* l)
{  // insere no fim da lista
    if (l == NULL) return 0;
    if ((l->lim > 0) && (l->size >= l->lim)) return -1;
    // cabe: cria um novo no e poe la no fim
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo == NULL) return -1; // nao alocado
    // se estava vazio entao inicia os ponteiros
    if (l->size == 0)
    {
        l->ini     = novo;
        l->fim     = novo;
        novo->prev = NULL;
        novo->prox = NULL;
    }
    else
    {
        novo->prev     = l->fim;  // o ultimo de antes
        (l->fim)->prox = novo;
        novo->prox     = NULL;  // depois nao tem ninguem
        l->fim         = novo;
    };
    novo->info = (Info*)malloc(sizeof(Info));
    if (novo->info == NULL)
    { 
        free(novo);
        return -2;
    }
    *(novo->info) = *item;  // copia
    l->size += 1;
    return 0;
};

int listar(Lista* l, const char* titulo)
{
    if (l == NULL) return -1;
    if (titulo != NULL) printf("%s\n", titulo);
    if (l->lim > 0)
        printf(
            "\nLista com %zd de %zd elementos MAX\n",
            l->size, l->lim);
    else
        printf(
            "\nLista com %zd elementos [MAX nao "
            "definido]\n",
            l->size);
    if (l->size < 1) return 0;

    Node* p = l->ini;
    printf("\n    Primeiro: %4d\n", l->ini->info->id);
    printf("      Ultimo: %4d\n", l->fim->info->id);

    printf("\nElementos\n\n");
    do {
        listar_item(p->info,NULL);
        p = p->prox;
    } while (p != NULL);
    printf("\nFim da lista\n\n");
    return 0;
};

int listar_item(Info* info, const char* tit)
{
    if (tit == NULL)
        printf(
            "%8d  %s %s %3d:%02d\n", info->id, info->nome,
            info->banda, info->duracao[0],
            info->duracao[1]);
    else
        printf(
            "%s  %8d  %s %s %3d:%02d\n", tit, info->id,
            info->nome, info->banda, info->duracao[0],
            info->duracao[1]);
    return 0;
};

int remover(size_t n, Lista* lista)
{  // isso nao e algo comum em listas
    if (lista == NULL) return -1;
    if (lista->size < n) return -2;  // nem tem tantos
    Node* p = lista->ini;
    // posiciona no registro n
    for (size_t i = 0; i < n - 1; i += 1) p = p->prox;
    //listar_item(p->info, "remover()");
    // sera o unico?
    if (lista->size == 1)
    {   // vai ficar vazia
        lista->ini = NULL;
        lista->fim = NULL;
        lista->size = 0;
        free(p);
        return 0;
    }
    // apaga as referencias a p
    if (p->prev != NULL)
        p->prev->prox = p->prox;
    else
        lista->ini = p->prox;  // novo primeiro

    if (p->prox != NULL)
        p->prox->prev = p->prev;
    else
        lista->fim = p->prev;  // novo ultimo

    lista->size -= 1;
    free(p); // apaga mesmo
    return 0;
}
