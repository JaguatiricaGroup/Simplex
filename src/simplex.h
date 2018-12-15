//## simplex por Gabriel Dias##//
#ifndef simplex_h
#define simplex_h 
#include "decomposicaoLU.h"
typedef struct{
	double **A;//matriz do Simplex
	double *b;//vetor b
	double *c;//vetor de custos c
	unsigned *I,n,m,*N;//vetor de indices na base, numero de colunas, numero de linhas, vetor de indices fora da base

}Simplex;

Simplex* iniSimplex(int m, int n);//inicia e aloca a estrutura
double** iniMatrizB(Simplex* L);//prepara a matriz que será usada
double* simplex(Simplex* L);//executa o método
#endif 


