#include "info.h"

Musica* criar_musica_fake(char f[4][256])
{

    printf(
        "Campos: [%s]  [%s]  [%s]  [%s]\n\n", f[0], f[1],
        f[2], f[3]);

    static int id = 1;
    Musica*    m  = (Musica*)malloc(sizeof(Musica));
    if (m == NULL) return NULL;
    sprintf(m->nome, "Musica-%05d", id);
    sprintf(m->banda, "Banda-%05d", id);
    m->duracao[0] = id % 10;      // min 0..9
    m->duracao[1] = 1 + id % 58;  // seg 1..59
    m->id         = id++;
    return m;
};  // criar()

Musica* criar_musica(char f[4][256])
{
    if (strlen(f[0]) == 0) return NULL;
    if (strlen(f[1]) == 0) return NULL;
    if (strlen(f[2]) == 0) return NULL;
    if (strlen(f[3]) == 0) return NULL;
    // id deve ter valor posisivo
    int     id = atoi(f[0]);
    if (id <= 0) return NULL;    
    Musica* m = (Musica*)malloc(sizeof(Musica));
    if (m == NULL) return NULL;
    m->id = id;
    // nome
    size_t len = sizeof(m->nome);
    if (strlen(f[1]) >= len)
    {  // copia o que cabe
        memcpy(m->nome, f[1], len - 1);
        m->nome[len - 1] = 0;
    }
    else
        strcpy(m->nome, f[1]);
    // banda
    len = sizeof(m->banda);
    if (strlen(f[2]) >= len)
    {  // copia o que cabe
        memcpy(m->banda, f[2], len - 1);
        m->banda[len - 1] = 0;
    }
    else
        strcpy(m->banda, f[2]);
    // duracao
    int min = 0;
    int seg = 0;
    int n   = sscanf(f[3], "%d:%d", &min, &seg);
    if (  // testes basicos com a duracao
        ( n != 2 ) || 
        min<0 ||
        (min == 0 && seg == 0) || 
        min > 590 ||
        seg < 0 ||
        seg>59 )
    {
        free(m);
        return NULL;
    }
    m->duracao[0] = min;
    m->duracao[1] = seg;
    return m;
};  // criar()
