#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "cobra.h"
#include "config.h"
#include "tela.h"
#include "menu.h"
#include "jogador.h"

void imprimir_cobra(cobra *cob, int cabeca_x_anterior, int cabeca_y_anterior) {
	int i;
	static int j = 1;
	
    // Apaga o último segmento do corpo da cobra
    posicionar_cursor(cob->corpo_cobra[cob->tamanho_cobra - 1][0], cob->corpo_cobra[cob->tamanho_cobra - 1][1]);
    printf(" ");
    
    // Atualiza o corpo da cobra, movendo cada segmento para a posição anterior
    for (i = cob->tamanho_cobra - 1; i > 0; i--) {
        cob->corpo_cobra[i][0] = cob->corpo_cobra[i - 1][0];
        cob->corpo_cobra[i][1] = cob->corpo_cobra[i - 1][1];
    }

    // Atualiza a posição do primeiro segmento do corpo para a posição da cabeça antiga
    if (cob->tamanho_cobra > 0) {
        cob->corpo_cobra[0][0] = cabeca_x_anterior;
        cob->corpo_cobra[0][1] = cabeca_y_anterior;
    }

    // Imprime a cabeça da cobra na nova posição
    posicionar_cursor(cob->cabeca_x, cob->cabeca_y);
    printf("\033[0;42m%c\033[0m", cob->simbolo_cobra);  // Cor verde escuro para a cabeça

    // Imprime cada segmento do corpo da cobra na posição atualizada
    for (i = 0; i < cob->tamanho_cobra; i++) {
        posicionar_cursor(cob->corpo_cobra[i][0], cob->corpo_cobra[i][1]);
		printf("\033[48;5;22m%c\033[0m", cob->simbolo_cobra);  // Cor verde  para resto o corpo
    }
    
    //trecho abaixo é para corrigir um pequeno bug do rastro da cobra no começo do jogo
    if(j == 3 && mapa_selecionado != 3){
    	posicionar_cursor(largura/ 2 , 14);
    	printf(" ");
	}
	j++;
}

void mover_cobra(cobra *cobra) {
    char input  = verificar_input_direcional();
    int cabeca_x_anterior = cobra->cabeca_x;
    int cabeca_y_anterior = cobra->cabeca_y;

    switch(input) {
        case 'w':
            cobra->cabeca_y--;
            break;
        case 'a':
            cobra->cabeca_x--;
            break;
        case 's':
            cobra->cabeca_y++;
            break;
        case 'd':
            cobra->cabeca_x++;
            break;
    }
    imprimir_cobra(cobra, cabeca_x_anterior, cabeca_y_anterior);
}

bool verificar_colisao(cobra dados_snk, int arena_int[altura][largura]) {
    int i, cabeca_y, cabeca_x;
    bool colidiu = false;

    // Verifica se a cabeça da cobra colidiu com o próprio corpo:
    for (i = 1; i < dados_snk.tamanho_cobra && !colidiu; i++) {
		if (dados_snk.cabeca_x == dados_snk.corpo_cobra[i][0] && dados_snk.cabeca_y == dados_snk.corpo_cobra[i][1]) {
            colidiu = true;
        }
    }
    
    if (dados_snk.cabeca_x <= 1 || dados_snk.cabeca_x >= largura || dados_snk.cabeca_y <= 1 || dados_snk.cabeca_y >= altura) {
        colidiu = true;
    }
    
	cabeca_y = dados_snk.cabeca_y;
	cabeca_x = dados_snk.cabeca_x;
	
	// Verifica se a cabeça da cobra colidiu nas paredes internas do mapa
	if(arena_int[cabeca_y][cabeca_x] == 1){ 
		colidiu = true;	
	}
    return colidiu;
}

void gerar_comida(cobra *cob, char arena[altura][largura], int arena_int[altura][largura], bool comida_especial_ativada){
    srand(time(NULL));
    bool local_valido = false, comida_sobre_cobra;
	int i;
		
    // Se a cobra comeu, gera uma nova comida em um lugar aleatório.
    while (!local_valido) {
        comida_sobre_cobra = false;
        if(comida_especial_ativada){
            cob->comida_especial_x = rand() % (97) + 2;
        	cob->comida_especial_y = rand() % (26) + 2;	
        	        	
        	// Verifica se a comida especial não está sendo gerada em cima da cabeça da cobra
	        if (cob->comida_especial_x == cob->cabeca_x && cob->comida_especial_y == cob->cabeca_y){
	            goto reiniciar_loop;
	        }
			int tamanho = cob->tamanho_cobra;
			
	        //verifica se a comida está sendo gerada em algum segmento do corpo da cobra
	        for (i = 0; i < cob->tamanho_cobra && !comida_sobre_cobra; i++) {
	            if (cob->comida_especial_x == cob->corpo_cobra[i][0] && cob->comida_especial_y == cob->corpo_cobra[i][1]) {
	                comida_sobre_cobra = true; // flag para parar o loop for;
	            }
	        }
	
	        if (comida_sobre_cobra) {
	            goto reiniciar_loop;
	        }
			 
        	//verifica se a comida a ser gerada é a comida especial e se 
			//ela está sendo gerada na mesma coordenada da comida normal
		    if(cob->comida_especial_y == cob->comida_y && cob->comida_especial_x == cob->comida_x){
		    	goto reiniciar_loop;	
			}
			
			int comida_especial_x = cob->comida_especial_x;
			int comida_especial_y = cob->comida_especial_y;
			
			if(arena_int[comida_especial_y][comida_especial_x] == 1){
				goto reiniciar_loop;
			}
			
			arena[cob->comida_especial_y][cob->comida_especial_x] = 32; // Atualiza a arena com a nova posição da comida especial
		}
		else{
	        cob->comida_x = rand() % (97) + 2;
        	cob->comida_y = rand() % (26) + 2;	
				
	        // Verifica se a comida não está sendo gerada em cima da cabeça da cobra
	        if (cob->comida_x == cob->cabeca_x && cob->comida_y == cob->cabeca_y){
	            goto reiniciar_loop;
	        }
			int tamanho = cob->tamanho_cobra;
			
	        //verifica se a comida está sendo gerada em algum segmento do corpo da cobra
	        for (i = 0; i < cob->tamanho_cobra && !comida_sobre_cobra; i++) {
	            if (cob->comida_x == cob->corpo_cobra[i][0] && cob->comida_y == cob->corpo_cobra[i][1]) {
	                comida_sobre_cobra = true; // flag para parar o loop for;
	            }
	        }
	
	        if (comida_sobre_cobra) {
	            goto reiniciar_loop;
	        }
			
			//verifica se a comida a ser gerada é a comida especial e se 
			//ela está sendo gerada na mesma coordenada da comida normal
		    if(cob->comida_especial_y == cob->comida_y && cob->comida_especial_x == cob->comida_x){
		    	goto reiniciar_loop;	
			}
			
			int comida_x = cob->comida_x;
			int comida_y = cob->comida_y;
			
			if(arena_int[comida_y][comida_x] == 1){
				goto reiniciar_loop;
			}
			
			arena[cob->comida_y][cob->comida_x] = 32; // Atualiza a arena com a nova posição da comida normal 	
		}

        //flag para parar o loop caso a posição da comida normal ou especial tenham cumprido todas as condições
        local_valido = true;

        reiniciar_loop:; // Ponto de reinício do loop, caso a comida esteja na cabeça ou corpo da cobra
    }

    imprimir_comida(cob, arena, comida_especial_ativada);
}

bool verificar_se_cobra_comeu(cobra dados_cobra){
    bool resultado = false;
	
    if (dados_cobra.cabeca_x == dados_cobra.comida_x && dados_cobra.cabeca_y == dados_cobra.comida_y) {
        resultado = true;
    }
    return resultado;
}

bool verificar_se_cobra_comeu_especial(cobra dados_cobra, Timer *timer_comida_especial){
    bool resultado = false;
	
    if (timer_comida_especial->contando_tempo_durante_ativacao && !timer_comida_especial->pausado 
	&& dados_cobra.comida_especial_x == dados_cobra.cabeca_x && dados_cobra.comida_especial_y == dados_cobra.cabeca_y){
        resultado = true;
    }
    return resultado;
}


