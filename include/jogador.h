#ifndef JOGADOR_H
#define JOGADOR_H

#include <stdio.h>
#include <time.h>

// Estrutura do jogador
typedef struct  {
    char nome_jogador[12];
    int pontuacao;
    char tempo_jogado[10];
} jogador;

// Funções relacionadas ao jogador
void pedir_nome(jogador *jogador);
void cronometrar_tempo(jogador* dados, clock_t tempo_inicial);
void salvar_dados_jogador(jogador jogador);

#endif
