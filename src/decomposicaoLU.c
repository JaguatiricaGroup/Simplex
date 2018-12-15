//## Estrutura de dados do simplex por Gabriel Dias##//
#define modulo(a) (((a) < 0)? ((a)*(-1)) : (a)) 
#include "decomposicaoLU.h"
#include <stdlib.h>
#include <math.h>
#define TAM 3
/*#include <stdio.h>*/

DecLU* iniLU(double **R, double *k, unsigned int tamanho){
   DecLU* l = malloc(sizeof(DecLU));
   l->n = tamanho;
   l->B = k;
   l->p = malloc(sizeof(unsigned int)*(l->n));
   for (int i = 0; i < l->n; ++i) {
       (l->p)[i] = i;
   }
   l->A = R;
   le(l);//ja inicia decomposto
    return l; 
}

DecLU* alocaLU(unsigned int tamanho){    
    DecLU* l = malloc(sizeof(DecLU));
    l->n = tamanho;
    l->B = malloc(sizeof(double)*tamanho);
    l->A = malloc(sizeof(double*)*tamanho);
    l->p = malloc(sizeof(unsigned int)*(l->n));
    for (int i = 0; i < l->n; ++i) {
       (l->p)[i] = i;
       (l->A)[i] = malloc(sizeof(double)*tamanho);
    }
    return l; 
}

void trocaEmP(unsigned int *p, int i, int j) {
    unsigned int aux = p[i];
    p[i]=p[j];
    p[j]=aux;
}

void aplicaMultiplicador(
DecLU* l, int linha,int linha2, double multiplicador){
    for (int i = linha2;  i < l->n; ++ i) {
            l->A[linha][i] -= (multiplicador*((l->A)[linha2][i]));
    }
}

int escolhePivo(
DecLU* l, int coluna){
    double maior = l->A[coluna][coluna];
    int maiorLinha = coluna;
    for (int i = coluna; i < l->n; ++i) {
        if (modulo(l->A[i][coluna]) > maior ) {
            maior = modulo(l->A[i][coluna]);
            maiorLinha = i;
        } 
    }
    return maiorLinha;
}

void trocaLinha(DecLU * s,int l, int L){
    if(l != L){
        /*double aux =0;*/
        /*for (int i = 0; i < s->n ; ++i) {*/
            /*aux = (s->A)[l][i];*/
            /*(s->A)[l][i] = (s->A)[L][i];*/
            /*(s->A)[L][i] = aux;*/
        /*}*/
        /*unsigned int aux1 = s->p[l];*/
        /*s->p[l] = s->p[L];*/
        /*s->p[L] = aux1;*/
        double* aux = s->A[l];
        s->A[l] = s->A[L];
        s->A[L] = aux;
        /*double aux1 = s->B[l];*/
        /*s->B[l] = s->B[L];*/
        /*s->B[L] = aux1;*/
        trocaEmP(s->p,l,L);
    }
}

void le(DecLU* l ){   
    for (int icoluna  = 0; icoluna  < l->n-1; ++icoluna ) {
        int indPivo = escolhePivo(l,icoluna );
        trocaLinha(l,icoluna , indPivo);
        for (int lAbaixoDiagonal = icoluna+1 ; lAbaixoDiagonal  < l->n; ++lAbaixoDiagonal)  {                    
            double multiplicador = (((l->A)[lAbaixoDiagonal][icoluna])/(l->A)[icoluna][icoluna]);
            /*printf("multi:%lf \n ",multiplicador);*/
            aplicaMultiplicador(l, lAbaixoDiagonal, icoluna , multiplicador);
            ((l->A)[lAbaixoDiagonal][icoluna]) = multiplicador;
        }
    } 
}


double* resolveSistema(DecLU *l){
    double* solucao = malloc(sizeof(double)*(l->n));
    for (int k = 0; k < l->n ; ++k) {        
        solucao[k]=0;        
    }
    for(int i=0;i< l->n ; i++){
        solucao[i] = l->B[l->p[i]];
        for (int j = 0; j < i; ++j) {
            solucao[i]-= ((l->A)[i][j])*solucao[j]; 
        }  
        solucao[i] /=1.0; 
    }        
    return solucao;
}

double* resolveSistemaInvertido(DecLU *l,double *b){
    double* x = malloc(sizeof(double)*(l->n));
    for (int k = 0; k < l->n ; ++k) {    
        x[k]=0;        
    }        
    for(int k = l->n-1; k>=0 ; k--){
        x[k] = b[k];//l->B[k];
        for (int i = k+1 ; i < l->n; i++) {
            x[k]-= (((l->A)[k][i])*x[i]);
        }
        /*printf("%lf\n", x[k]);*/
        x[k] /= l->A[k][k];
    }
    return x;
}

/*double* resolveSistema(Simplex *l){*/
    /*double* solucao = malloc(sizeof(double)*(l->n));*/
    /*for (int k = 0; k < l->n ; ++k) {        */
        /*solucao[k]=0;*/
    /*}*/
    /*for(int i=0;i< l->n ; i++){*/
        /*solucao[i] = l->B[l->p[i]];*/
        /*for (int j = 0; j < i; ++j) {*/
            /*solucao[i]-= ((l->A)[i][j])*solucao[j]; */
            /*[>printf("%lf ",l->A[j][i]);<]*/


        /*}  */
        /*[>printf("\n");<]*/
        /*solucao[i] /=1.0; */
    /*}        */
    /*return solucao;*/
/*}*/

double* resolveSistemaTransposto(DecLU *l){
    double* solucao = malloc(sizeof(double)*(l->n));
    for (int k = 0; k < l->n ; ++k) {        
        solucao[k]=0;
    }
    for(int i=0;i< l->n ; i++){
        solucao[i] = l->B[i];
        for (int j = 0; j < i; ++j) {
            solucao[i]-= ((l->A)[j][i])*solucao[j]; 
            /*printf("%lf ",l->A[j][i]);*/
        }  
        solucao[i] /= l->A[i][i]; 
            /*printf("%lf ",l->A[i][i]);*/
        /*printf("\n");*/
    }        
    return solucao;
}

/*double* resolveSistemaInvertido(Simplex *l,double *b){*/
    /*double* x = malloc(sizeof(double)*(l->n));*/
    /*for (int k = 0; k < l->n ; ++k) {*/
        /*x[k]=0;*/
    /*}*/
    /*for(int k = l->n-1; k>=0 ; k--){*/
        /*x[k] = b[k];//l->B[k];*/
        /*for (int i = k+1 ; i < l->n; i++) {*/
            /*x[k]-= (((l->A)[k][i])*x[i]);*/
            /*[>printf("%lf ",l->A[k][i]);<]*/
        /*}*/
       /*[>printf("%lf\n", x[k]);<]*/
        /*[>x[k] /= l->A[k][k];<]*/
            /*[>printf("%lf ",l->A[k][k]);<]*/
            /*[>printf("\n");<]*/
    /*}*/
    /*return x;*/
/*}*/

double* resolveSistemaInvertidoTransposto(DecLU *l,double *b){
    double* x = malloc(sizeof(double)*(l->n));
    for (int k = 0; k < l->n ; ++k) {        
        x[k]=0;
    }
    for(int k = l->n-1; k>=0 ; k--){
        x[k] = b[k];//l->B[k];
        for (int i = k+1 ; i < l->n; i++) {
            x[k]-= (((l->A)[i][k])*x[i]);
        }

    }
    return x;
}

double* descobreX(DecLU *l){
    double* L = resolveSistema(l);
    return  resolveSistemaInvertido(l,L);
}

double* descobreLambda(DecLU *l){
    double *u = resolveSistemaTransposto(l);
    return resolveSistemaInvertidoTransposto(l,u);
}

void trocaVetorB(DecLU* l, double* novoB){
    l->B = novoB;
}