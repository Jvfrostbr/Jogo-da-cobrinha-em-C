#ifndef COBRA_H
#define COBRA_H

#include <stdbool.h>
#include "config.h"
#include "jogador.h"
#include "timer.h"

// Estrutura da cobra
typedef struct {
    int cabeca_x, cabeca_y;
    int comida_x, comida_y;
    int comida_especial_x, comida_especial_y;
    int corpo_cobra[250][2];
    int tamanho_cobra;
    char simbolo_cobra;
} cobra;

// Funções relacionadas à cobra
void imprimir_cobra(cobra *cob, int cabeca_x_anterior, int cabeca_y_anterior);
void mover_cobra(cobra *cobra);
bool verificar_colisao(cobra dados_snk, int arena_int[altura][largura]);
void gerar_comida(cobra *cob, char arena[altura][largura], int arena_int[altura][largura], bool comida_especial_ativada);
bool verificar_se_cobra_comeu(cobra dados_cobra);
bool verificar_se_cobra_comeu_especial(cobra dados_cobra, Timer *timer_comida_especial);

#endif
