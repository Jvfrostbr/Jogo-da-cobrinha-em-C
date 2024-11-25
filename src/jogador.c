#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "jogador.h"
#include "tela.h"
#include "jogo.h"


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

void cronometrar_tempo(jogador* dados, struct timeval  tempo_inicial) {
    struct timeval tempo_atual;
    gettimeofday(&tempo_atual, NULL);

    // Calculando a diferença entre tempo_atual e tempo_inicial
    struct timeval tempo_decorrido;
    calcular_diferenca_tempo(&tempo_inicial, &tempo_atual, &tempo_decorrido);

    // Atualizando a pontuação e o tempo jogado
    int minutos = tempo_decorrido.tv_sec / 60;
    int segundos = tempo_decorrido.tv_sec % 60;

    // Formata o tempo no formato (minutos : segundos) e atualiza a variável global
    sprintf(tempo_formatado, "%02d:%02d", minutos, segundos);
    strcpy(dados->tempo_jogado, tempo_formatado); //atualiza o tempo jogado do jogador.
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


