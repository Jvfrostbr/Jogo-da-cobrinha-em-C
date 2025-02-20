#include <windows.h>
#include <stdbool.h>

#include "tela.h"
#include "jogador.h"
#include "config.h"

void redimensionar_terminal(int largura_terminal, int altura_terminal) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {largura_terminal, altura_terminal};
    SMALL_RECT sr = {0, 0, coord.X - 1, coord.Y - 1};

    SetConsoleWindowInfo(handle, TRUE, &sr);
    SetConsoleScreenBufferSize(handle, coord);
}

void ocultar_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Obt�m as informa��es atuais do cursor
    cursorInfo.bVisible = FALSE;                     // Define o cursor como invis�vel
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); 
}

void exibir_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Obt�m as informa��es atuais do cursor
    cursorInfo.bVisible = TRUE;                      // Define o cursor como vis�vel
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); 
}

void posicionar_cursor(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void imprimir_pontuacao(jogador* dados){
    posicionar_cursor(104, 6);
    printf("Pontua��o: %d\n", dados->pontuacao);
}

void imprimir_tempo(){
    posicionar_cursor(104, 8);
    printf("Tempo: %s\n", tempo_formatado);
}

void imprimir_tempo_de_ativacao_timer(bool comida_especial_ativada){
    posicionar_cursor(104, 10);
    printf("Tempo comida");
    posicionar_cursor(104, 11);
    
    if(comida_especial_ativada){
    	printf("especial: 00%s\n", tempo_ativacao_timer_formatado);
	}
	else{
		printf("especial: --:--");
	}
}

void imprimir_comida(cobra *cob, char arena[28][100], bool comida_especial_ativada) {
	
	//se for comida especial pinta de azul e se for comida normal pinta de vermelho
	if(comida_especial_ativada){
		printf("\033[48;5;21m\033[%d;%dH%c\033[0m", cob->comida_especial_y + 1, cob->comida_especial_x + 1, arena[cob->comida_especial_y][cob->comida_especial_x]);
	}
	else{
		printf("\033[48;5;196m\033[%d;%dH%c\033[0m", cob->comida_y + 1, cob->comida_x + 1, arena[cob->comida_y][cob->comida_x]);
	}
}

//Eu sei que ta feio, n�o d� pra entender p*rra nenhuma, mas na impress�o do terminal
//esse treco abaixo resumidamente � um desenho de uma cobra verde com o menu 
void imprimir_opcoes_menu_cobra(){
	printf("\n\033[0m                                  \033[0;42m   \033[0;42m     \033[0;42m     \033[0;42m\033[48;5;22m \033[0m  "
	       "\n\033[0m                                \033[0;42m     \033[0;42m    \033[0m|----------------------------------|" 
           "\n\033[0m                              \033[0;42m  \033[0;42m     \033[0;42m    \033[0m|                                  |\033[0m                                        \033[48;5;101m \033[0m"
           "\n\033[0m           \033[0;42m     \033[0m\033[48;5;22m \033[0m           \033[0;42m    \033[0;42m     \033[0;42m\033[0m\033[48;5;22m \033[0m   \033[0m|           1- Novo jogo           |\033[0m         \033[0;42m             \033[0;42m\033[0m\033[48;5;22m \033[0m                \033[48;5;101m   \033[0m"
           "\n\033[0m        \033[0;42m          \033[0;42m\033[0m\033[48;5;22m \033[0m       \033[0;42m      \033[0;42m   \033[0m\033[48;5;22m \033[0m     \033[0m|                                  |\033[0m       \033[0;42m     \033[0;42m     \033[0;42m     \033[0;42m  \033[0m\033[48;5;22m \033[0m             \033[48;5;101m     \033[0m"
           "\n\033[48;5;196m  \033[0m   \033\033[0;42m    \033[0m \033[1;47m \033[0m\033[0;42m           \033[0m\033[0;42m     \033[0;42m     \033[0;42m \033[0m\033[48;5;22m \033[0m       \033[0m|           2- Ranking             |\033[0m     \033[0;42m                     \033[0m\033[48;5;22m \033[0m           \033[48;5;101m     \033[0m"
           "\n\033[1;31m\033[0m  \033[48;5;196m   \033\033[0;42m                 \033[0;42m     \033[0;42m    \033[0m\033[48;5;22m \033[0m         \033[0m|                                  |\033[0m   \033[0;42m          \033[0m\033[48;5;22m \033[0m       \033[0;42m       \033[0m\033[48;5;22m \033[0m          \033[0;42m   \033[0m"
           "\n\033[48;5;196m  \033[0m\033[0m   \033\033[0;42m    \033[0m \033[1;47m \033[0m\033[0;42m           \033[0m\033[0;42m     \033[0;42m  \033[0m\033[48;5;22m \033[0m           \033[0m|           3- Controles           |\033[0m \033[0;42m          \033[0m\033[48;5;22m \033[0m           \033[0;42m       \033[0m\033[48;5;22m \033[0m       \033[0;42m    \033[0m"
           "\n\033[0m        \033[0;42m          \033[0m\033[48;5;22m \033[0m                      \033[0m|                                  |\033[0m\033[0;42m  \033[0;42m     \033[0;42m  \033[0m\033[48;5;22m \033[0m               \033[0;42m       \033[0;42m\033[0m\033[48;5;22m \033[0m   \033[0;42m     \033[0m\033[48;5;22m \033[0m"
           "\n\033[0m           \033[0;42m     \033[0m\033[48;5;22m \033[0m                        \033[0m|           4- Sair                |\033[0m\033[0;42m  \033[0;42m     \033[0;42m\033[0m\033[48;5;22m \033[0m                   \033[0;42m     \033[0;42m      \033[0;42m  \033[0m\033[48;5;22m \033[0m"
           "\n\033[0m                                         \033[0m|                                  |\033[0m\033[0;42m  \033[0;42m   \033[0m\033[48;5;22m \033[0m                       \033[0;42m   \033[0;42m      \033[0;42m\033[0m\033[48;5;22m \033[0m"
           "\n\033[0m                                         \033[0m|----------------------------------|\033[0m\033[0;42m  \033[0;42m \033[0m\033[48;5;22m \033[0m"
		   "\t\t\t\t\t\t\033[0m                                                           \033[0;42m      \033[0;42m     \033[0;42m     \033[0;42m    \033[48;5;22m \033[0m"
		   "\t\t\t\t\t\t\033[0m                                                              \033[0;42m   \033[0;42m     \033[0;42m     \033[0;42m \033[0m\033[48;5;22m \033[0m   \n\n\t\t\t\t\t\t\t");
}


//Tbm n�o da pra entender p*rra nenhuma, mas na impress�o no terminal isso abaixo � a
//palavra snake pintado de amarelo com um sombreamento causando uma falsa sensa��o de ser 3D
void imprimir_snake_menu(){
	printf("\033[0m             \033[48;5;220m             \033[48;5;94m  \033[0m     \033[48;5;220m     \033[48;5;94m  \033[0m       \033[48;5;220m     \033[48;5;94m  \033[0m    \033[48;5;220m            \033\033[48;5;94m  \033[0m     \033[48;5;220m    \033\033[48;5;94m  \033[0m     \033[48;5;220m      \033\033[48;5;94m  \033[0m \033[48;5;220m              \033\033[48;5;94m  \033[0m"
           "\n\033[0m           \033[48;5;220m                 \033[48;5;94m  \033[0m  \033[48;5;220m       \033[48;5;94m  \033[0m      \033[48;5;220m     \033[48;5;94m  \033[0m  \033[48;5;220m                \033[48;5;94m  \033[0m  \033[48;5;220m      \033[48;5;94m  \033[0m   \033[48;5;220m      \033[48;5;94m  \033[0m \033[48;5;220m                \033[48;5;94m  \033[0m"
           "\n\033[0m          \033[48;5;220m        \033[48;5;94m  \033[0m   \033[48;5;220m      \033[48;5;94m  \033[0m \033[48;5;220m        \033[48;5;94m  \033[0m     \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m    \033[48;5;220m      \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m  \033[48;5;220m      \033[48;5;94m  \033[0m  \033[48;5;220m               \033[48;5;94m  \033[0m"
           "\n\033[0m         \033[48;5;220m        \033[48;5;94m  \033[0m             \033[48;5;220m         \033[48;5;94m  \033[0m    \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m      \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m   \033[48;5;220m      \033[48;5;94m  \033[0m        "
           "\n\033[0m          \033[48;5;220m         \033[48;5;94m  \033[0m           \033[48;5;220m          \033[48;5;94m  \033[0m   \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m      \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m\033[48;5;220m      \033[48;5;94m  \033[0m    \033[48;5;220m      \033[48;5;94m  \033[0m        "
           "\n\033[0m            \033[48;5;220m            \033[48;5;94m  \033[0m      \033[48;5;220m     \033[48;5;94m \033[0m\033[48;5;220m     \033[48;5;94m  \033[0m  \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m      \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m \033[0m\033[48;5;220m      \033[48;5;94m  \033[0m     \033[48;5;220m               \033[48;5;94m  \033[0m"
           "\n\033[0m              \033[48;5;220m            \033[48;5;94m  \033[0m    \033[48;5;220m     \033[48;5;94m  \033[0m\033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m                  \033[48;5;94m  \033[0m \033[48;5;220m            \033[48;5;94m  \033[0m      \033[48;5;220m                \033[48;5;94m  \033[0m"
           "\n\033[0m                   \033[48;5;220m         \033[48;5;94m  \033[0m  \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m\033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m                  \033[48;5;94m  \033[0m \033[48;5;220m            \033[48;5;94m  \033[0m      \033[48;5;220m               \033[48;5;94m  \033[0m"
           "\n\033[0m                      \033[48;5;220m       \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m  \033[48;5;220m     \033[48;5;94m \033[0m\033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m    \033[48;5;220m      \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m \033[0m\033[48;5;220m      \033[48;5;94m  \033[0m     \033[48;5;220m      \033[48;5;94m  \033[0m        "
           "\n\033[0m                      \033[48;5;220m       \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m   \033[48;5;220m          \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m      \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m\033[48;5;220m      \033[48;5;94m  \033[0m    \033[48;5;220m      \033[48;5;94m  \033[0m        "
           "\n\033[0m        \033[48;5;220m      \033[48;5;94m  \033[0m   \033[48;5;220m         \033[48;5;94m  \033[0m  \033[48;5;220m     \033[48;5;94m  \033[0m    \033[48;5;220m         \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m      \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m   \033[48;5;220m               \033[48;5;94m  \033[0m"
           "\n\033[0m          \033[48;5;220m                 \033[48;5;94m  \033[0m   \033[48;5;220m     \033[48;5;94m  \033[0m     \033[48;5;220m        \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m      \033[48;5;220m     \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m  \033[48;5;220m      \033[48;5;94m  \033[0m  \033[48;5;220m                \033[48;5;94m  \033[0m"
           "\n\033[0m            \033[48;5;220m             \033[48;5;94m  \033[0m     \033[48;5;220m     \033[48;5;94m  \033[0m      \033[48;5;220m      \033[48;5;94m  \033[0m \033[48;5;220m      \033[48;5;94m  \033[0m      \033[48;5;220m      \033[48;5;94m  \033[0m \033[48;5;220m     \033[48;5;94m  \033[0m   \033[48;5;220m      \033[48;5;94m  \033[0m  \033[48;5;220m              \033[48;5;94m  \033[0m\n\033[0m");

}
