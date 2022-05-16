#include <stdio.h>
#include "lista.h"

int le_csv_v0(const char*);
int le_csv_v1(const char*);
Lista* le_csv_v2(const char*);

int main(void)
{
    printf("versao 0\n\n");
    le_csv_v0("stuff.csv");

    printf("\n\nversao 1\n\n");
    le_csv_v1("stuff.csv");

    printf("\n\nversao 2\n\n");
    Lista* teste = le_csv_v2("stuff.csv");
    listar(teste,"\nMusicas lidas do arquivo CSV");

    remover(4, teste);
    listar(teste, "\ndepois de remover o 4");

    remover(1, teste);
    listar(teste, "\ndepois de remover o primeiro");

    remover(teste->size, teste);
    listar(teste, "\ndepois de remover o ultimo");

    remover(1, teste);
    listar(teste, "\ndepois de remover o primeiro");

    remover(1, teste);
    listar(teste, "\ndepois de remover o primeiro");

    teste = apagar(teste);
    listar(teste, "\ndepois de apagar tudo");

    return 0;
}

int le_csv_v0(const char* arq)
{
    FILE* F = fopen(arq, "r");
    if (F == NULL) return -1;

    unsigned char buffer[256];
    size_t        lin = 0;
    char*         p   = fgets(buffer, sizeof(buffer), F);
    while (p != NULL)
    {
        size_t len = strlen(buffer) - 1;
        if (buffer[len] == '\n') buffer[len] = 0;
        printf(
            "%zd:\t[%s]\t(%zd)\n\n", ++lin, buffer,
            strlen(buffer));
        p = fgets(buffer, sizeof(buffer), F);
    }
    return 0;
};

int le_csv_v1(const char* arq)
{
    FILE* F = fopen(arq, "r");
    if (F == NULL) return -1;

    unsigned char buffer[256];
    size_t        lin     = 0;
    char          f[4][256];
    static const char*   mascara = "%[^,],%[^,],%[^,],%[^,\n]";
    char*         p = fgets(buffer, sizeof(buffer), F);
    while (p != NULL)
    {
        size_t len = strlen(buffer) - 1;
        if (buffer[len] == '\n') buffer[len] = 0;
        printf(
            "%zd:\t[%s]\t(%zd)\n", ++lin, buffer,
            strlen(buffer));
        int n =
            sscanf(buffer, mascara, f[0], f[1], f[2], f[3]);
        if (n != 4)
        {
            fprintf(stderr, "Erro na entrada\n");
            fclose(F);
            return -1;
        }
        printf(
            "Campos: [%s]  [%s]  [%s]  [%s]\n\n", f[0],
            f[1], f[2], f[3]);
        p = fgets(buffer, sizeof(buffer), F);
    }
    fclose(F);
    return 0;
}

Lista* le_csv_v2(const char* arq)
{
    Lista* nv = criar(100);
    if (nv == NULL) return NULL;
    
    FILE*  F  = fopen(arq, "r");
    if (F == NULL) return NULL;

    unsigned char      buffer[256];
    size_t             lin = 0;
    char               f[4][256];
    static const char* mascara =
        "%[^,],%[^,],%[^,],%[^,\n]";
    char* p = fgets(buffer, sizeof(buffer), F);
    while (p != NULL)
    {
        size_t len = strlen(buffer) - 1;
        if (buffer[len] == '\n') buffer[len] = 0;
        printf(
            "%zd:\t[%s]\t(%zd)\n", ++lin, buffer,
            strlen(buffer));
        int n =
            sscanf(buffer, mascara, f[0], f[1], f[2], f[3]);
        if (n != 4)
        {
            fprintf(stderr, "Erro na entrada\n");
            fclose(F);
            nv = apagar(nv); // apaga a lista
            return NULL;
        }
        // agora em f[] tem os campos: cria uma
        // Musica com os valores e insere na lista
        Musica* mus = criar_musica_fake(f);
        if (mus != NULL) inserir(mus, nv), free(mus);
        p = fgets(buffer, sizeof(buffer), F);
    }
    fclose(F);
    return nv;
};
