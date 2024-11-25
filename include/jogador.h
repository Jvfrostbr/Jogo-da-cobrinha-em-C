#ifndef JOGADOR_H
#define JOGADOR_H

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

// Estrutura do jogador
typedef struct  {
    char nome_jogador[12];
    int pontuacao;
    char tempo_jogado[6];
} jogador;

// Funções relacionadas ao jogador
void pedir_nome(jogador *jogador);
void cronometrar_tempo(jogador* dados, struct timeval tempo_inicial);
void salvar_dados_jogador(jogador jogador);

#endif
