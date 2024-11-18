#include <stdio.h>
#include <stdlib.h>


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define largura 100
#define altura 29

// Variáveis globais:
int loop;
char tempo_formatado[20];
static int tamanho_cobra_anterior;
static char ultima_direcao; // fará com que o primeiro movimento da cobra seja para a esquerda


// Structs:
struct jogador {
	int pontuacao;
	char nome_jogador[15], tempo_jogado[20];
};

struct cobra{
	int cabeca_x, cabeca_y;
	int tamanho_cobra;
	char simbolo_cobra;
	int comida_x, comida_y;
	int corpo_cobra[200][200];
};

/* A struct abaixo é para receber os dados dos arquivo Dados_jogadores.txt
que serão armazenados e posteriormente acessado no vetores de struct ranking*/
struct jogador_arq {
	int pontuacao;
	char nome_jogador[15], tempo_jogado[20];
};

void redimensionar_terminal(int largura_terminal, int altura_terminal) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {largura_terminal, altura_terminal};
    SMALL_RECT sr = {0, 0, coord.X - 1, coord.Y - 1};

    SetConsoleWindowInfo(handle, TRUE, &sr);
    SetConsoleScreenBufferSize(handle, coord);
}

void posicionar_cursor(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ocultar_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Obtém as informações atuais do cursor
    cursorInfo.bVisible = FALSE;                     // Define o cursor como invisível
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); 
}

void exibir_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Obtém as informações atuais do cursor
    cursorInfo.bVisible = TRUE;                      // Define o cursor como visível
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); 
}

void criar_arena(char area[altura][largura]) {
    int i, j;
    for (i = 0; i < altura + 1; i++) {
        for (j = 0; j < largura + 1; j++) {
			area[i][j] = ' ';

            //se i ou j estiver nas bordas da arena o printf imprime o caractere de espaço e pinta de branco
            if (i == 1 && j != 0|| i == altura && j != 0|| j == 1 && i != 0|| j == largura && i != 0) {
                printf("\033[1;47m%c\033[0m", area[i][j]);
            }
			else {
                printf("%c", area[i][j]);
            }
        }
        printf("\n");
    }
}

void imprimir_pontuacao(struct jogador* dados){
    posicionar_cursor(106, 8);
    printf("Pontuacao: %d\n", dados->pontuacao);
}

void imprimir_tempo(){
    posicionar_cursor(106, 10);
    printf("Tempo: %s\n", tempo_formatado);
}

void cronometrar_tempo(struct jogador* dados, clock_t tempo_inicial) {
    int tempo_jogado_em_segundos, minutos, segundos;
	clock_t tempo_atual;

    tempo_atual = clock();
    tempo_jogado_em_segundos = (int) (tempo_atual - tempo_inicial) / CLOCKS_PER_SEC;

    minutos = tempo_jogado_em_segundos / 60;
    segundos = tempo_jogado_em_segundos % 60;

    //formata o tempo no formato (minutos : segundos) e atualiza a variável global
    sprintf(tempo_formatado, "%02d:%02d", minutos, segundos);
}

void salvar_dados_jogador(struct jogador jog){
	FILE *f2 = fopen("Dados_jogador.txt", "a");

    // verifica se o arquivo foi aberto corretamente
    if (f2 == NULL) {
        printf("\n\n\n\t\t\t\t\tErro ao abrir o arquivo.\n");
        exit(1);
    }
    fprintf(f2, "%s %d  %s\n", jog.nome_jogador, jog.pontuacao, jog.tempo_jogado);
	fclose(f2);
}

void imprimir_cobra(struct cobra *cob, int cabeca_x_anterior, int cabeca_y_anterior) {
	int i;
    // Apaga o último segmento do corpo da cobra
    if (cob->tamanho_cobra > 0) {
        posicionar_cursor(cob->corpo_cobra[cob->tamanho_cobra - 1][0], cob->corpo_cobra[cob->tamanho_cobra - 1][1]);
        printf(" ");
    }

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
    printf("\033[0;32m%c\033[0m", cob->simbolo_cobra);  // Cor verde escuro para a cabeça

    // Imprime cada segmento do corpo da cobra na posição atualizada
    for (i = 0; i < cob->tamanho_cobra; i++) {
        posicionar_cursor(cob->corpo_cobra[i][0], cob->corpo_cobra[i][1]);
        printf("\033[0;92m%c\033[0m", cob->simbolo_cobra);  // Cor verde claro para o corpo
    }

    // Move o cursor para fora da área da cobra, para evitar sobreposição de impressão
    posicionar_cursor(1, altura);
}

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
    return ultima_direcao; // Se nenhuma tecla for digitada, retorna a ultima direção registrada.
}

void mover_cobra(struct cobra *pos_atual) {
    char input  = verificar_input_teclado();
    int cabeca_x_anterior = pos_atual->cabeca_x;
    int cabeca_y_anterior = pos_atual->cabeca_y;

    switch(input) {
        case 'w':
            pos_atual->cabeca_y--;
            break;
        case 'a':
            pos_atual->cabeca_x--;
            break;
        case 's':
            pos_atual->cabeca_y++;
            break;
        case 'd':
            pos_atual->cabeca_x++;
            break;
    }
	imprimir_cobra(pos_atual, cabeca_x_anterior, cabeca_y_anterior);
}

bool verificar_colisao(struct cobra dados_snk) {
    int i;
    bool colidiu = false;

    // Verifica se a cabeça da cobra colidiu com o próprio corpo:
    for (i = 1; i < dados_snk.tamanho_cobra && !colidiu; i++) {
		if (dados_snk.cabeca_x == dados_snk.corpo_cobra[i][0] && dados_snk.cabeca_y == dados_snk.corpo_cobra[i][1]) {
            colidiu = true;
        }
    }
    // Verifica se a cabeça da cobra colidiu com as bordas da área de jogo:
    if (dados_snk.cabeca_x <= 1 || dados_snk.cabeca_x >= largura || dados_snk.cabeca_y <= 1 || dados_snk.cabeca_y >= altura) {
        colidiu = true;
    }
    return colidiu;
}

int aumentar_velocidade(int tamanho_cobra) {
    static int delay_inicial = 200;
    int delay;

    // Reduz o delay em 5 milissegundos para cada segmento da cobra
    delay = delay_inicial - (tamanho_cobra * 5);

    // Define um limite mínimo para o delay
    if (delay < 50) {
        delay = 50;
    }

    return delay;
}

void gerar_comida(struct cobra *cob, char arena[altura][largura]) {
    srand(time(NULL));
    int local_valido = 0, comida_sobre_cobra,  i;

    // Se a cobra comeu, gera uma nova comida em um lugar aleatório.
    while (!local_valido) {
        comida_sobre_cobra = 0;
        cob->comida_x = rand() % (largura - 3) + 2;
        cob->comida_y = rand() % (altura - 3) + 2;

        // Verifica se a comida não está sendo gerada em cima da cabeça da cobra
        if (cob->comida_x == cob->cabeca_x && cob->comida_y == cob->cabeca_y){
            goto reiniciar_loop;
        }

        //verifica se a comida está sendo gerada em algum segmento do corpo da cobra
        for (i = 0; i < cob->tamanho_cobra && !comida_sobre_cobra; i++) {
            if (cob->comida_x == cob->corpo_cobra[i][0] && cob->comida_y == cob->corpo_cobra[i][1]) {
                comida_sobre_cobra = 1; // flag para parar o loop for;
            }
        }

        if (comida_sobre_cobra) {
            goto reiniciar_loop;
        }

        // Atualiza a arena com a nova posição da comida
        arena[cob->comida_y][cob->comida_x] = 219;

        //flag para parar o loop caso a posição da comida tenha comprido todas as condições
        local_valido = 1;

        reiniciar_loop:; // Ponto de reinício do loop, caso a comida esteja na cabeça ou corpo da cobra
    }

    // Desenha a comida na área
    printf("\033[1;31m\033[%d;%dH%c\033[0m", cob->comida_y + 1, cob->comida_x + 1, arena[cob->comida_y][cob->comida_x]);
}

bool verificar_se_cobra_comeu(struct cobra dados_cobra){
    bool resultado = false;

    if ((dados_cobra.cabeca_x == dados_cobra.comida_x) && (dados_cobra.cabeca_y == dados_cobra.comida_y) == 1) {
        resultado = true;
    }
    return resultado;
}

void inicializar_jogo(struct jogador *jogador, struct cobra *cobra,char arena[altura][largura]){
    criar_arena(arena);

    jogador->pontuacao = 0;
    strcpy(jogador->tempo_jogado, "00 : 00");

    cobra->simbolo_cobra = 219;
    cobra->tamanho_cobra = 2;
    cobra->cabeca_x = (largura - 1) / 2;
    cobra->cabeca_y = altura / 2;
 
    gerar_comida(cobra, arena);
}

void apresentar_aviso_encoding() {

    // Mensagem em vermelho
    printf(
        "\n\n\n\n\t\t\t\033[1;31m      |-------------------------------------------------------------|\n"
        "\t\t\t      |                                                             |\n"
        "\t\t\t      |    Aviso: O código foi codificado em UTF-8!                 |\n"
        "\t\t\t      |                                                             |\n"
        "\t\t\t      |    Caso a exibição de alguns caracteres especiais esteja  |\n"
        "\t\t\t      |    esquisita, isso pode ter sido causado por uma            |\n"
        "\t\t\t      |    codificação diferente da UTF-8 na sua IDE.             |\n"
        "\t\t\t      |                                                             |\n"
        "\t\t\t      |-------------------------------------------------------------|\n\n"
        "\033[0m"
    );

    Sleep(6000);
    system("cls");
}

void pedir_nome(struct jogador *jogador) {
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

char menu_principal(){
    char opcao;

    printf("\033[32m\n            *************       ****          *****      ************       ****       *****    **************"
                   "\n          *****************    *******        *****    ****************    ******     ******   ****************"
                   "\n         ********     ******   ********       *****   ******      ******   ******    ******    *************** "
                   "\n        ********               *********      *****   *****        *****   ******   ******     ******          "
                   "\n         *********             **********     *****   *****        *****   ******  ******      ******          "
                   "\n           ************        ***** *****    *****   *****        *****   ****** ******       *************** "
                   "\n             ************      *****  *****   *****   ******************   ************        ****************"
                   "\n                  *********    *****   *****  *****   ******************   ************        *************** "
                   "\n                     *******   *****    ***** *****   ******      ******   ****** ******       ******          "
                   "\n                     *******   *****     **********   *****        *****   ******  ******      ******          "
                   "\n       ******     *********    *****      *********   *****        *****   ******   ******     *************** "
                   "\n         *****************     *****       ********   *****        *****   ******    ******    ****************"
                   "\n           *************       *****         *****   ******        ******   ****      *****     ************** \n\033[0m");
    
    printf("\n\n\t\t\t\t\t  |----------------------------------|" 
           "\n\t\t\t\t\t  |                                  |"
           "\n\t\t\t\t\t  |           1- Novo jogo           |"
           "\n\t\t\t\t\t  |                                  |"
           "\n\t\t\t\t\t  |           2- Ranking             |"
           "\n\t\t\t\t\t  |                                  |"
           "\n\t\t\t\t\t  |           3- Controles           |"
           "\n\t\t\t\t\t  |                                  |"
           "\n\t\t\t\t\t  |           4- Sair                |"
           "\n\t\t\t\t\t  |                                  |"
           "\n\t\t\t\t\t  |----------------------------------|");
    posicionar_cursor(60,29);

    scanf(" %c", &opcao);
    printf("opção: %c", opcao);

    return opcao;
}

void apresentar_game_over(struct jogador print_dados) {
	
    system("cls");
    printf("\n\n\t\t\t\t\t     |-----------------------------------|\n"
           "\t\t\t\t\t     |                                   |\n"
           "\t\t\t\t\t     |            Fim de jogo            |\n"
           "\t\t\t\t\t     |                                   |\n"
           "\t\t\t\t\t     |       Jogador: %-10s         |\n"
           "\t\t\t\t\t     |                                   |\n"
           "\t\t\t\t\t     |       Pontuação: %-4d             |\n"
           "\t\t\t\t\t     |                                   |\n"
           "\t\t\t\t\t     |       Tempo: %-10s           |\n"
           "\t\t\t\t\t     |                                   |\n"
           "\t\t\t\t\t     |-----------------------------------|",
           print_dados.nome_jogador, print_dados.pontuacao, print_dados.tempo_jogado);
    Sleep(5000);
    system("cls");
    salvar_dados_jogador(print_dados);
}

void ler_ranking_do_arquivo(FILE *f2, struct jogador_arq ranking[300]) {
    char linha[100]; // Buffer para ler cada linha
    int i = 0; // Índice de jogadores

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), f2) != NULL && i < 300) {
        // Remove a quebra de linha, se houver
        linha[strcspn(linha, "\n")] = 0;

        // Usa sscanf para ler os dados formatados na linha
        int result = sscanf(linha, "%s %d %5s", ranking[i].nome_jogador, &ranking[i].pontuacao, ranking[i].tempo_jogado);

        // Verifica se os dados foram lidos corretamente
        if (result == 3) {
            // Dados lidos corretamente
            i++;
        } else {
            // Se ocorrer erro na leitura, exibe mensagem
            printf("Erro ao ler dados na linha: %s\n", linha);
        }
    }
}

void ordenar_ranking(struct jogador_arq ranking[300]) {
    int i, j;
    // Ordena o array em ordem decrescente de pontuação, em caso de empate, ordena por tempo
    for (i = 0; i < 300 - 1; i++) {
        for (j = i + 1; j < 300; j++) {
            if (ranking[j].pontuacao > ranking[i].pontuacao ||
                (ranking[j].pontuacao == ranking[i].pontuacao && strcmp(ranking[j].tempo_jogado, ranking[i].tempo_jogado) < 0)) {
                // Troca as posições dos jogadores
                struct jogador_arq temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }
}

void imprimir_ranking(struct jogador_arq ranking[300]) {
	int i;
    // Impressão dos 15 melhores jogadores
    printf("\n\n\n\n\t\t\t\t|----------------------------------------------------|\n\t\t\t\t|         Ranking dos 10 melhores jogadores:         |\n\t\t\t\t|                                                    |\n");
    for (i = 0; i < 15; i++) {
        printf("\t\t\t\t| %-2dº lugar: %-10s - score: %-4d - tempo: %-5s |\n", i + 1, ranking[i].nome_jogador, ranking[i].pontuacao, ranking[i].tempo_jogado);
    }
    printf("\t\t\t\t|                                                    |\n\t\t\t\t|----------------------------------------------------|");

    Sleep(10000);
    system("cls");
}

int main (){
	redimensionar_terminal(120, 31);
	setlocale(LC_ALL, "portuguese");
	int i = 0, j;
	int velocidade_jogo;
	bool retorno_colisao, retorno_comida;

	char arena[altura][largura];
    char opcao;

	struct jogador dados_jogador;
	struct cobra dados_cobra;
	struct jogador_arq ranking[300] = {0};

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
                ultima_direcao = 'a';

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
                system("cls");
                printf("\n\n\t\t\t\t|-----------------------------------------|"
					   "\n\t\t\t\t|                                         |"
					   "\n\t\t\t\t|     Controles:                          |"
					   "\n\t\t\t\t|                                         |"
					   "\n\t\t\t\t|         cima:      W                    |"
					   "\n\t\t\t\t|                                         |"
					   "\n\t\t\t\t|         Esquerda:  A                    |"
					   "\n\t\t\t\t|                                         |"
					   "\n\t\t\t\t|         Baixo:     S                    |"
					   "\n\t\t\t\t|                                         |"
					   "\n\t\t\t\t|         Direita:   D                    |"
					   "\n\t\t\t\t|                                         |"
					   "\n\t\t\t\t|-----------------------------------------|");
                Sleep(5000);
                system("cls");
                break;
                
            case '4':
                loop = 1;
                break;
                
            default: // Se foi digitado um número inteiro fora do intervalo de 1 a 4:
                printf("\n\n\t\t\t\t\t  |----------------------------------|"
				       "\n\t\t\t\t\t  |                                  |"
					   "\n\t\t\t\t\t  |     Digite um n?mero v?lido!     |"
					   "\n\t\t\t\t\t  |                                  |"
					   "\n\t\t\t\t\t  |----------------------------------|");
                Sleep (3000);
                system("cls");
                break;
        }
	}while(loop == 0);
	return 0;
}
