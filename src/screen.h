#ifndef SCREEN_H
#define SCREEN_H
#include "defs.h"
/*
||==============================================================================================||
||				Acquila Santos Rocha - Instituto de Informática UFG								||
||																								||
||	Este arquivo é o header do arquivo que implementa as necessidades gráficas do jogo:		    ||
||		1. Inicia a tela.																		||
||		2. Cria a função que recebe a textura (imagem)											||
||		3. Funçao para transformar string em imagem												||
||==============================================================================================||
*/
void renderBitmapString (float x, float y, char *string);
GLuint createTexture(const char nome[]);
void ObjectTexture(float X, float Y, float Comp, float Alt, unsigned int texture);
void initScreen(int argc, char *args[]);

#endif