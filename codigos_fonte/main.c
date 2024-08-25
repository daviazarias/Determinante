#include <stdio.h>
#include "determinante.h"

int main()
{
    Matriz A;
    if(leituraMatriz("matriz.txt", &A))
    {
        puts("Erro na leitura do arquivo.");
        return 1;
    }
    imprimeMatriz(&A);
    if(A.nlin == A.ncol)
    {
        printf("O determinante da matriz é %.2f.\n", determinante(&A, A.nlin));
    } else puts("A matriz fornecida não tem determinante, pois não é uma matriz quadrada.");
    liberaMatriz(&A);
    return 0;
}