#ifndef LU_H
#define LU_H

#define TOL 1e-5

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
#include "matrix.h"

/*decomposicao LU com pivotamento
 */
void lu( double **A, unsigned int **p_p, unsigned int n, int debug );

/*resolvendo Ax = b usando a decomposicao LU
 */
void lu_solve( double **A, unsigned int *p, double *b, double **x, unsigned int n );

/*resolvendo x^tA = b^t usando a decomposicao LU
 */
void lu_solve_trans( double **A, unsigned int *p, double *b, double **x, unsigned int n );


/***********************************************************
 * As funções abaixo são usadas para testar a decomposição *
 ***********************************************************/

/*é uma função usada para imprimir as matrizes L e U na tela.
 */
void lu_print( double **A, unsigned int *p, unsigned int n );

/*função para chegar se a decomposição está ok
 */
int lu_check( double **A, unsigned int *p, double **Ao, unsigned int n, int debug );

/*usada para verificar se a
 * solucao esta ok
 */
int lu_check_solve( double **A, unsigned int *p, double *b, double *x,
        unsigned int n, int debug);

int
lu_check_solve_trans( double **A, unsigned int *p, double *b, double *x,
        unsigned int n, int debug);

#endif /*LU_H*/
