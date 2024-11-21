#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "jogador.h"
#include "tela.h"

void pedir_nome(jogador *jogador) {
    char nome[12];

    printf(
        "\n\n\n\n\t\t\t      |-------------------------------------------------------------|\n"
        "\t\t\t      |                                                             |\n"
        "\t\t\t      |       Digite um nome (max 10 caracteres):                   |\n"
        "\t\t\t      |                                                             |\n"
        "\t\t\t      |-------------------------------------------------------------|\n\n"
    );
    
    posicionar_cursor(76, 6);
    scanf("%11s", nome);
    strcpy(jogador->nome_jogador, nome);
}

void cronometrar_tempo(jogador* dados, clock_t tempo_inicial) {
    int tempo_jogado_em_segundos, minutos, segundos;
    clock_t tempo_atual;

    tempo_atual = clock();
    tempo_jogado_em_segundos = (int) (tempo_atual - tempo_inicial) / CLOCKS_PER_SEC;

    minutos = tempo_jogado_em_segundos / 60;
    segundos = tempo_jogado_em_segundos % 60;

    // Formata o tempo no formato (minutos : segundos) e atualiza a variável global
    sprintf(tempo_formatado, "%02d:%02d", minutos, segundos);
}

void salvar_dados_jogador(jogador jogador) {
    FILE *file = fopen("Dados_jogador.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d %s\n", jogador.nome_jogador, jogador.pontuacao, jogador.tempo_jogado);
        fclose(file);
    } else {
        printf("Erro ao salvar os dados do jogador!\n");
    }
}


