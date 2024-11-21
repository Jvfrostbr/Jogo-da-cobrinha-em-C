#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cobra.h"
#include "jogador.h"
#include "tela.h"
#include "teclado.h"
#include "config.h"
#include "jogo.h"

void inicializar_jogo(jogador *jogador, cobra *cobra, char arena[altura][largura]) {
    criar_arena(arena);

    jogador->pontuacao = 0;
    strcpy(jogador->tempo_jogado, "00 : 00");

    cobra->simbolo_cobra = 219;
    cobra->tamanho_cobra = 2;
    cobra->cabeca_x = (largura - 1) / 2;
    cobra->cabeca_y = altura / 2;
 
    gerar_comida(cobra, arena);
    ultima_direcao = 'a';
}

int aumentar_velocidade(int tamanho_cobra) {
    static int delay_inicial = 200;
    int delay;

    // Reduz o delay em 5 milissegundos para cada segmento da cobra
    delay = delay_inicial - (tamanho_cobra * 5);

    // Define um limite mínimo para o delay
    if (delay < 50) {
        delay = 50;
    }

    return delay;
}

