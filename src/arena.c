#include <stdio.h>

#include "arena.h"
#include "config.h" // Inclui o arquivo com as globais

// Função para criar a arena de jogo
void criar_arena(char area[altura][largura]) {
    int i, j;
    for (i = 0; i < altura + 1; i++) {
        for (j = 0; j < largura + 1; j++) {
            area[i][j] = ' ';

            // Se i ou j estiver nas bordas da arena, imprime o caractere de espaço com fundo branco
            if (i == 1 && j != 0 || i == altura && j != 0 || j == 1 && i != 0 || j == largura && i != 0) {
                printf("\033[1;47m%c\033[0m", area[i][j]);
            } else {
                printf("%c", area[i][j]);
            }
        }
        printf("\n");
    }
}
