#include <locale.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>

// Headers dos módulos criados
#include "config.h"  
#include "ranking.h" 
#include "teclado.h" 
#include "tela.h"    
#include "jogo.h"    
#include "arena.h"
#include "cobra.h"
#include "jogador.h"
#include "mensagens.h"
#include "menu.h"

int main (){
	redimensionar_terminal(120, 31);
	setlocale(LC_ALL, "portuguese");
	int loop;
	int velocidade_jogo;
	bool retorno_colisao, retorno_comida;

	char arena[altura][largura];
    char opcao;

	jogador dados_jogador;
	cobra dados_cobra;
	jogador ranking[300] = {0};

    apresentar_aviso_encoding();

	do {
        opcao = menu_principal();

        switch (opcao){
            case '1': // Gameplay:
                system("cls");
                pedir_nome(&dados_jogador);
                
            //Começo do jogo:
                system("cls");
                inicializar_jogo(&dados_jogador, &dados_cobra, arena);
                clock_t tempo_inicial = clock();
                ocultar_cursor();
                loop = 0;

                while(loop == 0){
                    mover_cobra(&dados_cobra);
                    retorno_colisao = verificar_colisao(dados_cobra);
                    
                    if (retorno_colisao){
                        break; 
                    }
					
					retorno_comida = verificar_se_cobra_comeu(dados_cobra);
					      
                    if (retorno_comida) {
                        arena[dados_cobra.comida_y][dados_cobra.comida_x] = ' '; // remove o caractere da comida do mapa
                        dados_jogador.pontuacao += 10;
                        dados_cobra.tamanho_cobra++; // adiciona 1 segmento na cobra que será impresso.
                        gerar_comida(&dados_cobra, arena);
                    }
                    
                    cronometrar_tempo(&dados_jogador, tempo_inicial);
                    imprimir_tempo();
                    imprimir_pontuacao(&dados_jogador);
                    velocidade_jogo = aumentar_velocidade (dados_cobra.tamanho_cobra);
                    Sleep(velocidade_jogo);
                }
                strcpy(dados_jogador.tempo_jogado, tempo_formatado); //atualiza o tempo jogado do jogador.
                apresentar_game_over(dados_jogador);
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // Limpa o buffer de entrada do console
                exibir_cursor();
                break;

            case '2': // Ranking
			    system("cls");
			    FILE *f2 = fopen("Dados_jogador.txt", "r");
			
			    if (f2 == NULL) {
			        printf("Erro ao abrir o arquivo\n");
			        exit(1);
			    }
						
			    ler_ranking_do_arquivo(f2, ranking);
			    fclose(f2);
			
			    ordenar_ranking(ranking);
			    imprimir_ranking(ranking);
			    break;
                
            case '3': // Impressão dos controles no jogo:
            	apresentar_controles();
               	break;
                
            case '4':
                loop = 1;	//Encerra o loop principal e a execução do jogo
                break;
                
            default: // Se foi digitado um número inteiro fora do intervalo de 1 a 4:
    			apresentar_opcao_invalida();
                break;
        }
	}while(loop == 0);
	return 0;
}
