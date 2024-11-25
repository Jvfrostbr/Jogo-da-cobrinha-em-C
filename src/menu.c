#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "tela.h"
#include "ranking.h"
#include "cobra.h"
#include "jogador.h"
#include "jogo.h"
#include "tela.h"

 

bool menu_de_pause(jogador *jogador, cobra *cobra, char arena[altura][largura]) {
    bool sair_do_jogo = false;
    char opcao;
    
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // Limpa o buffer de entrada do console
	exibir_cursor();
	  
    system("cls");
    printf("\n\n\t\t\t\t\t|-----------------------------------|\n"
           "\t\t\t\t\t|                                   |\n"
           "\t\t\t\t\t|              PAUSE                |\n"
           "\t\t\t\t\t|                                   |\n"
           "\t\t\t\t\t|          1- Continuar             |\n"
           "\t\t\t\t\t|                                   |\n"
           "\t\t\t\t\t|          2- Sair                  |\n"
           "\t\t\t\t\t|                                   |\n"
           "\t\t\t\t\t|-----------------------------------|\n\n\t\t\t\t\t\t\t");
    scanf(" %c", &opcao);  
	
	ocultar_cursor();
    switch (opcao) {
        case '1':
            system("cls");
            strcpy(tempo_formatado, jogador->tempo_jogado); //lihha necessária para que a memória da variável não seja preenchida com lixo de memória
            reiniciar_jogo(jogador, cobra, arena);
            break;
            
        case '2':
            sair_do_jogo = true;
            break;
            
        default:
            apresentar_opcao_invalida();
            menu_de_pause(jogador, cobra, arena); // entra em looping 
            break;
    }
    return sair_do_jogo;
}

char menu_principal() {
    char opcao;

    imprimir_snake_menu(); 
    imprimir_opcoes_menu_cobra();
    posicionar_cursor(61,32);

    scanf(" %c", &opcao);
    return opcao;
}
