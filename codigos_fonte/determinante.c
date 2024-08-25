#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "determinante.h"

void alocaMatriz(Matriz *m)
{
    int i;
    (*m).elemento = (float **) malloc((*m).nlin*sizeof(float *));
    for(i = 0; i < m->nlin; i++){
        *((*m).elemento + i) = (float *) malloc((*m).ncol*sizeof(float));
    }
}

void liberaMatriz(Matriz *m)
{
    int i;
    for(i = 0; i < m->nlin; i++){
        free(*((*m).elemento + i));
    }
    free((*m).elemento);
}


void imprimeMatriz(Matriz *p)
{
    int i, j;
    puts("");
    for(i = 0; i < p->nlin; i++)
    {
        for(j = 0; j < p->ncol; j++)
        {
            printf("%.2f ", p->elemento[i][j]);
        }
        puts("");
    }
    puts("");
}


int leituraMatriz(const char *arquivo, Matriz *p)
{
    FILE *arq;
    int i, j;
    arq = fopen(arquivo, "r");
    if(arq == NULL)
        return 1;
        /*Não foi possível abrir o arquivo.*/

    fscanf(arq, "%d %d", &p->nlin, &p->ncol);

    if(p->nlin <= 0 || p->ncol <= 0)
        return 1;
        /*Tamanho não válido (nlin <= 0 ou ncol <= 0).*/

    alocaMatriz(p);
    for(i = 0; i < p->nlin; i++)
    {
        for(j = 0; j < p->ncol; j++)
        {
            fscanf(arq, "%f", &p->elemento[i][j]);
        }
    }
    fclose(arq);
    return 0;
}

/*
Recebe dois ponteiros do tipo Matriz e a posição de um elemento específico na matriz
apontada por "*p". A posição é determinada informando a linha e a coluna onde está
localizado o elemento (elin, ecol).
A matriz apontada por "*c" é uma matriz de saída (será gerada pelo procedimento), 
e é definida como sendo a matriz dos cofatores do elemento p[elin,ecol] da matriz apontada por "*p".
*/
void matcof(Matriz *p, Matriz *c, int elin, int ecol)
{
    int i, j, k = 0;
    c->nlin = p->nlin - 1;
    c->ncol = p->ncol - 1;
    alocaMatriz(c);
    for(i = 0; i < p->nlin; i++)
    {
        int l = 0;
        if(i != elin)
        {
            for(j = 0; j < p->ncol; j++)
            {
                if(j != ecol)
                {
                    c->elemento[k][l] = p->elemento[i][j];
                    l++;
                }
            }
            k++;
        }
    }
}

/*
Recebe o ponteiro de uma matriz e sua dimensão e retorna o determinante da matriz fornecida. 
*/
float determinante(Matriz *p, int dimensao)
{
    int col;
    float soma = 0;
    Matriz cof;
    if(dimensao > 1)
    {
        /*Percorrendo todos os elementos da primeira linha da matriz.*/
        for(col = 0; col < p->ncol; col++)
        {   
            /*Gerando a matriz dos cofatores de cada um dos elementos acessados.*/
            matcof(p, &cof, 0, col);
            /*Somatório que define o determinante da matriz. A definição do determinante
            de uma matriz é recursiva.*/
            soma += pow(-1, col + 2)*(p->elemento[0][col])*determinante(&cof, dimensao - 1);
            liberaMatriz(&cof);
        }
    } else soma = p->elemento[0][0];
    /*O determinante de uma matriz 1x1 é o valor de seu único elemento.*/
    return soma;
}
