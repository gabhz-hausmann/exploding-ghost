#ifndef _MAPA_H
#define _MAPA_H

#define HEROI '@'
#define FANTASMA '&'
#define VAZIO '*'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '='
#define PILULA '!'

struct mapa {
	char** matriz;
	int linhas, colunas;
};

typedef struct mapa MAPA;

struct posicao {
	int x, y;
};

typedef struct posicao POSICAO;

void alocando(); 
void lemapa();
void liberamapa();
void imprimemapa();
void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
void copiamapa(MAPA* origem, MAPA* destino);

int encontraheroi(MAPA* m, POSICAO* p, char c);
int ehvazio(MAPA* m, int x, int y);
int ehvalido(MAPA* m, int x, int y);
int ehpersonagem(MAPA* m, char personagem, int x, int y);
int podeandar(MAPA* m, char personagem, int x, int y);
int ehparede(MAPA* m, int x, int y);

#endif