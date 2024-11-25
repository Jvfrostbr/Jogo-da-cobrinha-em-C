#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

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
		
    cobra->simbolo_cobra = 32;
    cobra->tamanho_cobra = 2;
    cobra->cabeca_x = (largura - 1) / 2;
    cobra->cabeca_y = altura / 2;
 

    gerar_comida(cobra, arena);
    ultima_direcao = 'a';
}

void reiniciar_jogo(jogador *jogador, cobra *cobra, char arena[altura][largura]) {
    // Recria a arena
    criar_arena(arena);
    
    // Reimprime a pontua��o e o tempo
    imprimir_pontuacao(jogador);
    imprimir_tempo();
    
    // Reimprime a cobra e a comida
    imprimir_cobra(cobra, cobra->corpo_cobra[0][0], cobra->corpo_cobra[0][1]);
    arena[cobra->comida_y][cobra->comida_x] = 219;
    printf("\033[1;31m\033[%d;%dH%c\033[0m", cobra->comida_y + 1, cobra->comida_x + 1, arena[cobra->comida_y][cobra->comida_x]);
}

int aumentar_velocidade_jogo(int tamanho_cobra) {
    static int delay_inicial = 200;
    int delay;

    // Reduz o delay em 5 milissegundos para cada segmento da cobra
    delay = delay_inicial - (tamanho_cobra * 5);

    // Define um limite m�nimo para o delay
    if (delay < 50) {
        delay = 50;
    }

    return delay;
}

void calcular_diferenca_tempo(struct timeval *inicio, struct timeval *fim, struct timeval *resultado) {
    resultado->tv_sec = fim->tv_sec - inicio->tv_sec;
    resultado->tv_usec = fim->tv_usec - inicio->tv_usec;

    // Ajuste para evitar valores negativos em tv_usec
    if (resultado->tv_usec < 0) {
        resultado->tv_sec -= 1;
        resultado->tv_usec += 1000000;
    }
}

void ajustar_tempo_inicial_com_pausa(struct timeval *tempo_inicial, struct timeval *tempo_pausa) {
    // Soma o tempo de pausa ao tempo inicial
    tempo_inicial->tv_sec += tempo_pausa->tv_sec;
    tempo_inicial->tv_usec += tempo_pausa->tv_usec;

    // Ajuste para o caso de tv_usec ultrapassar 1 segundo (1.000.000 microsegundos)
    if (tempo_inicial->tv_usec >= 1000000) {
        tempo_inicial->tv_sec += tempo_inicial->tv_usec / 1000000;
        tempo_inicial->tv_usec %= 1000000;
    }
}

