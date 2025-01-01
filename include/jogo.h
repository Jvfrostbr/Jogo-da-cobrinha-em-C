#ifndef JOGO_H
#define JOGO_H

#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

#include "cobra.h"
#include "jogador.h"
#include "tela.h"

void inicializar_jogo(jogador *jogador, cobra *cobra, char arena[altura][largura]);
void reiniciar_jogo(jogador *jogador, cobra *cobra, char arena[altura][largura], bool comida_especial_ativada);
int aumentar_velocidade_jogo(int tamanho_cobra);
void calcular_diferenca_tempo(struct timeval *inicio, struct timeval *fim, struct timeval *tempo_de_pause);
void ajustar_tempo_inicial_com_pausa(struct timeval *tempo_inicial, struct timeval *tempo_pausa);
#endif // JOGO_H

