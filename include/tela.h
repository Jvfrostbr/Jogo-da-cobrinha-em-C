#ifndef Tela_H
#define TELA_H

#include <windows.h>
#include "jogador.h"
#include "config.h"

// Funções relacionadas a tela
void redimensionar_terminal(int largura_terminal, int altura_terminal);
void ocultar_cursor();
void exibir_cursor();
void posicionar_cursor(int x, int y);
void imprimir_pontuacao(jogador* dados);

#endif 
