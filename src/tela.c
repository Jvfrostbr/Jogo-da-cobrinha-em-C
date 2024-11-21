#include <windows.h>

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

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Obtém as informações atuais do cursor
    cursorInfo.bVisible = FALSE;                     // Define o cursor como invisível
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); 
}

void exibir_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Obtém as informações atuais do cursor
    cursorInfo.bVisible = TRUE;                      // Define o cursor como visível
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); 
}

void posicionar_cursor(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void imprimir_pontuacao(jogador* dados){
    posicionar_cursor(104, 8);
    printf("Pontuação: %d\n", dados->pontuacao);
}

void imprimir_tempo(){
    posicionar_cursor(104, 10);
    printf("Tempo: %s\n", tempo_formatado);
}
