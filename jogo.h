#ifndef _JOGO_H
#define _JOGO_H

#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define BOMBA 'b'

int acabou();
int ehdirecao(char direcao);
int direcaofantasma(int xatual, int yatual, int* xdestino, int* ydestino);

void fantasmas();
void explode();
void raiodaexplosao(int x, int y, int somax, int somay, int qtd);
void mover(char direcao);
void resultado();
void vitoria();
void derrota();

#endif