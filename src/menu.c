#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <stdbool.h>

#include "tela.h"
#include "ranking.h"
#include "cobra.h"
#include "jogador.h"
#include "jogo.h"
#include "tela.h"
#include "musica.h" 
 
bool menu_de_pause(jogador *jogador, cobra *cobra, char arena[altura][largura], int arena_int[altura][largura], bool comida_especial_ativada) {
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
            strcpy(tempo_formatado, jogador->tempo_jogado); //linha necessária para que a memória da variável não seja preenchida com lixo de memória
            reiniciar_jogo(jogador, cobra, arena, arena_int, comida_especial_ativada);
            break;
            
        case '2':
            sair_do_jogo = true;
            break;
            
        default:
            apresentar_opcao_invalida();
            menu_de_pause(jogador, cobra, arena, arena_int, comida_especial_ativada); // entra em looping 
            break;
    }
    return sair_do_jogo;
}

char menu_principal(bool *musica_principal_tocando) {
    char opcao;
	
// Verifica se a música não está tocando antes de iniciar
    if (!(*musica_principal_tocando)) {
        tocar_musica_principal();
        *musica_principal_tocando = true; // Atualiza para indicar que a música está tocando
    }
	
    imprimir_snake_menu(); 
    imprimir_opcoes_menu_cobra();
    posicionar_cursor(61,32);

    scanf(" %c", &opcao);
    return opcao;
}

int menu_selecionar_mapa() {
    int mapa_selecionado = 0;
    char opcao;

    system("cls"); // Limpa o console (use "clear" no Linux/MacOS)
    printf("\n\n\t\t\t\t|-----------------------------------------------------------|\n"
           "\t\t\t\t|                                                           |\n"
           "\t\t\t\t|          Selecione o mapa que você deseja jogar:          |\n"
           "\t\t\t\t|                                                           |\n"
           "\t\t\t\t|             1- mapa 1       |       5- mapa 5             |\n"
           "\t\t\t\t|                             |                             |\n"
           "\t\t\t\t|             2- mapa 2       |       6- mapa 6             |\n"
           "\t\t\t\t|                             |                             |\n"
           "\t\t\t\t|             3- mapa 3       |       7- mapa 7             |\n"
           "\t\t\t\t|                             |                             |\n"
           "\t\t\t\t|             4- mapa 4       |       8- Aleatório          |\n"
           "\t\t\t\t|                             |                             |\n"
           "\t\t\t\t|                                                           |\n"
           "\t\t\t\t|-----------------------------------------------------------|\n\n\t\t\t\t\t\t\t");
    scanf(" %c", &opcao);

    switch (opcao) {
        case '1':
            mapa_selecionado = 1;
            break;

        case '2':
            mapa_selecionado = 2;
            break;

        case '3':
            mapa_selecionado = 3;
            break;

        case '4':
            mapa_selecionado = 4;
            break;

        case '5':
            mapa_selecionado = 5;
            break;
            
        case '6':
        	mapa_selecionado = 6;
			break;
			
        case '7':
        	mapa_selecionado = 7;
			break;
			
        default:
            apresentar_opcao_invalida();
            menu_selecionar_mapa();
            break;
    }
    
    system("cls");
    return mapa_selecionado;
}

int menu_selecionar_mapa_ranking() {
    int mapa_selecionado = 0;
    char opcao;

    system("cls"); // Limpa o console (use "clear" no Linux/MacOS)
    printf("\n\n\t\t\t\t|-----------------------------------------------------------|\n"
           "\t\t\t\t|                                                           |\n"
           "\t\t\t\t|      Selecione o mapa que você deseja ver o ranking:      |\n"
           "\t\t\t\t|                                                           |\n"
           "\t\t\t\t|             1- mapa 1       |       5- mapa 5             |\n"
           "\t\t\t\t|                             |                             |\n"
           "\t\t\t\t|             2- mapa 2       |       6- mapa 6             |\n"
           "\t\t\t\t|                             |                             |\n"
           "\t\t\t\t|             3- mapa 3       |       7- mapa 7             |\n"
           "\t\t\t\t|                             |                             |\n"
           "\t\t\t\t|             4- mapa 4       |                             |\n"
           "\t\t\t\t|                             |                             |\n"
           "\t\t\t\t|                             |                             |\n"
           "\t\t\t\t|                                                           |\n"
           "\t\t\t\t|-----------------------------------------------------------|\n\n\t\t\t\t\t\t\t");
    scanf(" %c", &opcao);

    switch (opcao) {
        case '1':
            mapa_selecionado = 1;
            break;

        case '2':
            mapa_selecionado = 2;
            break;

        case '3':
            mapa_selecionado = 3;
            break;

        case '4':
            mapa_selecionado = 4;
            break;

        case '5':
            mapa_selecionado = 5;
            break;
            
        case '6':
        	mapa_selecionado = 6;
			break;
			
		case '7':
        	mapa_selecionado = 7;
			break;
					
        default:
            apresentar_opcao_invalida();
            menu_selecionar_mapa();
            break;
    }
    
    system("cls");
    return mapa_selecionado;
}

int menu_tipo_ranking() {
    int opcao_selecionada = 0;
    char opcao;

    system("cls"); // Limpa o console (use "clear" no Linux/MacOS)
    printf("\n\n\t\t\t\t|-----------------------------------------------------------|\n"
           "\t\t\t\t|                                                           |\n"
           "\t\t\t\t|          Selecione o tipo de ranking que deseja ver:      |\n"
           "\t\t\t\t|                                                           |\n"
           "\t\t\t\t|                1- Ranking Geral                           |\n"
           "\t\t\t\t|                                                           |\n"
           "\t\t\t\t|                2- Ranking por Mapa                        |\n"
           "\t\t\t\t|                                                           |\n"
           "\t\t\t\t|-----------------------------------------------------------|\n\n\t\t\t\t\t\t\t");
    scanf(" %c", &opcao);

    switch (opcao) {
        case '1':
            opcao_selecionada = 1; // Ranking Geral
            break;

        case '2':
            opcao_selecionada = 2; // Ranking por Mapa
            break;

        default:
            apresentar_opcao_invalida();
            menu_tipo_ranking();
            break;
    }
    
    system("cls");
    return opcao_selecionada;
}
