#include <stdio.h>
#include <math.h>

#define TAM 20

typedef struct 
{
    int nlin; /*Número de linhas da matriz (0 < nlin <= 20)*/
    int ncol; /*Número de colunas da matriz (0 < ncol <= 20)*/
    float elemento[TAM][TAM]; /*Elementos da matriz*/
} Matriz;

int leituramatriz(const char *arquivo, Matriz *p)
{
    FILE *arq;
    arq = fopen(arquivo, "r");
    if(arq == NULL)
        return 1;
        /*Não foi possível abrir o arquivo.*/

    fscanf(arq, "%d %d", &p->nlin, &p->ncol);

    if(p->nlin <= 0 || p->nlin > 20 || p->ncol <= 0 || p->ncol > 20)
        return 1;
        /*Tamanho não válido (nlin ou ncol <=0) ou fora do escopo do programa (>20)*/

    for(int i = 0; i < p->nlin; i++)
    {
        for(int j = 0; j < p->ncol; j++)
        {
            fscanf(arq, "%f", &p->elemento[i][j]);
        }
    }
    fclose(arq);
    return 0;
}

void imprimematriz(Matriz *p)
{
    puts("");
    for(int i = 0; i < p->nlin; i++)
    {
        for(int j = 0; j < p->ncol; j++)
        {
            printf("%.2f ", p->elemento[i][j]);
        }
        puts("");
    }
    puts("");
}

/*
Recebe dois ponteiros do tipo Matriz e a posição de um elemento específico na matriz
apontada por "*p". A posição é determinada informando a linha e a coluna onde está
localizado o elemento (elin, ecol).
A matriz apontada por "*c" é uma matriz de saída (será gerada pelo procedimento), 
e é definida como sendo a matriz dos cofatores do elemento p[elin,ecol] da matriz apontada por "*p".
*/
void matcof(Matriz *p, Matriz *c, int elin, int ecol){
    c->nlin = p->nlin - 1;
    c->ncol = p->ncol - 1;
    int k = 0;
    for(int i = 0; i < p->nlin; i++)
    {
        int l = 0;
        if(i != elin)
        {
            for(int j = 0; j < p->ncol; j++)
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
    float soma = 0;
    int lin = p->nlin - dimensao;
    Matriz cof;
    if(dimensao > 1)
    {
        /*Percorrendo todos os elementos da primeira linha da matriz.*/
        for(int col = p->ncol - dimensao; col < p->ncol; col++)
        {   
            /*Gerando a matriz dos cofatores de cada um dos elementos acessados.*/
            matcof(p, &cof, lin, col);
            /*Somatório que define o determinante da matriz. A definição do determinante
            de uma matriz é recursiva.*/
            soma += pow(-1, lin + col + 2)*(p->elemento[lin][col])*determinante(&cof, dimensao - 1);
        }
    } else soma = p->elemento[lin][p->ncol - dimensao];
    /*O determinante de uma matriz 1x1 é o valor de seu único elemento.*/
    return soma;
}

int main()
{
    Matriz A;
    if(leituramatriz("matriz.txt", &A))
    {
        puts("Erro na leitura do arquivo.");
        return 1;
    }
    imprimematriz(&A);
    if(A.nlin == A.ncol)
    {
        printf("O determinante da matriz é %.2f.\n", determinante(&A, A.nlin));
    } else puts("A matriz fornecida não tem determinante, pois não é uma matriz quadrada.");
    return 0;
}