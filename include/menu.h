#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

#include "jogador.h"
#include "cobra.h"
#include "config.h" 

// Funções relacionadas a menus
bool menu_de_pause(jogador *jogador, cobra *cobra, char arena[altura][largura]);
char menu_principal();
#endif 
