#ifndef JOGO_H
#define JOGO_H

#include <time.h>
#include "cobra.h"
#include "jogador.h"
#include "tela.h"

// Fun��es relacionadas � l�gica do jogo
void inicializar_jogo(jogador *jogador, cobra *cobra, char arena[altura][largura]);
int aumentar_velocidade(int tamanho_cobra);

#endif // JOGO_H

