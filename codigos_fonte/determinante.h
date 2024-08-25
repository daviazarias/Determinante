#ifndef _H_DETERMINANTE
#define _H_DETERMINANTE

typedef struct 
{
    int nlin; /*Número de linhas da matriz*/
    int ncol; /*Número de colunas da matriz*/
    float **elemento; /*Elementos da matriz*/
} Matriz;

void alocaMatriz(Matriz *m);
void liberaMatriz(Matriz *m);
void imprimeMatriz(Matriz *p);
int leituraMatriz(const char *arquivo, Matriz *p);
void matcof(Matriz *p, Matriz *c, int elin, int ecol);
float determinante(Matriz *p, int dimensao);

#endif