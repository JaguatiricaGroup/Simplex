#include <stdio.h>
#include <stdlib.h>
// #include "src/decomposicaoLU.h"
#include "src/ioSimplex.h"
#include "src/simplex.h"
#define RANGE_NUMEROS_ALEATORIOS 20
#define TAMANHO 500

// void printMatriz(DecLU* l){
//     for (int i = 0; i < l->n; ++i) {
//         for (int j = 0; j < l->n ; ++j) {
//             printf(" %5.5lf ", (l->A)[i][j]);           
//         }
//         printf("| %5.5lf \n",l->B[i]);
//     }
//     printf("----\n");
// }

double** geraMatrizQuad(int Tam){
    double **L = malloc(sizeof(double*)*Tam);    
    for (int i=0; i < Tam; ++i) {
        L[i] = malloc(sizeof(double)*Tam);
        for (int j = 0; j < Tam; ++j) {
            L[i][j] = (rand()%RANGE_NUMEROS_ALEATORIOS)*((rand()%2) ? (-1):1) ;
        }
    } 
    return L;
}

double* geraVetorB(int tamanho){
   double* l = malloc(sizeof(double)*tamanho) ;
   for (int i = 0; i < tamanho; ++i) {
       l[i] = rand()%RANGE_NUMEROS_ALEATORIOS;
   }
   return l;
}

void printVetor(unsigned *v,int tamanho){
    for (int i = 0; i < tamanho; ++i) {
        printf("%u, \n",v[i] );
    }    
}

void printVetor1(double *v,int tamanho){
    for (int i = 0; i < tamanho; ++i) {
        printf("%0.3lf, ",v[i] );
    }    
    printf("\n");
}

char* nomeSaida(char nome[]){ 
    int i = 0;
    // int acheiBarra = 0;
    char *nomeS = malloc(sizeof(char)*150);
    nomeS  = "saida/solucao_";    
    for(i = 0; nome[i] ; i++){
        printf("%c",nome[i]);
        /*if( strcmp(nome[i],"/") ){*/
            /*acheiBarra = 1;*/
            /*i+=2;*/
        /*}*/
        /*if(acheiBarra){*/
            nomeS[13+i] = nome[i]; 
        /*}*/
    }
    return nomeS;
}

int main(int argc, char** argv){
    /*srand(7);*/
    /*double **A ;*/
    // DecLU* l;//= iniSimplex(geraMatrizQuad(TAMANHO),geraVetorB(TAMANHO),TAMANHO);*/
    // l = leLU(argv[1]);    
    // le(l);
    // escreveSimplex("solucao.txt",l);    
    Simplex* L = NULL;

    L = leSimplex(argv[1]);//"exemplo_entrada_saida/in8");
    double * solucao = simplex(L);
    printVetor1(solucao,L->n);
    /*printMatriz(l);*/
    /*printMatriz(l);*/
    /*int indPivo = escolhePivo(l,0);//teste pivo*/
    /*printf("%d\n", indPivo);*/
    /*aplicaMultiplicador(l,0,0,(((l->A)[1][0])/(l->A)[0][0]));*/
    /*printVetor(l->p,l->n);//teste troca linha*/
    /*trocaLinha(l,0,indPivo);*/
    /*printMatriz(l);*/
    /*double multiplicador = (((l->A)[1][0])/(l->A)[0][0]);*/
    /*printf("multi: %lf \n", multiplicador);*/
    /*aplicaMultiplicador(l,1,0,multiplicador);*/
    /*(l->A)[1][0] =multiplicador;*/
    /*printMatriz(l);*/
    /*multiplicador = (((l->A)[2][0])/(l->A)[0][0]);*/
    /*printf("multi: %lf \n",multiplicador);*/
    /*aplicaMultiplicador(l,2,0,multiplicador);*/
    /*(l->A)[2][0] = multiplicador;*/
    /*printMatriz(l);*/
    /*multiplicador = (((l->A)[2][1])/(l->A)[1][1]);*/
    /*printf("multi: %lf \n",multiplicador);*/
    /*aplicaMultiplicador(l,2,1,multiplicador);*/
    /*(l->A)[2][1] = multiplicador;*/
    /*printMatriz(l);*/
    /*printVetor(l->p,l->n);*/
    /*aplicaMultiplicador(l,0,1,2);*/
    /*le(l);*/
    /*printMatriz(l);*/
    /*printf("Fim\n");*/
    /*printMatriz(l);*/
    /*printVetor1(resolveSistema(l),l->n); */
    /*printVetor1(descobreX(l),l->n); */
    /*printVetor1(resolveSistemaInvertido(l,resolveSistema(l)),l->n);*/
    /*printVetor1(resolveSistema(l),l->n);*/

}
