#include "decomposicaoLU.h"
#include "simplex.h"
#ifndef IOSIMPLEX_H
#define IOSIMPLEX_H
DecLU* leLU(char* nomeInstancia);
Simplex* leSimplex(char* nomeInstancia);
void escreveSimplex(char* nomeSolucao,DecLU *l);
#endif /* ifndef IOSIMPLEX_H */
