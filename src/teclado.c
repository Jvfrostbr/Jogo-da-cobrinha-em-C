#include <windows.h>

#include "teclado.h"
#include "config.h" // Para acessar a variável global ultima_direcao

char verificar_input_teclado() {
    if (GetAsyncKeyState('W') & 0x8000 && ultima_direcao != 's'){
        ultima_direcao = 'w';
    }
    else if (GetAsyncKeyState('A') & 0x8000 && ultima_direcao != 'd'){
        ultima_direcao = 'a';
    }
    else if (GetAsyncKeyState('S') & 0x8000 && ultima_direcao != 'w'){
        ultima_direcao = 's';
    }
    else if (GetAsyncKeyState('D') & 0x8000 && ultima_direcao != 'a'){
        ultima_direcao = 'd';
    }
    return ultima_direcao; // Se nenhuma tecla for digitada, retorna a última direção registrada.
}
