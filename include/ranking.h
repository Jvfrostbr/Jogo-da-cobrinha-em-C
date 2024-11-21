#ifndef RANKING_H
#define RANKING_H

#include <stdio.h> // Para FILE, printf, etc.
#include <string.h> // Para manipulação de strings

#include "jogador.h"

// Funções relacionadas ao ranking
void ler_ranking_do_arquivo(FILE *f2, jogador ranking[300]);
void ordenar_ranking(jogador ranking[300]);
void imprimir_ranking(jogador ranking[300]);

#endif // RANKING_H

