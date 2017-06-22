#include "screen.h"

/*
|===============================================================================================|
|				Acquila Santos Rocha - Instituto de Informática UFG								|
|																								|		
|	Esta função configura as necessidades gráficas do jogo:										|
|		1. Inicia a tela.																		|
|		2. Cria a função que recebe a textura (imagem)											|
|		3. 																						|
|===============================================================================================|
*/

/*Esta função é responsável por renderizar uma string em forma de textura, para mostrar na tela */
/*Ela vai mostrar na tela os pontos, do jogdor, se está ou não usando a barreira, e a quantidade de balas e barreiras disponíveis*/
void renderBitmapString (float x, float y, char *string)
{
	int len;
	int i;
	glColor4f(1,1,1,1);//Define a cor da letra
	glRasterPos2i(x,y);//Define o posicionamento que esta na matriz de desenho

	glDisable(GL_TEXTURE);//Desabilita a textura
	glDisable(GL_TEXTURE_2D);//Desabilita a textura 2d
	/*Laço que percorre a string passada como parâmetro transformando cada caracter em uma bitmap string*/
	for(i = 0, len = strlen(string); i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,(int)string[i]);	
	}

	glEnable(GL_TEXTURE_2D);//Habilita textura 2d
	glEnable(GL_TEXTURE);//Habilita textura
}

/*Talvez esta função seja a mais usada no programa, ela é a responsável por identificar a imagem e criar a textura para ela*/
/*GLuint: um unsigned binary int*/
GLuint createTexture(const char nome[])
{  
	SDL_Surface* imagem;
	imagem = IMG_Load(nome);
	if(!imagem) 
	{	
		printf("Imagem a ser carregada: %s\n", IMG_GetError());
	}

	SDL_DisplayFormatAlpha(imagem);//Esta função habilita o canal alpha da textura

	GLuint id = 0;//Ende

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagem->w, imagem->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagem->pixels);

	SDL_FreeSurface(imagem);
	
	return id;
}
void ObjectTexture(float X, float Y, float Comp, float Alt, unsigned int texture)
{
	glColor4ub(255, 255, 255, 255);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture );
			
			glBegin(GL_QUADS);
		
				glTexCoord2d(0,0);	glVertex2f(X, Y);
				glTexCoord2d(1,0);	glVertex2f(X + Comp, Y);
				glTexCoord2d(1,1);	glVertex2f(X + Comp, Y + Alt);
				glTexCoord2d(0,1);	glVertex2f(X, Y + Alt);	
	glEnd();
}
void initScreen(int argc, char *args[])
{
	
	glutInit(&argc, args);
	SDL_Init(SDL_INIT_EVERYTHING);

    //Restringir us da memoria
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Nome da janela
	SDL_WM_SetCaption("Space Infection",NULL);


	screen_menu = SDL_SetVideoMode(TamJanela_x, TamJanela_y, 32, SDL_OPENGL|SDL_GL_DOUBLEBUFFER/*|SDL_FULLSCREEN*/);

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	
	//Cor inicial de janela
	glClearColor(0,0,0,0.0);

	//Area exibida pela janela
	glViewport(0,0,TamJanela_x,TamJanela_y);
	glShadeModel(GL_SMOOTH);
	
	//2d
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();//Para mexer com imagens geometricas

	//3d
	glDisable(GL_DEPTH_TEST);

	//uso da imagem 
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}