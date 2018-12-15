#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"

/*inicializa a matriz
 */
void matrix_init ( double ***A, unsigned int n );

/*inicializa um vetor
 */
void vector_init ( double **b, unsigned int n );

/*le matriz de arquivo, usando o formado
 * definido no projeto
 */
void matrix_read ( double ***A, double **b, unsigned int *n);

/*funçao para liberar memoria
 */
void matrix_free ( double **A, unsigned int n );

/*funcao copia A para B (B eh alocada nesta funcao)
 */
void matrix_cpy ( double **A, double ***B, unsigned int n);

/*imprime uma matriz na tela
 */
void matrix_print ( double **A, unsigned int n, unsigned int *p );

/*imprime um vetor de doubles na tela
 */
void vector_print ( double *x, unsigned int n );

/*imprime um vetor de unsig. inteiros na tela
 */
void vector_print_ui ( unsigned int *p, unsigned int n );

/*multiplica duas matrizes
 */
void matrix_mult ( double **A, double **B, double **C, unsigned int n );

#endif /*MATRIX_H*/
