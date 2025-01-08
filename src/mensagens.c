#include <stdio.h>
#include <windows.h> 

#include "mensagens.h"
#include "jogador.h" 
#include "musica.h"

// Fun��o para exibir o aviso sobre encoding
void apresentar_aviso_encoding() {
    printf(
        "\n\n\n\n\t\t\t\033[1;31m      |-------------------------------------------------------------|\n"
        "\t\t\t      |                                                             |\n"
        "\t\t\t      |    Aviso: Este c�digo foi desenvolvido no Dev-C++           |\n"
        "\t\t\t      |                                                             |\n"
        "\t\t\t      |    Caso a exibi��o de alguns caracteres especiais esteja    |\n"
        "\t\t\t      |    esquisita, isso se deve por conta da sua IDE ter um      |\n"
        "\t\t\t      |    encoding diferente.                                      |\n"
        "\t\t\t      |                                                             |\n"
        "\t\t\t      |    Certifique que tenha o Dev-C++ instalado na sua m�quina  |\n"
        "\t\t\t      |    para uma melhor experi�ncia e exibi��o dos caracteres.   |\n"
        "\t\t\t      |                                                             |\n"
        "\t\t\t      |-------------------------------------------------------------|\n\n"
        "\033[0m"
    );
    Sleep(7000);
    system("cls");
}

// Fun��o para exibir a tela de fim de jogo
void apresentar_game_over(jogador print_dados) {
	
    system("cls");
    printf("\n\n\t\t\t\t\t     |-----------------------------------|\n"
           "\t\t\t\t\t     |                                   |\n"
           "\t\t\t\t\t     |            Fim de jogo            |\n"
           "\t\t\t\t\t     |                                   |\n"
           "\t\t\t\t\t     |       Jogador: %-10s         |\n"
           "\t\t\t\t\t     |                                   |\n"
           "\t\t\t\t\t     |       Pontua��o: %-4d             |\n"
           "\t\t\t\t\t     |                                   |\n"
           "\t\t\t\t\t     |       Tempo: %-10s           |\n"
           "\t\t\t\t\t     |                                   |\n"
           "\t\t\t\t\t     |-----------------------------------|",
           print_dados.nome_jogador, print_dados.pontuacao, print_dados.tempo_jogado);
    tocar_som_gameover();
    Sleep(5000);
    system("cls");
}

// Fun��o para exibir uma mensagem de op��o inv�lida
void apresentar_opcao_invalida() {
    system("cls");
    printf("\n\n\t\t\t\t|----------------------------------|\n"
           "\t\t\t\t|                                  |\n"
           "\t\t\t\t|     Digite uma op��o v�lida!     |\n"
           "\t\t\t\t|                                  |\n"
           "\t\t\t\t|----------------------------------|\n");
    Sleep(3000);			
    system("cls");
}

void apresentar_controles(){
	system("cls");
	printf("\n\n\t\t\t\t\t|-----------------------------------------|"
	   	   "\n\t\t\t\t\t|                                         |"
	       "\n\t\t\t\t\t|     Controles:                          |"
	       "\n\t\t\t\t\t|                                         |"
	       "\n\t\t\t\t\t|         cima:      W                    |"
	       "\n\t\t\t\t\t|                                         |"
	       "\n\t\t\t\t\t|         Esquerda:  A                    |"
	       "\n\t\t\t\t\t|                                         |"
	       "\n\t\t\t\t\t|         Baixo:     S                    |"
	       "\n\t\t\t\t\t|                                         |"
	       "\n\t\t\t\t\t|         Direita:   D                    |"
	       "\n\t\t\t\t\t|                                         |"
	       "\n\t\t\t\t\t|         Pause:     P                    |"
	       "\n\t\t\t\t\t|                                         |"
	       "\n\t\t\t\t\t|-----------------------------------------|");
	Sleep(5000);
	system("cls");
}
