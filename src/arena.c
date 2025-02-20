#include <stdio.h>

#include "arena.h"
#include "config.h" 

// Função para criar a arena de jogo

void criar_area_interna_mapa_1(char arena[28][100], int arena_int[28][100]){
    int i, j;
    
	posicionar_cursor(0, 2);
    for (i = 2; i < 28; i++) {
        for (j = 0; j < 100 - 2; j++) {
            arena[i][j] = ' ';
			
			if(i >= 2 && j == 1){
			 	printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;	
			}
            else if ( (i == 2 || i == 3 || i == 26 || i == 27) && (j == 50) ||
				(i == 4 || i == 25) && (j >= 14 && j <= 39 || j >= 62 && j <= 87) ||
                (i == 8 || i == 21) && (j == 8 || j >= 15 && j <= 41 || j >= 60 && j <= 86 || j == 93 ) ||
                (i >= 9 && i <= 11 || i >= 18 && i <= 20) && (j == 8 || j == 15 || j == 86 || j == 93) ||
                (i == 12 || i == 13 || i == 16 || i == 17) && (j == 27 || j == 73) ||
                (i == 14 || i == 15) && (j >= 27 && j <= 73)) {

                printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;
            } 
			else {
                printf("%c", arena[i][j]);
                arena_int[i][j] = 0;
            }
        }
        printf("\n");
    }
}

void criar_area_interna_mapa_2(char arena[28][100], int arena_int[28][100]){
    int i, j;
    
	posicionar_cursor(0, 2);
    for (i = 2; i < 28; i++) {
        for (j = 0; j < 100; j++) {
            arena[i][j] = ' ';
			
			if(i >= 2 && j == 1){
			 	printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;	
			}
            else if ((i >= 2 && i <= 4 || i >= 25 && i <= 27) && (j == 44 || j == 57) ||
                (i == 5 || i == 24) && (j >= 15 && j <= 33 || j == 44 || j == 57 || j >= 68 && j <= 86) ||
                (i == 6 || i == 8 || i == 21 || i == 23) && (j == 15 || j == 33 || j == 68 || j == 86) ||
                (i == 7 || i == 22) && (j >= 2 && j <= 4 || j >= 12  && j <= 14 || j == 15 || j == 33 || j == 68 || j >= 86 && j <= 89 || j >= 97 && j <= 99 ) ||
                (i == 9 || i == 20) && (j == 15 || j == 24 || j == 33 || j >= 44 && j <= 57 || j == 68 || j == 77 || j == 86) ||
                (i == 10 || i == 11 || i == 18 || i == 19) && (j == 15 || j == 24 || j == 33 || j == 44 || j == 57 || j == 68 || j == 77 || j == 86) ||
                (i == 12 || i == 17) && (j == 24 || j == 77) ||
                (i == 14 || i == 15) && (j >= 47 && j <= 54)) {

                printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;
            } 
			else {
                if(j <= 97){
					printf("%c", arena[i][j]);
                	arena_int[i][j] = 0;
				}
            }
        }
        printf("\n");
    }
}

void criar_area_interna_mapa_3(char arena[28][100], int arena_int[28][100]){
    int i, j;
    
	posicionar_cursor(0, 2);
    for (i = 2; i < 28; i++) {
        for (j = 0; j < 100; j++) {
            arena[i][j] = ' ';
			
			if(i >= 2 && j == 1){
			 	printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;	
			}
            else if ((i == 2 || i == 3 || i == 26 || i == 27) && (j == 41 || j == 60) ||
                (i == 5 || i == 6 || i == 23 || i == 24) && (j >= 16 && j <= 28 || j >= 74 && j <= 85) ||
                (i == 8 || i == 9 || i == 20 || i == 21) && (j == 41 || j == 50 || j == 51 || j == 60) ||
                (i == 10 || i == 19) && (j >= 2 && j <= 15 || j >= 29 && j <= 41 || j == 50 || j == 51 || j >= 60 && j <= 73 || j >= 87 && j <= 99) ||
				(i >= 11 && i <= 13 || i >= 16 && i <= 18) && (j == 50 || j == 51) ||
				(i == 14 || i == 15) && (j >= 23 && j <= 78)) {

                printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;
            } 
			else {
				if(j != 100){
					printf("%c", arena[i][j]);
                	arena_int[i][j] = 0;
				}
            }
        }
        printf("\n");
    }
}

void criar_area_interna_mapa_4(char arena[28][100], int arena_int[28][100]){
    int i, j;

    for (i = 2; i < 28; i++) {
        for (j = 0; j < 100 - 1; j++) {
            arena[i][j] = ' ';
			
			if(i >= 3 && j == 1){
			 	printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;	
			}
            else if ((i == 4 || i == 25) && (j >= 15 && j <= 18 || j >= 25 && j <= 28 || j >= 40 && j <= 45 || j >= 56 && j <= 61 || j >= 73 && j <= 76 || j >= 83 && j <= 86) ||
                (i == 5 || i == 24) && (j == 15 || j == 28 || j == 40 || j == 61 || j == 73 || j == 86) ||
                (i == 6 || i == 12 || i == 13 || i == 16 || i == 17 || i == 23) && (j == 40 || j == 61) ||
                (i >= 7 && i <= 9 || i >= 19 && i <= 22) && (j == 50 || j == 51) ||
                (i == 10 || i == 19) && ( j == 15 || j == 28 || j == 50 || j == 51 || j == 73 || j == 86) ||
                (i == 11 || i == 18) && (j >= 15 && j <= 18 || j >= 25 && j <= 28 || j == 50 || j == 51 ||j >= 73 && j <= 76 || j >= 83 && j <= 86) ||
				(i == 14 || i == 15) && (j >= 11 && j <= 32 || j >= 40 && j <= 45 || j >= 56 && j <= 61 || j >= 69 && j <= 90)) {

                printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;
            } 
			else {
				if(j != 98){
                	printf("%c", arena[i][j]);
                	arena_int[i][j] = 0;
				}
            }
        }
         printf("\n");
    }
}

void criar_area_interna_mapa_5(char arena[28][100], int arena_int[28][100]){
    int i, j;

    for (i = 2; i < 28; i++) {
        for (j = 0; j < 100 - 2; j++) {
            arena[i][j] = ' ';
			
			if(i >= 3 && j == 1){
			 	printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;	
			}
            else if ((i == 4 || i == 25) && (j >= 13  && j <= 25  || j >= 41 && j <= 60 || j >= 76 && j <= 88) ||
                (i >= 5 && i <= 7 || i >= 22 && i <= 25) && (j == 13 || j == 88) ||
                (i == 8 || i == 21) && (j == 13 || j >= 24 && j <= 31 || j >= 41 && j <= 60 || j >= 70 && j <= 77 || j == 88) ||
				(i == 9 || i == 20) && (j == 13 ||j == 24 || j == 50 || j == 51 || j == 77 || j == 88) ||
				(i == 10 || i == 19) && (j == 24 || j == 50 || j == 51 || j == 77) ||
				(i == 11 || i == 18) && (j == 24 || j == 77) ||
				(i == 14 || i == 15) && (j >= 9 && j <= 17 || j >= 31 && j <= 37 || j >= 46 && j <= 55 || j >= 64 && j <= 70 || j >= 84 && j <= 92)) {

                printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;
            } 
			else {
                printf("%c", arena[i][j]);
                arena_int[i][j] = 0;
            }
        }
        printf("\n");
    }
}

void criar_area_interna_mapa_6(char arena[28][100], int arena_int[28][100]){
    int i, j;
	posicionar_cursor(0, 2);
	
    for (i = 2; i < 28; i++) {
        for (j = 0; j < 100 + 1; j++) {
            arena[i][j] = ' ';
			
			if(i >= 2 && j == 1){
			 	printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;	
			}
            else if ((i >= 2  && i <= 4 || i >= 25 && i <= 27) && (j == 45 || j == 56) ||
            	(i == 5 || i == 24) && (j >= 13  && j <= 22 || j >= 36 && j <= 45 || j >= 56 && j <= 65 || j >= 79 && j <= 88) ||
                (i == 6 || i == 7 || i == 22 || i == 23) && (j == 13 || j == 88) ||
                (i == 8 || i == 21) && (j == 2 || j == 3 || j >= 11 && j <= 13 || j >= 24 && j <= 34 || j >= 67 && j <= 77 || j >= 88 && j <= 90 || j == 98 || j == 100) ||
				(i == 9 || i == 20) && (j == 13 || j == 45 || j == 56 || j == 88) ||
				(i == 10 || i == 19) && (j == 13 || j >= 42 && j <= 45 || j >= 56 && j <= 59 || j == 88) ||
				(i == 11 || i == 18) && (j == 13 || j >= 40 && j <= 42 || j >= 59 && j <= 61 || j == 88) ||
				(i == 12 || i == 17) && (j >= 13 && j <= 23 || j >= 35 && j <= 40 || j >= 61 && j <= 66 || j >= 77 && j <= 88)) {

                printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;
            } 
			else {
				if(j <= 98){
					printf("%c", arena[i][j]);
                	arena_int[i][j] = 0;
				}
            }
        }
        printf("\n");
    }
}

void criar_area_interna_mapa_7(char arena[28][100], int arena_int[28][100]){
    int i, j;
	
    for (i = 2; i < 28; i++) {
        for (j = 0; j <= 100; j++) {
            arena[i][j] = ' ';
			
			if(i >= 3 && j == 1){
			 	printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;	
			}
            else if ((i == 4 || i == 25 ) && (j == 45 || j == 57) ||
            	(i == 5 || i == 24 ) && (j >= 8  && j <= 19 || j >= 34 && j <= 45 || j >= 57 && j <= 68 ||j >= 82 && j <= 93) ||
                (i == 6 || i == 7 || i == 22 || i == 23) && (j == 8 || j == 93) ||
                (i == 8 || i == 21) && (j == 8 || j >= 21 && j <= 26 || j >= 42 && j <= 45 || j >= 57 && j <= 60 || j >= 76 && j <= 81 || j == 93)  ||
                (i == 9 || i == 20) && (j == 8 || j == 21 || j == 45 || j == 57 || j == 81 || j == 93) || 
				(i == 10 || i == 19) && (j >= 8  && j <= 10 || j >= 19 && j <= 21 || j == 45 || j == 57 || j >= 81 && j <= 83 || j >= 91 && j <= 93) ||
				(i == 11 || i == 18) && (j == 8 || j == 21 || j >= 39 && j <= 45 || j >= 57 && j <= 63 || j == 81 || j == 93) ||
				(i == 12 || i == 17) && (j == 8 || j >= 21 && j <= 23 || j >= 36 && j <= 39 || j >= 63 && j <= 66 || j >= 79 && j <= 81 || j == 93) ||
				(i == 13 || i == 16) && (j == 51) ||
				(i == 14 || i == 15) && (j >= 48 && j <= 54)) {

                printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;
            } 
			else {
				if(j <= 97){
					printf("%c", arena[i][j]);
                	arena_int[i][j] = 0;
				}
            }
        }
        printf("\n");
    }
}

void selecionar_mapa_escolhido(char arena[28][100], int arena_int[28][100]){
    switch(mapa_selecionado){
        case 1:
            criar_area_interna_mapa_1(arena, arena_int);
        break;

        case 2:
            criar_area_interna_mapa_2(arena, arena_int);
        break;

        case 3:
            criar_area_interna_mapa_3(arena, arena_int);
        break;

        case 4:
            criar_area_interna_mapa_4(arena, arena_int);
        break;

        case 5:
            criar_area_interna_mapa_5(arena, arena_int);
        break;
        
        case 6:
			criar_area_interna_mapa_6(arena, arena_int);
        	break;
        	
        case 7:
			criar_area_interna_mapa_7(arena, arena_int);
        	break;
        	
        case 8 : // caso o usuário escolha um mapa aleatório
        	srand(time(NULL));
        	mapa_selecionado = rand() % 6 + 1;
        	selecionar_mapa_escolhido(arena, arena_int); 
    }
}

void criar_arena(char arena[28][100], int arena_int[28][100]) {
    int i, j;
    
    for (i = 0; i <= 28; i++) {
        for (j = 0; j <= 100; j++) {
            arena[i][j] = ' ';

            // Se i ou j estiver nas bordas da arena, imprime o caractere de espaço com fundo branco
            if (i == 1 && j != 0 || i == 28 && j != 0 || j == 1 && i != 0 || j == 100 && i != 0) {
                printf("\033[1;47m%c\033[0m", arena[i][j]);
                arena_int[i][j] = 1;
            } else {
                printf("%c", arena[i][j]);
                arena_int[i][j] = 0;
            }
        }
        printf("\n\033[0m");
    }
    printf("\033[0m");
    posicionar_cursor(2, 2);
    selecionar_mapa_escolhido(arena, arena_int);
}



