#include <windows.h>

#include "teclado.h"
#include "config.h" // Para acessar a variável global ultima_direcao

char verificar_input_direcional() {
    static char ultima_direcao = 'd';  // Direção inicial

    if (GetAsyncKeyState('W') & 0x8000 && ultima_direcao != 's') {
        ultima_direcao = 'w';
    } else if (GetAsyncKeyState('A') & 0x8000 && ultima_direcao != 'd') {
        ultima_direcao = 'a';
    } else if (GetAsyncKeyState('S') & 0x8000 && ultima_direcao != 'w') {
        ultima_direcao = 's';
    } else if (GetAsyncKeyState('D') & 0x8000 && ultima_direcao != 'a') {
        ultima_direcao = 'd';
    }

    return ultima_direcao;  // Retorna a direção pressionada
}

bool verificar_input_pause() {
	bool apertou_botao = false;
	
    if (GetAsyncKeyState('P') & 0x8000) {
        apertou_botao = true;  
    }
    return apertou_botao;  
}

