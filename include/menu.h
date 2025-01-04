#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

#include "jogador.h"
#include "cobra.h"
#include "config.h" 
#include "musica.h" 

// Fun��es relacionadas a menus
bool menu_de_pause(jogador *jogador, cobra *cobra, char arena[altura][largura], int arena_int[altura][largura], bool comida_especial_ativada);
char menu_principal(bool *musica_principal_tocando);
int menu_selecionar_mapa();
int menu_selecionar_mapa_ranking();
int menu_tipo_ranking();
#endif 
