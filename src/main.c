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
#include "musica.h"
#include "timer.h"

int main (){
	redimensionar_terminal(120, 31);
	setlocale(LC_ALL, "portuguese");

	int velocidade_jogo, loop;
	int tempo_para_ativacao_comida, tempo_da_ativacao_comida, tempo_de_pause;
	bool retorno_colisao, retorno_comida, retorno_comida_especial;
	bool quer_pausar, quer_sair = false;
	bool musica_principal_tocando = false, perdeu_comida_especial_tocando, game_inicio_tocando;
	

	char arena[altura][largura];
	int arena_int[altura][largura]; // estrutura auxiliar para algumas vericações das funções colisão e geração de comida
    char opcao;
	
	//Entidades:
	jogador dados_jogador;
	cobra dados_cobra;
	jogador ranking[300] = {0};
	Timer timer_comida_especial;
	
	struct timeval tempo_inicial, tempo_pausa_inicio, tempo_pausa_fim, duracao_em_pause;

    apresentar_aviso_encoding();

	do {
		loop = 0;
        opcao = menu_principal(&musica_principal_tocando);

        switch (opcao){
            case '1': // Gameplay:
                system("cls");
                pedir_nome(&dados_jogador);
                
            //Começo do jogo:
                system("cls");
                comida_especial_ativada = false;
                mapa_selecionado = menu_selecionar_mapa();
                parar_musica();
                inicializar_jogo(&dados_jogador, &dados_cobra, arena, arena_int);
                tocar_som_gameinicio();
                game_inicio_tocando = true;
				gettimeofday(&tempo_inicial, NULL);
				iniciar_timer(&timer_comida_especial, rand() % 20 + 10, 15, 15); //inicia um timer_comida_especial num intervalo de 10 a 60 segundos 
                ocultar_cursor();
                quer_sair = false;

                while(true){
                	perdeu_comida_especial_tocando = false;
                    mover_cobra(&dados_cobra);
                    
                    tempo_para_ativacao_comida = verificar_tempo_para_ativacao(&timer_comida_especial);
					
			        if (tempo_para_ativacao_comida == 0) {
			        	comida_especial_ativada = true;
			        	ativar_tempo_de_ativacao(&timer_comida_especial);
                        gerar_comida(&dados_cobra, arena, arena_int,true); 
						tocar_som_comida_especial();
			        }
					
					tempo_da_ativacao_comida = verificar_tempo_da_ativacao(&timer_comida_especial);
					
					if(tempo_da_ativacao_comida == 0){
						comida_especial_ativada = false;
						perdeu_comida_especial_tocando = true;
						pausar_timer(&timer_comida_especial);
						//faz um print nas coodedanas abaixo apagando a cor azul
						printf("\033[%d;%dH\033[0m ", dados_cobra.comida_especial_y + 1, dados_cobra.comida_especial_x + 1);
						tocar_som_perdeu_comida_especial();
					}
					
					tempo_de_pause = verificar_tempo_de_pausa(&timer_comida_especial);
					if(tempo_de_pause == 0){
						reativar_timer(&timer_comida_especial);
					}
			        
                    quer_pausar = verificar_input_pause();
                    
                    if(quer_pausar){
						gettimeofday(&tempo_pausa_inicio, NULL); 
                    	quer_sair = menu_de_pause(&dados_jogador, &dados_cobra, arena, arena_int, comida_especial_ativada);
                    	gettimeofday(&tempo_pausa_fim, NULL); 
                    	                        
						// Calculando a duração do tempo de pausa e subtraindo o valor do tempo inicial
						if(!quer_sair){
							calcular_diferenca_tempo(&tempo_pausa_inicio, &tempo_pausa_fim, &duracao_em_pause);
	                        ajustar_tempo_inicial_com_pausa(&tempo_inicial, &duracao_em_pause);	
	                        ajustar_tempo_timer_com_pausa(&timer_comida_especial, &duracao_em_pause);
						}
						else{
							goto sair_do_jogo;
						}
					}
                    
                    retorno_colisao = verificar_colisao(dados_cobra, arena_int);
                    
                    if (retorno_colisao || quer_sair){ 
                        break; 
                    }
					
					retorno_comida = verificar_se_cobra_comeu(dados_cobra);
					retorno_comida_especial = verificar_se_cobra_comeu_especial(dados_cobra, &timer_comida_especial);
					
                    if (retorno_comida) {
                    	if(!perdeu_comida_especial_tocando && !game_inicio_tocando){
                    		tocar_som_comida();
						}
                        arena[dados_cobra.comida_y][dados_cobra.comida_x] = ' '; // apaga a impressão da comida da arena
                        dados_jogador.pontuacao += 10;
                        dados_cobra.tamanho_cobra++; // adiciona 1 segmento na cobra que será impresso.
                        gerar_comida(&dados_cobra, arena, arena_int, false);
                    }
                    else if(retorno_comida_especial){
                    	if(!perdeu_comida_especial_tocando){
                    		tocar_som_comida();
						}
						comida_especial_ativada = false;
                    	arena[dados_cobra.comida_especial_y][dados_cobra.comida_especial_x] = ' '; // apaga a impressão da comida da arema
						dados_jogador.pontuacao += 20;
						dados_cobra.tamanho_cobra += 2; // adiciona 2 segmento2 na cobra que será impresso.
						pausar_timer(&timer_comida_especial); // pausa o timer em 15 segundos	 
					}
					sair_do_jogo:
                	game_inicio_tocando = false;
                    cronometrar_tempo(&dados_jogador, tempo_inicial);
                    imprimir_tempo();
                    imprimir_pontuacao(&dados_jogador);
                    imprimir_tempo_de_ativacao_timer(comida_especial_ativada);  	
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
				
				int opcao_selecionada = menu_tipo_ranking();
				bool ordenar_por_mapa;
				
				qtd_preenchido_array = ler_ranking_do_arquivo(f2, ranking);
			    	fclose(f2);
			    	
				if(opcao_selecionada == 1){	
					ordenar_por_mapa = false;	
			    	ordenar_ranking(ranking, ordenar_por_mapa);
				}	
				else{
					ordenar_por_mapa = true;
					mapa_selecionado = menu_selecionar_mapa_ranking();	
			    	ordenar_ranking(ranking, ordenar_por_mapa);
				}
					
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
