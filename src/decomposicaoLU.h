//## Estrutura de dados do simplex por Gabriel Dias##//
#ifndef decomposicaoLU_h
#define TAM 3
#define decomposicaoLU_h
typedef struct {
    unsigned int n;//tamanho matriz nxn e vetor p
    unsigned int *p;//vetor permutacao
    double **A;//matriz
    double *B;
}DecLU;


/* Resolve o sistema Ax=b usando a decomposiçao LU, e retorna um array de double contendo a soluçao x.*/

/*Resolve o sistema labda^T A = b^T usando a decomposiçao LU, e retorna um array de double contendo a soluçao lambda.*/
//double* le_solve_trans( double **A, unsigned int *p, double *b, unsigned int n );
DecLU* iniLU(double **R, double *k, unsigned int tamanho);
void trocaVetorB(DecLU* l, double* novoB);
DecLU* alocaLU(unsigned int tamanho);
void trocaEmP(unsigned int *p, int i, int j) ;
void aplicaMultiplicador(DecLU* l, int linha,int linha2, double multiplicador);
int escolhePivo(DecLU* l, int coluna);
void trocaLinha(DecLU * s,int l, int L);
/* funçao faz a decomposiçao LU na própria matriz A.*/
void le(DecLU *l);
double* resolveSistema(DecLU *l);
double* resolveSistemaInvertido(DecLU *l,double* b);
double* descobreX(DecLU *l);
double* descobreLambda(DecLU *l);
double* resolveSistemaTransposto(DecLU *l);
double* resolveSistemaInvertidoTransposto(DecLU *l,double *b);
#endif /* ifndef decomposicaoLU_h */


