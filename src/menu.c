#include <stdio.h>
#include <stdlib.h>

#include "tela.h"
#include "ranking.h"
#include "cobra.h"
#include "jogador.h"
#include "jogo.h" 


char menu_principal() {
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
    return opcao;
}