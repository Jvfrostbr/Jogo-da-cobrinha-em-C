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
        retorno = sscanf(linha, "%s %d %d %5s", ranking[i].nome_jogador, &ranking[i].pontuacao, &ranking[i].mapa_jogado, ranking[i].tempo_jogado);

        // Verifica se os dados foram lidos corretamente
        if (retorno == 4) {
            i++;
        } else {
            printf("Erro ao ler dados na linha: %s\n", linha);
        }
    }
    
    return i; // retorna a quantidade de dados preenchidos no array;
}

void ordenar_ranking(jogador ranking[], bool ranquear_por_mapa) {
    int i, j;

    if (ranquear_por_mapa) {
        jogador filtrado[qtd_preenchido_array];
        int tamanho_filtrado = 0;
		
	    // Filtra os jogadores pelo mapa selecionado
        for (i = 0; i < qtd_preenchido_array; i++) {
            if (ranking[i].mapa_jogado == mapa_selecionado) {
                filtrado[tamanho_filtrado] = ranking[i];
                tamanho_filtrado++;
            }
        }
		
		if(tamanho_filtrado > 1){
			// Ordenar apenas os jogadores filtrados
	        for (i = 0; i < tamanho_filtrado; i++) {
	            for (j = i + 1; j < tamanho_filtrado; j++) {
	                if (j < tamanho_filtrado && filtrado[j].pontuacao > filtrado[i].pontuacao ||
	                    j < tamanho_filtrado && (filtrado[j].pontuacao == filtrado[i].pontuacao && 
	                     strcmp(filtrado[j].tempo_jogado, filtrado[i].tempo_jogado) < 0)) {
	                    // Troca as posições dos jogadores
	                    jogador temp = filtrado[i];
	                    filtrado[i] = filtrado[j];
	                    filtrado[j] = temp;
	                }
	            }
	        }	
		}
        
		// copiando os os jogadores ordernados no array ranking
	    qtd_preenchido_array = tamanho_filtrado;
	    for(i = 0; i < tamanho_filtrado; i++){
	    	ranking[i] = filtrado[i];
		}
    }
	else {
        // Ordenar o array completo em ordem decrescente de pontuação
        for (i = 0; i < qtd_preenchido_array - 1; i++) {
            for (j = i + 1; j < qtd_preenchido_array; j++) {
                if (j < qtd_preenchido_array && ranking[j].pontuacao > ranking[i].pontuacao ||
                    j < qtd_preenchido_array && (ranking[j].pontuacao == ranking[i].pontuacao && 
                     strcmp(ranking[j].tempo_jogado, ranking[i].tempo_jogado) < 0)) {
                    // Troca as posições dos jogadores
                    jogador temp = ranking[i];
                    ranking[i] = ranking[j];
                    ranking[j] = temp;
                }
            }
        }
    }
}


void imprimir_ranking(jogador ranking[300]) {
	int i;
	bool parar_loop = false;
    // Impressão dos 20 melhores jogadores
    printf("\n\n\t\t\t\t|--------------------------------------------------------------|"
	       "\n\t\t\t\t|             Ranking dos 10 melhores jogadores:               |"
           "\n\t\t\t\t|                                                              |\n");
	
    for (i = 0; i < qtd_preenchido_array && !parar_loop; i++) {
    	if(qtd_preenchido_array > 20){
    		parar_loop = true;
		}
		else{
			if(i < 9){
				printf("\t\t\t\t|  %dº lugar: %-10s - score: %-4d - tempo: %-5s - mapa: %d |\n", i + 1, ranking[i].nome_jogador, ranking[i].pontuacao, ranking[i].tempo_jogado, ranking[i].mapa_jogado);
			}
			else{
				printf("\t\t\t\t| %-2dº lugar: %-10s - score: %-4d - tempo: %-5s - mapa: %d |\n", i + 1, ranking[i].nome_jogador, ranking[i].pontuacao, ranking[i].tempo_jogado, ranking[i].mapa_jogado);
			}
		}
    }
    printf("\t\t\t\t|                                                              |\n"
		   "\t\t\t\t|--------------------------------------------------------------|");

    Sleep(10000);
    system("cls");
}

