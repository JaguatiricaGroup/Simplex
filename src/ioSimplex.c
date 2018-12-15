#include "ioSimplex.h"
#include "simplex.h"
#include <stdlib.h>
#include <stdio.h>
// #include "decomposicaoLU.h"
Simplex* leSimplex(char* nomeInstancia){
    FILE* instancia = fopen( nomeInstancia, "r" );
    int n,m=0;    
    Simplex *L = NULL;        
    if(!ferror(instancia)){
        fscanf(instancia,"%d,%d\n",&m,&n);
        L = iniSimplex(m,n);
        // printf("%d %d\n", m,n);
        /*double A[10][10];*/
        for (int i = 0; i < m; ++i) {
            for (int l = 0; l  < n; ++l ) {                
                fscanf(instancia,"%lf ",&((L->A)[i][l]));
                // printf("%lf ",((L->A)[i][l]));
            }
            // printf("\n");
        } 
        for (int l = 0; l  < m; ++l ) {            
            fscanf(instancia,"%lf ", &((L->b)[l]));
            // printf("%f ",((L->b)[l]));            
        }                  
        // printf("\n");
        for (int l = 0; l  < n; ++l ) {            
            fscanf(instancia,"%lf ", &((L->c)[l]));
            // printf("%f ",((L->c)[l]));
        }            
        // printf("\n");      
    }
    fclose(instancia);
    return L;
}

DecLU* leLU(char* nomeInstancia){
    FILE* instancia = fopen( nomeInstancia, "r" );
    int aux=0;    
    DecLU *L = NULL;    
    if(!ferror(instancia)){
        fscanf(instancia,"%d\n",&aux);
        L = alocaLU(aux);
        /*printf("%d\n", aux);*/
        /*double A[10][10];*/
        for (int i = 0; i < aux; ++i) {
            for (int l = 0; l  < aux; ++l ) {                
                fscanf(instancia,"%lf ",&((L->A)[i][l]));
                /*printf("%f",((L->A)[i][l]));*/
            }
        } 
        for (int l = 0; l  < aux; ++l ) {            
            fscanf(instancia,"%lf ", &((L->B)[l]));
            /*printf("%f",((L->B)[l]));*/
        }                  
    }
    fclose(instancia);
    return L;
}

void escreveU(DecLU* l,FILE* instancia){
    fprintf(instancia, "U = \n");
    int k =0; 
    for(int i =0; i < l->n ; i++){
        for(int j = 0; j < k; j++){       
            double aux = 0;     
            fprintf(instancia," %-10.3f ", aux);      
        }
        for(int j =k; j < l->n ; j++){
            fprintf(instancia," %-10.3f ", (l->A)[i][j]);           
        /*fprintf(instancia, " = \n");*/
        }
        fprintf(instancia,"\n");
        k++;
    }
}

void escreveL(DecLU* l,FILE* instancia){
    fprintf(instancia, "L = \n");
    int k=0;
    for(int i =0; i < l->n ; i++,k++){        
        for(int j = 0; j < k; j++){
            fprintf(instancia," %-10.3f ", (l->A)[i][j]);
        }
        double aux1 = 1;
        fprintf(instancia," %-10.3f ", aux1);               
        for(int j = k+1; j < l->n ; j++){ 
            double aux = 0;     
            fprintf(instancia," %-10.3f ", aux);      
        }
        fprintf(instancia,"\n");        
    }

}

void escreveP(DecLU* l,FILE* instancia){
    fprintf(instancia, "P = \n");
    int k=0;
    for(int i =0; i < l->n ; i++,k++){        
        fprintf(instancia," %u ", l->p[i]);
    }    
    fprintf(instancia,"\n");          
}

void escreveSolucao(DecLU* l,FILE* instancia,double* L,char* titulo){
    fprintf(instancia, titulo);
    for(int i =0; i < l->n ; i++){ 
        fprintf(instancia," %-10.3f  ", L[i]);
    }
    fprintf(instancia,"\n");
}

void escreveSimplex(char* nomeSolucao,DecLU* l){
    FILE* instancia;
    instancia = fopen(nomeSolucao,"w");
    escreveL(l,instancia);
    escreveU(l,instancia);       
    escreveP(l,instancia);
    escreveSolucao(l,instancia,descobreX(l),"X =\n");
    /*escreveSolucao(l,instancia,descobreLambda(l),"Lambda =\n");*/
    double* L = descobreLambda(l);
    fprintf(instancia, "Lambda =\n");
    /*for(int i =l->n-1; i >=0 ; --i){ */
    for(int i =0; i <l->n ; ++i){ 
        fprintf(instancia," %-10.3f  ", L[l->p[i]]);
    }
    fprintf(instancia,"\n");
    fclose(instancia);
}
