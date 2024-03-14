#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "mapa.h"
#include <ctype.h>
#include <time.h>
#include "ui.h"

MAPA m;
POSICAO heroi;
int tempilula = 0;

int direcaofantasma(int xatual, int yatual, int* xdestino, int* ydestino) {
	int opcao[4][2] = {
		{xatual + 1, yatual},
		{xatual - 1, yatual},
		{xatual, yatual + 1},
		{xatual, yatual - 1}
	};

	srand(time(0));

	for (int i = 0; i < 10; i++) {
		int posicao = rand() % 4;

		if (podeandar(&m, FANTASMA, opcao[posicao][0], opcao[posicao][1])) {
			*xdestino = opcao[posicao][0];
			*ydestino = opcao[posicao][1];

			return 1;
		}
	}
	
	return 0;
}

void fantasmas(){
	MAPA copia;

	copiamapa(&m, &copia);

	for (int i = 0; i < m.linhas; i++) {
		for (int j = 0; j < m.colunas; j++) {

			if(copia.matriz[i][j] == FANTASMA){
				int xdestino;
				int ydestino;
			
				int encontrou = direcaofantasma(i, j, &xdestino, &ydestino);

				if(encontrou){
					andanomapa(&m, i, j, xdestino, ydestino);
				}
			}
		}
	}
	liberamapa(&copia);
}

int ehdirecao(char direcao){
	return direcao == CIMA || direcao == BAIXO || direcao == ESQUERDA || direcao == DIREITA;
}

void mover(char direcao) {

	if(!ehdirecao(direcao)){
		return;
	}

	int xseguinte = heroi.x;
	int yseguinte = heroi.y;

	switch(direcao) {
		case CIMA:
			xseguinte--;
			break;
		case BAIXO:
			xseguinte++;
			break;
		case ESQUERDA:
			yseguinte--;
			break;
		case DIREITA:
			yseguinte++;
			break;
	}

	if(!podeandar(&m, HEROI, xseguinte, yseguinte))
		return;

	if(ehpersonagem(&m, PILULA, xseguinte, yseguinte)) {
		tempilula++;
	}

	andanomapa(&m, heroi.x, heroi.y, xseguinte, yseguinte);
	heroi.x = xseguinte;
	heroi.y = yseguinte;
}

void explode() {
	if(!tempilula) return;

	raiodaexplosao(heroi.x, heroi.y, 0, 1, 3);
	raiodaexplosao(heroi.x, heroi.y, 0, -1, 3);
	raiodaexplosao(heroi.x, heroi.y, 1, 0, 3);
	raiodaexplosao(heroi.x, heroi.y, -1, 0, 3);

	tempilula--;
}

void raiodaexplosao(int x, int y, int somax, int somay, int qtd) {
	if(qtd == 0) return;

	int novox = x + somax;
	int novoy = y + somay;

	if(!ehvalido(&m, novox, novoy) || ehparede(&m, novox, novoy)) return;

	m.matriz[novox][novoy] = VAZIO;
	raiodaexplosao(novox, novoy, somax, somay, qtd - 1);
}

int acabou() {
	POSICAO pos;
	int encontrouheroi = encontraheroi(&m, &pos, HEROI);
	int encontroufantasma = encontraheroi(&m, &pos, FANTASMA);
	return !encontrouheroi || !encontroufantasma; 
}

void resultado() {
	POSICAO pos;
    int temheroi = encontraheroi(&m, &pos, HEROI);
	int temfantasma = encontraheroi(&m, &pos, FANTASMA);

    if(!temfantasma) {
    	vitoria();
  	} 

  	if(!temheroi) {
    	derrota();
  	}
}

void vitoria() {
	system("cls");
	printf("  __   _____  _   _  __        _____ _   _ _         \n");
	printf("  \\ \\ / / _ \\| | | | \\ \\      / /_ _| \\ | | |  \n");
	printf("   \\ V / | | | | | |  \\ \\ /\\ / / | ||  \\| | |   \n");
	printf("    | || |_| | |_| |   \\ V  V /  | || |\\  |_|      \n");
	printf("    |_| \\___/ \\___/     \\_/\\_/  |___|_| \\_(_)   \n");
	printf("                ___________                    		 \n");
	printf("               '._==_==_=_.'                         \n");
	printf("               .-\\:      /-.                        \n");
	printf("              | (|:.     |) |                        \n");
	printf("               '-|:.     |-'                         \n");
	printf("                 \\::.    /                          \n");
	printf("                  '::. .'                            \n");
	printf("                    ) (                              \n");
	printf("                  _.' '._                            \n");
	printf("                 '-------'                           \n\n");

}

void derrota() {
	system("cls");
	printf("  ____    _    __  __ _____    _____     _______ ____  _          \n");
	printf(" / ___|  / \\  |  \\/  | ____|  / _ \\ \\   / / ____|  _ \\| |    \n");
	printf("| |  _  / _ \\ | |\\/| |  _|   | | | \\ \\ / /|  _| | |_) | |     \n");
	printf("| |_| |/ ___ \\| |  | | |___  | |_| |\\ V / | |___|  _ <|_|       \n");
	printf(" \\____/_/   \\_\\_|  |_|_____|  \\___/  \\_/  |_____|_| \\_(_)   \n");
	printf("                       _______________                            \n");        
	printf("                      /               \\                          \n");      
	printf("                     /                 \\                         \n");  
	printf("                   //                   \\/\\                     \n");
	printf("                   \\|   XXXX     XXXX   | /                      \n");
	printf("                    |   XXXX     XXXX   |/                        \n");
	printf("                    |   XXX       XXX   |                         \n");
	printf("                    |                   |                         \n");
	printf("                    \\__      XXX      __/                        \n");
	printf("                      |\\     XXX     /|                          \n");
	printf("                      | |           | |                           \n");
	printf("                      | I I I I I I I |                           \n");
	printf("                      |  I I I I I I  |                           \n");
	printf("                      \\_             _/                          \n");
	printf("                        \\_         _/                            \n");
	printf("                          \\_______/                              \n\n");
}

int main() {

	char comando;

	lemapa(&m);
	encontraheroi(&m, &heroi, '@');

    do {
    	printf("Tem pilula: %s \n", (tempilula ? "SIM" : "NAO"));
    	printf("PILULAS: %d \n", tempilula);
    	imprimemapa(&m);

    	scanf(" %c", &comando);
    	comando = tolower(comando);
    	if (comando == BOMBA) explode();
    	mover(comando);
    	fantasmas();

    } while(!acabou());

    resultado();

    liberamapa(&m);

}