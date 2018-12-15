#include "simplex.h"
#include "lu.h"
#include <stdlib.h>

double calculaProdutoInterno(double* l, double* L, int tam){
	double solucao=0;	
	for (int i = 0; i < tam; ++i)
	{
			
		solucao += l[i]*L[i];
	}
	return solucao;
}

Simplex* iniSimplex(int m, int n){
	printf("iniciando Simplex:\n");
	Simplex *L = malloc(sizeof(Simplex));
	L->n = n;
	L->m = m;
	L->A = malloc(sizeof(double*)*m);//aloca matriz quadrada B
	L->I = malloc(sizeof(unsigned)*m);
	L->N = malloc(sizeof(unsigned)*(n-m));
	int j =0 ;
	for (int i = 0; i < L->m; ++i){
		L->A[i] = malloc(sizeof(double)*n);		

	}	
	for (int i = 0; i < (n - m); ++i){
		L->N[i] = i;

	}	
	for (int i = L->n - L->m; i < L->n; ++i)
	{
		L->I[j] = i;				
		j++;			
	}
	L->b = malloc(sizeof(double)*m);
	L->c = malloc(sizeof(double)*n);		
	return L;
}

double** iniMatrizB(Simplex* L){
	double** B = malloc(sizeof(double*)*(L->m));
	for (int i = 0; i < L->m; ++i)
	{
		B[i] = malloc(sizeof(double)*(L->m));
	}
	for (int i = 0; i < L->m; ++i)//supondo que sempre tem sulucao factivel nas n-m ultimas colunas
		{
			for (int j = (L->n - L->m); j < L->n; ++j)//copiando a base no B
			{				
				B[i][j - (L->n - L->m)] = L->A[i][j]; //(L->A[j][L->I[j]]);				
			}
		}			
	return B;
}

static void retornaColuna(double** B, unsigned numColuna, unsigned tam, double* auxColuna){
	// double* coluna = (double*) malloc(sizeof(double));
	// printf("%d\n", coluna);

	for (int i = 0; i < tam; ++i)
	{						
		(auxColuna)[i] = B[i][numColuna];
		// printf("%lf\n", B[i][numColuna]);
	}	
	// for (int i = 0; i < tam; ++i)
	// {
	// 	printf("%lf\n", coluna[i]);
	// }		
}

unsigned quemSaiBase(Simplex* L,double* solucaoX, double* Y, unsigned tam){
	double menorFracao = DBL_MAX;	
	unsigned indMenorFracao = -1;
	// printf("quem sai da base: ");
	for (int i = 0; i < tam; ++i)
	{
		// printf("%lf ",Y[i]);
		if (Y[i] > 0 )//&& indiceEstaNaBase(i, L->I, L->m))
		{
			double aux = solucaoX[i]/Y[i];
			// printf("%lf(%d) ", aux, L->I[i]);
			if (menorFracao > aux)
			{
				menorFracao = aux;
				indMenorFracao = i;
			}
		}
	}
	if (indMenorFracao == -1)		
	{
		printf("\nsolucao ilimitada...\n");		
		exit(1);
	}
	// printf(":: (%d) %d\n",  indMenorFracao,L->I[indMenorFracao]);
	return indMenorFracao;
}

void trocaColunas(double** B, double* Y,unsigned colunaB, unsigned tam)
{
	for (int i = 0; i < tam; ++i)
	{
		B[i][colunaB] = Y[i];
	}
}

// void printVetor1(double *v,int tamanho){
//     for (int i = 0; i < tamanho; ++i) {
//         printf("%lf, ",v[i] );
//     }    
//     printf("\n");
// }
char indiceEstaNaBase(unsigned indice, unsigned *I, unsigned tam){
	for (int i = 0; i < tam; ++i)
	 {
	 	if(I[i] == indice){
	 		return 1;
	 	}
	 } 
	 return 0;
}

static int aindaNaoEOtimo(Simplex* L,double* R, double *auxColuna, double* solucaoLambda){//se ótimo retorna -1, caso contrario o indice
	for (int i = 0; i < L->n ; ++i)
		{
			if (!indiceEstaNaBase(i, L->I, L->m))
			{				
				retornaColuna(L->A, i, L->m, auxColuna);
				(R)[i] = L->c[i] - calculaProdutoInterno(solucaoLambda, auxColuna, L->m);								
				if ((R)[i] < 0)
				{
					return i;
				}		
			}

		}	
		return -1;
}

void atualizaB(Simplex* L, double** B,unsigned tam, double* auxColuna){
		for (int i = 0; i < L->m; ++i)
		{			
			retornaColuna(L->A, L->I[i], L->m, auxColuna);
			for (int j = 0; j < L->m; ++j)
			{
				B[j][i] = (auxColuna)[j];
			}			
			// free(coluna);
			// coluna = NULL;
		}
}



double* simplex(Simplex* L){// corrigir cada coisa	
	// char eOtima = 1;
	double* solucaoX = malloc(sizeof(double)*L->n);//solucao em X da Base usada
	double* R = malloc(sizeof(double)*L->n);//vetor de custos
	double* Y = malloc(sizeof(double)*L->m);//vetor de representaçao da coluna q na base
	double* solucaoLambda = malloc(sizeof(double)*L->n);//solucao lambda na base
	double** B = iniMatrizB(L);//montada matriz B inicial
	unsigned int *pivotamento = malloc(sizeof(unsigned));
	double* Cb = malloc(sizeof(double)*L->m);
	double* auxColuna = malloc(sizeof(double)*L->m);		
	do
	{
		lu( B,  &pivotamento, L->m, 0);//decompoe a matriz B
		lu_solve( B, pivotamento, (L)->b, &solucaoX, L->m );//descobre a solucao X da base
		lu_solve_trans( B, pivotamento, Cb, &solucaoLambda,L->m );//descobre os lambdaT	
		int primeiroIndiceNnegativo = aindaNaoEOtimo(L, R, auxColuna, solucaoLambda);		
		if(primeiroIndiceNnegativo == -1)
		{		
			fflush(stdout);
			double* respostaFinal = malloc(sizeof(double)*L->n);
			for (int i = 0; i < L->m; ++i)		
			{
				respostaFinal[L->I[i]] = solucaoX[i];
			}						
			return respostaFinal;
		}else{
			retornaColuna(L->A, primeiroIndiceNnegativo, L->m, auxColuna);				
			lu_solve( B, pivotamento, auxColuna, &Y, L->m );	
			unsigned P = quemSaiBase(L,solucaoX,Y,L->m);// sai da base	
			L->I[P] = primeiroIndiceNnegativo;						
			L->N[primeiroIndiceNnegativo] = P;
			atualizaB(L,B,L->m,auxColuna);			
			Cb[P] =  L->c[L->I[P]];
		}		
	}while(1);	
}
