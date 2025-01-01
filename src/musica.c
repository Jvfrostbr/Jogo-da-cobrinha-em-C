#include <windows.h>
#include "musica.h"

void tocar_musica_principal() {
    PlaySound(TEXT("../musicas/TemaPrincipal.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void tocar_som_gameover(){
	PlaySound(TEXT("../musicas/Gameover.wav"), NULL, SND_ASYNC);
}

void tocar_som_comida(){
	PlaySound(TEXT("../musicas/Comida.wav"), NULL, SND_ASYNC);
}

void tocar_som_comida_especial(){
	PlaySound(TEXT("../musicas/ComidaEspecial.wav"), NULL, SND_ASYNC);
}

void tocar_som_perdeu_comida_especial(){
	PlaySound(TEXT("../musicas/PerdeuComidaEspecial.wav"), NULL, SND_ASYNC);
}

void tocar_som_gameinicio(){
	PlaySound(TEXT("../musicas/GameInicio.wav"), NULL, SND_ASYNC);
}


void parar_musica() {
    PlaySound(NULL, NULL, SND_PURGE);
}
