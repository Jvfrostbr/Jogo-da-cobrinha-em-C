#include <locale.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>

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
	int velocidade_jogo, loop;
	bool retorno_colisao, retorno_comida, quer_pausar, quer_sair = false;

	char arena[altura][largura];
    char opcao;

	jogador dados_jogador;
	cobra dados_cobra;
	jogador ranking[300] = {0};
	
	struct timeval tempo_inicial, tempo_pausa_inicio, tempo_pausa_fim, duracao_em_pause;

    //apresentar_aviso_encoding();

	do {
		loop = 0;
        opcao = menu_principal();

        switch (opcao){
            case '1': // Gameplay:
                system("cls");
                pedir_nome(&dados_jogador);
                
            //Começo do jogo:
                system("cls");
                inicializar_jogo(&dados_jogador, &dados_cobra, arena);
				gettimeofday(&tempo_inicial, NULL); 
                ocultar_cursor();
                quer_sair = false;

                while(true){
                    mover_cobra(&dados_cobra);
                    quer_pausar = verificar_input_pause();
                    
                    if(quer_pausar){
						gettimeofday(&tempo_pausa_inicio, NULL); 
                    	quer_sair = menu_de_pause(&dados_jogador, &dados_cobra, arena);
                    	gettimeofday(&tempo_pausa_fim, NULL); 
                    	                        
						// Calculando a duração do tempo de pausa e subtraindo o valor do tempo inicial
                        
						if(!quer_sair){
							calcular_diferenca_tempo(&tempo_pausa_inicio, &tempo_pausa_fim, &duracao_em_pause);
	                        ajustar_tempo_inicial_com_pausa(&tempo_inicial, &duracao_em_pause);	
						}
					}
                    
                    retorno_colisao = verificar_colisao(dados_cobra);
                    
                    if (retorno_colisao || quer_sair){ 
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
                    velocidade_jogo = aumentar_velocidade_jogo(dados_cobra.tamanho_cobra);
                    Sleep(velocidade_jogo);
                }
                strcpy(dados_jogador.tempo_jogado, tempo_formatado); //atualiza o tempo jogado do jogador.
                apresentar_game_over(dados_jogador);
                salvar_dados_jogador(dados_jogador);
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // Limpa o buffer de entrada do console
                exibir_cursor();
                loop = 0;
                break;

            case '2': // Ranking
			    system("cls");
			    FILE *f2 = fopen("Dados_jogador.txt", "r");
			
			    if (f2 == NULL) {
			        printf("Erro ao abrir o arquivo\n");
			        exit(1);
			    }
						
			    int qtd_preenchido_array = ler_ranking_do_arquivo(f2, ranking);
			    fclose(f2);
			    				
			    ordenar_ranking(ranking, qtd_preenchido_array);
			    imprimir_ranking(ranking);
			    loop = 0;
			    break;
                
            case '3': // Impressão dos controles no jogo:
            	apresentar_controles();
            	loop = 0;
               	break;
                
            case '4':
                loop = 1;	//Encerra o loop principal e a execução do jogo
                break;
                
            default: // Se foi digitado um número inteiro fora do intervalo de 1 a 4:
    			apresentar_opcao_invalida();
    			loop = 0;
                break;
        }
	} while(loop == 0);
	return 0;
}
