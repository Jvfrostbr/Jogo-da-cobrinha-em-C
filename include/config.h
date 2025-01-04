#ifndef CONFIG_H
#define CONFIG_H

#include <sys/time.h>
#include <stdbool.h>

// Definições globais
#define altura 29
#define largura 100

// Declarações de variáveis globais
extern char tempo_formatado[6];
extern char tempo_ativacao_timer_formatado[6];
extern char ultima_direcao; 
extern struct timeval tempo_atual;
extern int mapa_selecionado;
extern bool comida_especial_ativada;
extern int qtd_preenchido_array;
#endif
