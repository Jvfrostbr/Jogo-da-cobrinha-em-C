#ifndef Tela_H
#define TELA_H

#include <windows.h>
#include "jogador.h"
#include "config.h"
#include "cobra.h"

// Fun��es relacionadas a tela
void redimensionar_terminal(int largura_terminal, int altura_terminal);
void ocultar_cursor();
void exibir_cursor();
void posicionar_cursor(int x, int y);
void imprimir_pontuacao(jogador* dados);
void imprimir_opcoes_menu_cobra();
void imprimir_snake_menu();
void imprimir_comida(cobra *cob, char arena[altura][largura]);

#endif 
