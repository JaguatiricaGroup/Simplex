#include "matrix.h"

void
matrix_init( double ***A, unsigned int n )
{
    int i;

    *A = (double**)ma(sizeof(double*)*n);
    for(i=0;i<n;++i) (*A)[i] = (double*)ma(sizeof(double)*n);
}

void 
vector_init( double **b, unsigned int n)
{
    *b = (double*)ma(sizeof(double)*n);
}

void
matrix_read( double ***A, double **b, unsigned int *n)
{
    int i,j;

    /*ler tamanho da matriz
     */
    scanf("%d",n);

    /*iniciando matriz
     */
    matrix_init(A,*n);

    /*checando
     */
    if(*n <= 0)
    {
        printf("Tamanho da matriz invalido\n");
        exit(0);
    }

    /*lendo valores de A
     */
    for(i=0;i<*n;++i)
        for(j=0;j<*n;++j)
            scanf("%lf",&(*A)[i][j]);

    /*iniciando o vetor
     */
    vector_init(b,*n);

    /*lendo o vetor b
     */
    for(j=0;j<*n;++j)
        scanf("%lf",&(*b)[j]);
}

void
matrix_cpy( double **A, double ***B, unsigned int n)
{
    int i;
    matrix_init(B,n);
    for(i=0;i<n;++i)
        memcpy((*B)[i],A[i],sizeof(double)*n);
}

void 
matrix_free( double **A, unsigned int n )
{
    int i;

    for(i=0;i<n;++i)
        free(A[i]);
    free(A);
}

void
vector_print( double *x, unsigned int n )
{
    int i;
    for(i=0;i<n;++i) printf(" %7.3lf ",x[i]);
    printf("\n");
}

void
vector_print_ui( unsigned int *p, unsigned int n )
{
    int i;
    for(i=0;i<n;++i) printf(" %7d ",p[i]);
    printf("\n");
}

void 
matrix_print( double **A, unsigned int n, unsigned int *p )
{
    int i,j;

    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
            if(p) printf(" %7.3lf ",A[p[i]][j]);
            else  printf(" %7.3lf ",A[i][j]);
        printf("\n");
    }
}

void
matrix_mult( double **A, double **B, double **C, unsigned int n )
{
    int i,j,k;

    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
        {
            C[i][j] = 0.0;
            for(k=0;k<n;++k)
                C[i][j] += A[i][k]*B[k][j];
        }
}
