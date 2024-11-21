#ifndef COBRA_H
#define COBRA_H

#include <stdbool.h>
#include "config.h"

// Estrutura da cobra
typedef struct {
    int cabeca_x, cabeca_y;
    int comida_x, comida_y;
    int corpo_cobra[100][2];
    int tamanho_cobra;
    char simbolo_cobra;
} cobra;

// Funções relacionadas à cobra
void imprimir_cobra(cobra *cob, int cabeca_x_anterior, int cabeca_y_anterior);
void mover_cobra(cobra *pos_atual);
bool verificar_colisao(cobra dados_snk);
void gerar_comida(cobra *cob, char arena[altura][largura]);
bool verificar_se_cobra_comeu(cobra dados_cobra);

#endif
