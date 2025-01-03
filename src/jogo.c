#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>


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
 
    gerar_comida(cobra, arena, false);
    ultima_direcao = 'a';
}

void reiniciar_jogo(jogador *jogador, cobra *cobra, char arena[altura][largura], bool comida_especial_ativada) {
    // Recria a arena
    criar_arena(arena);
    
    // Reimprime a pontua��o e o tempo
    imprimir_pontuacao(jogador);
    imprimir_tempo();
    
    // Reimprime a cobra e a comida
    imprimir_cobra(cobra, cobra->corpo_cobra[0][0], cobra->corpo_cobra[0][1]);
    arena[cobra->comida_y][cobra->comida_x] = 32;
    imprimir_comida(cobra, arena, false); // reimprime a comida normal
    
    if(comida_especial_ativada){
    	arena[cobra->comida_especial_y][cobra->comida_especial_x] = 32;
    	imprimir_comida(cobra, arena, comida_especial_ativada); // reimprime a comida especial
	}
}

int aumentar_velocidade_jogo(int tamanho_cobra) {
    static int delay_inicial = 200;
    int delay;

    // Reduz o delay em 5 milissegundos para cada segmento da cobra
    delay = delay_inicial - (tamanho_cobra * 5);

    // Define um limite m�nimo para o delay
    if (delay < 40) {
        delay = 40;
    }

    return delay;
}

void calcular_diferenca_tempo(struct timeval *inicio, struct timeval *fim, struct timeval *tempo_de_pause) {
    tempo_de_pause->tv_sec = fim->tv_sec - inicio->tv_sec;
    tempo_de_pause->tv_usec = fim->tv_usec - inicio->tv_usec;

    // Ajuste para evitar valores negativos em tv_usec
    if (tempo_de_pause->tv_usec < 0) {
        tempo_de_pause->tv_sec -= 1;
        tempo_de_pause->tv_usec += 1000000;
    }
}

void ajustar_tempo_inicial_com_pausa(struct timeval *tempo_inicial, struct timeval *tempo_pausa) {
    // Soma a dura��o do tempo de pausa ao tempo inicial pois o tempo de pausa � um valor negativo 
    tempo_inicial->tv_sec += tempo_pausa->tv_sec;
    tempo_inicial->tv_usec += tempo_pausa->tv_usec;

    // Ajuste para o caso de tv_usec ultrapassar 1 segundo (1.000.000 microsegundos)
    if (tempo_inicial->tv_usec >= 1000000) {
        tempo_inicial->tv_sec += tempo_inicial->tv_usec / 1000000;
        tempo_inicial->tv_usec %= 1000000;
    }
}

