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
 
bool menu_de_pause(jogador *jogador, cobra *cobra, char arena[altura][largura], bool comida_especial_ativada) {
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
            reiniciar_jogo(jogador, cobra, arena, comida_especial_ativada);
            break;
            
        case '2':
            sair_do_jogo = true;
            break;
            
        default:
            apresentar_opcao_invalida();
            menu_de_pause(jogador, cobra, arena, comida_especial_ativada); // entra em looping 
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
