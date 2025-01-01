#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <time.h>

typedef struct {
    struct timeval tempo_inicial_para_ativacao; 
	struct timeval tempo_inicial_da_pausa; 		
	struct timeval tempo_inicial_da_ativacao;
	int duracao_para_ativacao; 		 
    int duracao_da_ativacao;       
	int duracao_da_pausa; 	    	
    bool contando_tempo_ate_ativacao; 
	bool contando_tempo_durante_ativacao;     	    	
    bool pausado;        		
} Timer;

void iniciar_timer(Timer *timer, int duracao_para_ativacao, int duracao_da_ativacao, int duracao_da_pausa);
void ativar_tempo_de_ativacao(Timer *timer);
void pausar_timer(Timer *timer);
void reativar_timer(Timer *timer);
int verificar_tempo_da_ativacao(Timer *timer);
int verificar_tempo_para_ativacao(Timer *timer);
int verificar_tempo_de_pausa(Timer *timer);
void calcular_diferenca_tempo_timer(Timer *timer, struct timeval *fim, struct timeval *tempo_de_pause);
void ajustar_tempo_timer_com_pausa(Timer *timer, struct timeval *tempo_pausa);
#endif

