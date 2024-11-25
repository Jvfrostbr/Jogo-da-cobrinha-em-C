#include "ranking.h"
#include "jogador.h"

int ler_ranking_do_arquivo(FILE *f2, jogador ranking[300]) {
    char linha[100]; 
    int i = 0;
	int retorno; 

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), f2) != NULL && i < 300) {
        
		// Remove a quebra de linha, se houver
        linha[strcspn(linha, "\n")] = 0;

        // lê os dados formatados na linha
        retorno = sscanf(linha, "%s %d %5s", ranking[i].nome_jogador, &ranking[i].pontuacao, ranking[i].tempo_jogado);

        // Verifica se os dados foram lidos corretamente
        if (retorno == 3) {
            i++;
        } else {
            printf("Erro ao ler dados na linha: %s\n", linha);
        }
    }
    
    return i; // retorna a quantidade de dados preenchidos no array;
}

void ordenar_ranking(jogador ranking[], int tamanho_preenchido) {
    int i, j;
    // Ordena o array em ordem decrescente de pontuação, em caso de empate, ordena por tempo
    for (i = 0; i < tamanho_preenchido - 1; i++) {
        for (j = i + 1; j < tamanho_preenchido; j++) {
            if (ranking[j].pontuacao > ranking[i].pontuacao ||
                (ranking[j].pontuacao == ranking[i].pontuacao && strcmp(ranking[j].tempo_jogado, ranking[i].tempo_jogado) < 0)) {
                // Troca as posições dos jogadores
                jogador temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }
}

void imprimir_ranking(jogador ranking[300]) {
	int i;
    // Impressão dos 20 melhores jogadores
    printf("\n\n\t\t\t\t\t|----------------------------------------------------|"
	       "\n\t\t\t\t\t|         Ranking dos 10 melhores jogadores:         |"
           "\n\t\t\t\t\t|                                                    |\n");
	
    for (i = 0; i < 20; i++) {
        printf("\t\t\t\t\t| %-2dº lugar: %-10s - score: %-4d - tempo: %-5s |\n", i + 1, ranking[i].nome_jogador, ranking[i].pontuacao, ranking[i].tempo_jogado);
    }
    printf("\t\t\t\t\t|                                                    |"
		   "\n\t\t\t\t\t|----------------------------------------------------|");

    Sleep(10000);
    system("cls");
}

