#include "lu.h"

/*decomposicao LU com pivotamento
 */
void
lu( double **A, unsigned int **p_p, unsigned int n, int debug )
{
    unsigned int i,j,k,tmp,pivot_i,*p;
    double pivot_val,m;

    /*imprimindo para verificação
     */
    if(debug>1)
    {
        matrix_print(A,n,NULL); printf("\n");
    }

    /*allocando vetor de permutacao
     */
    // if (*p_p != NULL)
    // {
        p = *p_p = (unsigned int*)ra(*p_p,sizeof(unsigned int)*n);
    // }
    
    for(i=0;i<n;++i) p[i] = i;

    /*decomp LU
     */
    for(k=0;k<n-1;++k) /*(estagios)*/
    {
        /*procurando pivo
         */
        pivot_val = fabs(A[p[k]][k]);
        pivot_i   = k;
        for(i=k+1;i<n;i++)
            if(pivot_val < fabs(A[p[i]][k]))
            {
                pivot_val = fabs(A[p[i]][k]);
                pivot_i   = i;
            }
        /*trocando p[k] por p[pivot_i]
         */
        tmp        = p[k];
        p[k]       = p[pivot_i];
        p[pivot_i] = tmp;
        /**/

        /*para verificação
         */ 
        if(debug>1)
        {
            printf("Trocando linha %d com %d\n",p[k],p[pivot_i]);
            matrix_print(A,n,p);
            for(i=0;i<n;++i) printf(" %7d ",p[i]);
            printf("\n");
        }

        /*para cada linha abaixo da k-esima linha
         */
        for(i=k+1;i<n;i++)
        {
            m = A[p[i]][k]/A[p[k]][k];
            for(j=k;j<n;j++)
                A[p[i]][j] = A[p[i]][j] - m*A[p[k]][j]; 
            A[p[i]][k] = m;
        }
       
        /*para verificação
         */ 
        if(debug>1)
        {
            printf("Apos eliminação dos valores abaixo da coluna %d\n",k);
            matrix_print(A,n,p); printf("\n");
        }
    }
}

void
lu_solve( double **A, unsigned int *p, double *b, double **x, unsigned int n )
{
    int i,j;
    double det;
    double *y;

    /*calculando o determinante
     * da matriz
     */
    det = 0.0;
    for(i=0;i<n;++i) det += A[p[i]][i];

    /*sair det =~ 0
     */
    if(fabs(det) < TOL){ *x = NULL; return; }

    /*iniciando vetor temporario*/
    vector_init(&y,n);

    /*Ly = Pb;
     */
    for(i=0;i<n;++i)
    {
        y[i] = b[p[i]];
        for(j=0;j<i;++j)
            y[i] -= A[p[i]][j]*y[j];
    }

    /*Ux = y
     */
    for(i=n-1;i>=0;--i)
    {
        (*x)[i] = y[i];
        for(j=i+1;j<n;++j)
            (*x)[i] -= A[p[i]][j]*(*x)[j];
        (*x)[i] /= A[p[i]][i];
    }

    /*liberando vetor temporario*/
    free(y);
}

void
lu_solve_trans( double **A, unsigned *p, double *b, double **x, unsigned int n )
{
    int i,j;
    double det;
    double *y;

    /*calculando o determinante
     * da matriz
     */
    det = 0.0;
    for(i=0;i<n;++i) det += A[p[i]][i];

    /*sair det =~ 0
     */
    if(fabs(det) < TOL){ *x = NULL; return; }

    /*iniciando vetor temporario*/
    vector_init(&y,n);

    /*U^ty = b^t;
     */
    for(i=0;i<n;++i)
    {
        y[i] = b[i];
        for(j=0;j<i;++j)
            y[i] -= A[p[j]][i]*y[j];
        y[i] /= A[p[i]][i];
    }

    /*L^tPx = y
     */
    for(i=n-1;i>=0;--i)
    {
        (*x)[p[i]] = y[i];
        for(j=i+1;j<n;++j)
            (*x)[p[i]] -= A[p[j]][i]*(*x)[p[j]];
    }

    /*liberando vetor temporario*/
    free(y);
}

/*******************************************************
 * Funcoes teste
 ******************************************************/

/*é uma função usada para imprimir as matrizes L e U na tela.
 */
void
lu_print( double **A, unsigned int *p, unsigned int n )
{
    int i,j;
    double **L, **U;
   
    matrix_init(&L,n);
    matrix_init(&U,n);

    /*gerando matrizes L e U
     */
    for(i=0;i<n;++i)
    {
        for(j=0;j<i;++j)
        {
            L[i][j] = A[p[i]][j];
            U[i][j] = 0.0;
        }

        L[i][i] = 1.0;
        U[i][i] = A[p[i]][i];

        for(j=i+1;j<n;++j)
        {
            L[i][j] = 0.0;
            U[i][j] = A[p[i]][j];
        }
    }

    printf("\n");
    printf("L = \n");
    matrix_print(L,n,NULL);
    printf("\n");

    printf("U = \n");
    matrix_print(U,n,NULL);
    printf("\n");

    printf("p = \n");
    vector_print_ui(p,n);
    printf("\n");

    matrix_free(L,n);
    matrix_free(U,n);
}

/*função para chegar se a decomposição está ok
 */
int
lu_check( double **A, unsigned int *p, double **Ao, unsigned int n, int debug )
{
    unsigned int i,j,ok;
    double **L, **U, **PA;
   
    matrix_init(&L,n);
    matrix_init(&U,n);
    matrix_init(&PA,n);

    /*gerando matrizes L e U
     */
    for(i=0;i<n;++i)
    {
        for(j=0;j<i;++j)
        {
            L[i][j] = A[p[i]][j];
            U[i][j] = 0.0;
        }

        L[i][i] = 1.0;
        U[i][i] = A[p[i]][i];

        for(j=i+1;j<n;++j)
        {
            L[i][j] = 0.0;
            U[i][j] = A[p[i]][j];
        }
    }

    /*PA = L*U
     */
    matrix_mult(L,U,PA,n);

    /*comparando as matrizes
     */
    ok = 1;
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
            if(fabs(PA[i][j] - Ao[p[i]][j]) > TOL) ok = 0;

    if(debug>1)
    {
        printf("\n");
        printf("A = \n");
        matrix_print(Ao,n,p);
        printf("\n");

        printf("\n");
        printf("PA = \n");
        matrix_print(PA,n,NULL);
        printf("\n");

    }

    if(debug)
    {
        printf("\n");
        printf("L = \n");
        matrix_print(L,n,NULL);
        printf("\n");

        printf("U = \n");
        matrix_print(U,n,NULL);
        printf("\n");
    }

    matrix_free(L,n);
    matrix_free(U,n);
    matrix_free(PA,n);

    return ok;
}

int
lu_check_solve( double **A, unsigned int *p, double *b, double *x,
        unsigned int n, int debug)
{
    int i,j,ok;
    double *y;

    /*se nao ha resultado, sair
     */
    if(!x) return 1;

    vector_init(&y,n); 

    /*calculando y = Ax
     */
    for(i=0;i<n;++i)
    {
        y[i] = 0.0;
        for(j=0;j<n;++j)
            y[i] += A[i][j]*x[j];
    }

    if(debug)
    {
        printf("Ax = \n");
        vector_print(y,n);

        printf("b = \n");
        vector_print(b,n);
    }

    /*vefificando se y == b
     */
    ok = 1;
    for(i=0;i<n;++i)
        if(fabs(y[i] - b[i]) > TOL) ok = 0;

    free(y);
    
    return ok;
}


int
lu_check_solve_trans( double **A, unsigned int *p, double *b, double *x,
        unsigned int n, int debug)
{
    int i,j,ok;
    double *y;

    /*se nao ha resultado, sair
     */
    if(!x) return 1;

    vector_init(&y,n); 

    /*calculando y = A^Tx
     */
    for(i=0;i<n;++i)
    {
        y[i] = 0.0;
        for(j=0;j<n;++j)
            y[i] += A[j][i]*x[j];
    }

    if(debug)
    {
        printf("A^T x = \n");
        vector_print(y,n);

        printf("b = \n");
        vector_print(b,n);
    }

    /*vefificando se y == b
     */
    ok = 1;
    for(i=0;i<n;++i)
        if(fabs(y[i] - b[i]) > TOL) ok = 0;

    free(y);
    
    return ok;
}
