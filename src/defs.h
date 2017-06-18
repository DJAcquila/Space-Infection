#ifndef DEFS_H
#define DEFS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "SDL/SDL_image.h"
#include <sys/time.h>
#include <math.h>

#define TamJanela_x  1360
#define TamJanela_y 720

enum boolean
{
	true = 1, false = 0
};

typedef enum boolean bool;

//Struct para o inimigo (Movimento automatico, velocidade em ambos os eixos, e se esta vivo ou morto)
struct inimigos
{
	float inimigoX;
	float inimigoY;
	float inimigoCA;
	float velx;
	float vely;
	bool colisaoX;
	bool colisaoY;
	int flag;
	bool vivo;
};
typedef struct inimigos Inimigos;

//PERSONAGEM/CARRO/NAVE
struct car
{
	float carX;
	float carY;
	float carComp;
	float carAlt;
	bool colisaoX;
	bool colisaoY;
	bool car_bar; //Se for true eh pq ha barreira
};
typedef struct car Car;

//Struct para as barreiras
struct barreira
{
	float barreiraX;
	float barreiraY;
	float barreiraCA;
	bool vivo;
	bool colisaoX;
	bool colisaoY;
	bool aparecer_barreira;

};
typedef struct barreira Barreira;

//Opcoes do menu
struct options
{
	float X;
	float Y;
	float Comp;
	float Alt;
	unsigned int texture_uns;
	unsigned int texture_sel;
	bool flagSel;
};
typedef struct options Options;

//Struct referente as opcoes (Para caso precise de extras)
struct menu
{
	Options op[3];
	
};
typedef struct menu Menu;


// Algarismos para o contador de inimigos do menu
struct algarismos
{
	int parte;

	float X;
	float Y;
	float Comp;
	float Alt;
	unsigned int text;
};
typedef struct algarismos Algarismos;

struct bullet
{
	float velX;
	float velY;
	
	float posX;
	float posY;
	
	float Comp;
	float Alt;
	
	bool balaNeles;
	bool vivo;
	
	int tecla_atual;
	
	unsigned int textureUp;

};
typedef struct bullet Bullet;

struct recharge
{
	float x;
	float y;
	float comp;
	float alt;

	int cont;

	int vivo;

	bool pegar_bala;
	unsigned int texture;
};
typedef struct recharge Recharge;

struct enemy2
{
	float x;
	float y;
	float comp;
	float alt;
	float vel;

	int cont;

	unsigned int texture;

	bool vivo;
	bool start;

	int hits;

	bool colisaoX;
	bool colisaoY;
};
typedef struct enemy2 Enemy2;

SDL_Surface* screen;
SDL_Surface* screen_menu;

#endif //INCLUDES_H
