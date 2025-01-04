#ifndef RANKING_H
#define RANKING_H

#include <stdio.h> 
#include <string.h> 
#include <stdbool.h>

#include "jogador.h"

// Funções relacionadas ao ranking
int ler_ranking_do_arquivo(FILE *f2, jogador ranking[300]);
void ordenar_ranking(jogador ranking[], bool ranquear_por_mapa);
void imprimir_ranking(jogador ranking[300]);

#endif // RANKING_H

