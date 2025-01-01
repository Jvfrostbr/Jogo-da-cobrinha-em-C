#include "timer.h"
#include <stdio.h>

static struct timeval tempo_atual;

void iniciar_timer(Timer *timer, int duracao_para_ativacao, int duracao_da_ativacao, int duracao_da_pausa){
    
	// Obtendo o tempo atual e armazenando em tempo_inicial_para_ativacao
    gettimeofday(&tempo_atual, NULL);
    timer->tempo_inicial_para_ativacao = tempo_atual;
    
    timer->duracao_para_ativacao = duracao_para_ativacao;   
	timer->duracao_da_ativacao = duracao_da_ativacao;   
	timer->duracao_da_pausa = duracao_da_pausa; 
    timer->contando_tempo_ate_ativacao = true;   
	timer->contando_tempo_durante_ativacao = false;                 
    timer->pausado = false;
}

void ativar_tempo_de_ativacao(Timer *timer){
	gettimeofday(&tempo_atual, NULL);
	
	timer->contando_tempo_ate_ativacao = false;
	timer->contando_tempo_durante_ativacao = true;
	timer->tempo_inicial_da_ativacao = tempo_atual;
}

void pausar_timer(Timer *timer){
    	
    timer->contando_tempo_durante_ativacao = false;
    timer->pausado = true;
    timer->tempo_inicial_da_pausa = tempo_atual;
}

void reativar_timer(Timer *timer){
	gettimeofday(&tempo_atual, NULL);
	
	timer->contando_tempo_ate_ativacao = true;
	timer->pausado = false;  
	timer->tempo_inicial_para_ativacao = tempo_atual; // Reinicia o timer após a pausa

}

int verificar_tempo_para_ativacao(Timer *timer) {
    int tempo_restante;

    if (!timer->contando_tempo_ate_ativacao) {
        tempo_restante = -1; // Timer inativo, retorna -1
    } else {
        struct timeval agora;
        gettimeofday(&agora, NULL);

        tempo_restante = timer->duracao_para_ativacao - (int)(agora.tv_sec - timer->tempo_inicial_para_ativacao.tv_sec);

        if (tempo_restante <= 0) {
            timer->contando_tempo_ate_ativacao = false;
            tempo_restante = 0;
        }
    }

    return tempo_restante;
}

int verificar_tempo_da_ativacao(Timer *timer) {
    int tempo_restante;

    if (!timer->contando_tempo_durante_ativacao) {
        tempo_restante = -1; // Timer inativo, retorna -1
    } else {
        struct timeval agora;
        gettimeofday(&agora, NULL);

        tempo_restante = timer->duracao_da_ativacao - (int)(agora.tv_sec - timer->tempo_inicial_da_ativacao.tv_sec);

        if (tempo_restante <= 0) {
            timer->contando_tempo_durante_ativacao = false;
            tempo_restante = 0;
        }
    }

    return tempo_restante;
}

int verificar_tempo_de_pausa(Timer *timer) {
    int tempo_restante;

    if (!timer->pausado) {
        tempo_restante = -1; // Timer não está pausado
    } else {
        struct timeval agora;
        gettimeofday(&agora, NULL);

        tempo_restante = timer->duracao_da_pausa - (int)(agora.tv_sec - timer->tempo_inicial_da_pausa.tv_sec);

        if (tempo_restante <= 0) {
            timer->pausado = false;
            tempo_restante = 0;
        }
    }

    return tempo_restante;
}


void calcular_diferenca_tempo_timer(Timer *timer, struct timeval *fim, struct timeval *tempo_de_pause){
    if (timer->contando_tempo_ate_ativacao) {
        tempo_de_pause->tv_sec = fim->tv_sec - timer->tempo_inicial_para_ativacao.tv_sec;
        tempo_de_pause->tv_usec = fim->tv_usec - timer->tempo_inicial_para_ativacao.tv_usec;
    } 
    else if (timer->contando_tempo_durante_ativacao) {
        tempo_de_pause->tv_sec = fim->tv_sec - timer->tempo_inicial_da_ativacao.tv_sec;
        tempo_de_pause->tv_usec = fim->tv_usec - timer->tempo_inicial_da_ativacao.tv_usec;
    } 
    else {
        tempo_de_pause->tv_sec = fim->tv_sec - timer->tempo_inicial_da_pausa.tv_sec;
        tempo_de_pause->tv_usec = fim->tv_usec - timer->tempo_inicial_da_pausa.tv_usec;
    }

    // Ajuste para valores negativos ou ultrapassando 1 segundo
    if (tempo_de_pause->tv_usec < 0) {
        tempo_de_pause->tv_sec -= 1;
        tempo_de_pause->tv_usec += 1000000;
    } 
    else if (tempo_de_pause->tv_usec >= 1000000) {
        tempo_de_pause->tv_sec += tempo_de_pause->tv_usec / 1000000;
        tempo_de_pause->tv_usec %= 1000000;
    }
}

void ajustar_tempo_timer_com_pausa(Timer *timer, struct timeval *tempo_pausa){
    if (timer->contando_tempo_ate_ativacao) {
        timer->tempo_inicial_para_ativacao.tv_sec += tempo_pausa->tv_sec;
        timer->tempo_inicial_para_ativacao.tv_usec += tempo_pausa->tv_usec;

        // Ajuste para quando tv_usec ultrapassa 1 segundo
        if (timer->tempo_inicial_para_ativacao.tv_usec >= 1000000) {
            timer->tempo_inicial_para_ativacao.tv_sec += timer->tempo_inicial_para_ativacao.tv_usec / 1000000;
            timer->tempo_inicial_para_ativacao.tv_usec %= 1000000;
        }
    } else if (timer->contando_tempo_durante_ativacao) {
        timer->tempo_inicial_da_ativacao.tv_sec += tempo_pausa->tv_sec;
        timer->tempo_inicial_da_ativacao.tv_usec += tempo_pausa->tv_usec;

        if (timer->tempo_inicial_da_ativacao.tv_usec >= 1000000) {
            timer->tempo_inicial_da_ativacao.tv_sec += timer->tempo_inicial_da_ativacao.tv_usec / 1000000;
            timer->tempo_inicial_da_ativacao.tv_usec %= 1000000;
        }
    } else {
        timer->tempo_inicial_da_pausa.tv_sec += tempo_pausa->tv_sec;
        timer->tempo_inicial_da_pausa.tv_usec += tempo_pausa->tv_usec;

        if (timer->tempo_inicial_da_pausa.tv_usec >= 1000000) {
            timer->tempo_inicial_da_pausa.tv_sec += timer->tempo_inicial_da_pausa.tv_usec / 1000000;
            timer->tempo_inicial_da_pausa.tv_usec %= 1000000;
        }
    }
}
