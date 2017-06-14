#include "structs.h"


#define TamJanela_x  1360
#define TamJanela_y 720 

int cont = 10;

int MAX_BALAS = 500; 

int MAX_RECHARGE = 3;

int MAX_BARREIRAS = 3;

int MAX_ENEMY2 = 40; 

typedef struct game Game ;

SDL_Surface* screen;
SDL_Surface* screen_menu;

/*
************************************************************************************************************************************************
*/
//Colisao entre dois elementos

bool colisionBarreiraCar(Inimigos* iniA, Car* iniB)
{
	if(!(iniA->inimigoY + iniA->inimigoCA < iniB->carY))
	{ 
		iniA->inimigoY;
		iniB->colisaoY;
	}
	if(!(iniA->inimigoY > iniB->carY + iniB->carAlt)) 
	{ 
		iniA->inimigoY;
		iniB->colisaoY;
	}
	if(!(iniA->inimigoX + iniA->inimigoCA < iniB->carX)) 
	{
		iniA->inimigoX;
		iniB->colisaoX;
	}
	if(!(iniA->inimigoX > iniB->carX + iniB->carComp))
	{
		iniA->inimigoX;
		iniB->colisaoX;
	}

	return !(iniA->inimigoY + iniA->inimigoCA < iniB->carY || iniA->inimigoY > iniB->carY + iniB->carAlt || iniA->inimigoX + iniA->inimigoCA < iniB->carX || iniA->inimigoX > iniB->carX + iniB->carComp);
		
}

bool ColisionCarBar (Barreira* ini, Car* c)
{
	
	return !(ini->barreiraY + ini->barreiraCA < c->carY || ini->barreiraY > c->carY + c->carAlt || ini->barreiraX + ini->barreiraCA < c->carX || ini->barreiraX > c->carX + c->carComp);
}



bool colision2Enemy(Inimigos* iniA, Inimigos* iniB)
{
	//Identificar lado da colisao
	if(!(iniA->inimigoY + iniA->inimigoCA < iniB->inimigoY))
	{ 
		iniA->colisaoY;
		iniB->colisaoY;
	}
	if(!(iniA->inimigoY > iniB->inimigoY + iniB->inimigoCA)) 
	{ 
		iniA->colisaoY;
		iniB->colisaoY;
	}
	if(!(iniA->inimigoX + iniA->inimigoCA < iniB->inimigoX)) 
	{
		iniA->colisaoX;
		iniB->colisaoX;
	}
	if(!(iniA->inimigoX > iniB->inimigoX + iniB->inimigoCA)) 
	{
		iniA->colisaoX;
		iniB->colisaoX;
	}

	return !(iniA->inimigoY + iniA->inimigoCA < iniB->inimigoY || iniA->inimigoY > iniB->inimigoY + iniB->inimigoCA || iniA->inimigoX + iniA->inimigoCA < iniB->inimigoX || iniA->inimigoX > iniB->inimigoX + iniB->inimigoCA);
		
}

bool ColisionEnemyCar (Inimigos* ini, Car* c)
{
	return !(ini->inimigoY + ini->inimigoCA < c->carY || ini->inimigoY > c->carY + c->carAlt || ini->inimigoX + ini->inimigoCA < c->carX || ini->inimigoX > c->carX + c->carComp);
}

bool ColisionBulEnemy (Inimigos* ini, Bullet* bul)
{
	return !(ini->inimigoY + ini->inimigoCA < bul->posY || ini->inimigoY > bul->posY + bul->Alt || ini->inimigoX + ini->inimigoCA < bul->posX || ini->inimigoX > bul->posX + bul->Comp);
}
bool ColisionRechargeCar (Recharge* rer, Car* c)
{
	return !(c->carY + c->carAlt < rer->y || c->carY > rer->y + rer->alt || c->carX + c->carComp < rer->x || c->carX > rer->x + rer->comp);
}

bool ColisionBulEnemy2 (Enemy2* ini, Bullet* bul)
{
	return !(ini->y + ini->alt < bul->posY || ini->y > bul->posY + bul->Alt || ini->x + ini->comp < bul->posX || ini->x > bul->posX + bul->Comp);
}

bool ColisionCarEnemy2(Enemy2* rer,  Car*c)
{
	return !(c->carY + c->carAlt < rer->y || c->carY > rer->y + rer->alt || c->carX + c->carComp < rer->x || c->carX > rer->x + rer->comp);
}

bool EnemyColision(Inimigos* ini)
{
	bool coli = false;
	int i; int j;
	for(i = 0; i < cont; i++)
	{
		(ini+i)->flag = 1;
	}
	for(i = 0; i < cont; i++)
	{
		for (j = i+1; j < cont; j++)
		{	
			if(colision2Enemy( (ini+i),(ini+j) ) )
			{	
				coli = true;
				(ini+i)->flag = -(ini+i)->flag;
				(ini+j)->flag = -(ini+j)->flag;
				(ini+i)->colisaoX = true;
				(ini+j)->colisaoY = true;
			}		 
		}
	}
	return coli;
}
bool MesmaDirecao(Inimigos* iniA, Inimigos* iniB)
{

	if(iniB->flag > 0 && iniB->flag > 0) return true;
	else if(iniA->flag < 0 && iniB->flag < 0) return true;
			
	return false;
}
void EnemyMove (Inimigos* ini)
{
	int n;
	for(n = 0; n < cont; n++)
	{
		(ini+n)->inimigoX += (ini+n)->velx;
		(ini+n)->inimigoY += (ini+n)->vely;
		
		//logica de colisao do inimigo
		
		if((ini+n)->inimigoX < 0)
		{
	 		(ini+n)->velx = -(ini+n)->velx;

		}
		else if(((ini+n)->inimigoX + (ini+n)->inimigoCA) > TamJanela_x-5 )
		{
			(ini+n)->velx = -(ini+n)->velx;
		}
		if((ini+n)->inimigoY < 0)
		{
			(ini+n)->vely = -(ini+n)->vely;

		}
		else if(((ini+n)->inimigoY + (ini+n)->inimigoCA) > TamJanela_y-5 )
		{
			(ini+n)->vely = -(ini+n)->vely;
		}
		
			
		int aux; //Variavel auxiliar
		for(aux = 0; aux < cont; aux++)
		{	
			if(EnemyColision(ini))
			{
				if((ini+aux)->colisaoX)
				{
					(ini+aux)->velx = -(ini+aux)->velx;
					(ini+aux)->colisaoX = false;
				}
				if((ini+aux)->colisaoY)
				{
					(ini+aux)->vely = -(ini+aux)->vely;
					(ini+aux)->colisaoY = false;
				}

				/*else if((ini+aux)->colisaoX || (ini+aux)->colisaoY)
				{	
					(ini+aux)->velx = -(ini+aux)->velx;
					(ini+aux)->colisaoX = false;
					(ini+aux)->vely = -(ini+aux)->vely;
					(ini+aux)->colisaoY = false;
				}*/
			}
		}
	}	
}



void CarColision (Car* c, SDL_Event event, bool esq, bool dir, bool cima, bool baixo)
{
//Colisao do personagem com os limites da tela
	if(c->carX < 0 )
	{
		c->carX = 0;
	}
	else if((c->carX + c->carComp) > TamJanela_x )
	{
		c->carX = TamJanela_x - c->carComp;
	}
	else if(c->carY < 0)
	{
		c->carY = 0;

	}
	else if((c->carY + c->carAlt) > TamJanela_y )
	{
		c->carY = TamJanela_y - c->carAlt;
	}
	if(c->colisaoX && c->car_bar)
	{
		//Para evitar que o carro ultrapasse os limites do inimigo no momento da colisao dreta
		while(SDL_PollEvent(&event))
		{	

			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_LEFT)
				{
					c->carX += 100;

				}
			
				else if(event.key.keysym.sym == SDLK_RIGHT)
				{
					c->carX -= 100;

				}
			}
		}
	}
	if(c->colisaoY && c->car_bar)
	{
		while(SDL_PollEvent(&event))
		{	

			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_UP)
				{
					c->carY += 100;

				}
				else if(event.key.keysym.sym == SDLK_DOWN)
				{
					c->carY -= 100;
				}
			}
		}
	
	}


}
/*
************************************************************************************************************************************************
*/
//Fonte

void renderBitmapString (float x, float y, char *string)
{
	
	int len;
	int i;
	glColor4f(1,1,1,1);
	glRasterPos2i(x,y);

	glDisable(GL_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	for(i = 0, len = strlen(string); i < len;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,(int)string[i]);	
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);
}

/*
************************************************************************************************************************************************
*/


//Carregamento de imagem

GLuint createTexture(const char nome[])
{  

   SDL_Surface* imagem;
   imagem = IMG_Load(nome);
   if(!imagem) 
   {
    printf("IMG_Load: %s\n", IMG_GetError());
    // handle error
	}

   SDL_DisplayFormatAlpha(imagem);

   GLuint id = 0;

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
/*
************************************************************************************************************************************************
*/

//Atribuir essa funcao a quantidade de barreiras;



void preSets(Barreira* b, int qtd_barreiras, Bullet* bul, Inimigos* ini, Recharge* rer, Car* c, Enemy2* enem)
{
	int i;
	for(i = 0; i < (MAX_BARREIRAS); i++)
	{
		(b+i)->vivo = true;
		(b+i)->barreiraX = rand () % TamJanela_x - 50;
		(b+i)->barreiraY = rand () % TamJanela_y - 50;
		(b+i)->barreiraCA = 50;
	}
	int n;
	for(n = 0; n < MAX_BALAS; n++)
	{
		(bul+n)->Comp = 13;
		(bul+n)->Alt = 18;
		(bul+n)->velY = 20;
		(bul+n)->balaNeles = false;
		(bul+n)->vivo = false;
	}
	c->carX = 1000;
	c->carY = TamJanela_y-50/2;
	c->carComp = 50;
	c->carAlt = 50;
	c->car_bar = false;

	float x, y;
	srand(time(NULL));

	for(n = 0; n < cont; n++)
	{ 
		do{
			do
			{
				x = rand () %  TamJanela_x ;
			}while(x < 100 || x > 1240);
			y = rand () % 360;
		}while(ColisionEnemyCar((ini+n),c) && EnemyColision(ini));

		
		(ini+n)->velx = 4;
		
		
		(ini + n)->vely = (ini + n)->velx;
		(ini + n)->inimigoX = x;
		(ini + n)->inimigoY = y;
		(ini + n)->inimigoCA = 30;
		(ini + n)->vivo = true;
	}
	
	//Propriedades da recarga de balas

	
	for(n = 0; n < MAX_RECHARGE; n++)
	{
		(rer + n)->x = rand () % TamJanela_x;
		(rer + n)->y = rand () % 360;
		(rer + n)->comp = 50;
		(rer + n)->alt = 50;
		(rer + n)->vivo = false;
		(rer + n)->texture = 0;
		(rer + n)->texture = createTexture("Textures/Bullet/recarga.png");
		
	}
	for(n = 0; n < MAX_ENEMY2; n++)
	{
		do
		{
			(enem + n)->x = rand () %  TamJanela_x ;
		}while((enem + n)->x < 100 || (enem + n)->x > 1240);
		do
		{
			(enem + n)->y = rand () % -TamJanela_y;
		}while((enem + n)->y > 0);
		
		(enem + n)->comp = 80;
		(enem + n)->alt = 80;
		(enem + n)->start = false;
		(enem + n)->vivo = false;
		(enem + n)->hits = 0;
		(enem + n)->texture = 0;
		(enem + n)->texture = createTexture("Textures/EnemiesFase.png");

		if(n < MAX_ENEMY2/3)
			(enem + n)->vel = 3;
		else if(n >= MAX_ENEMY2/3 && n < MAX_ENEMY2 - 10)
			(enem + n)->vel = 4;
		else
			(enem + n)->vel = 5;
	
	}
	
}

/*
************************************************************************************************************************************************
*/
//Texturizacao e criiaçao de um quadrado
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

/*
************************************************************************************************************************************************
*/

int Incrementa(int cont)
{
	cont++;
	return cont;
}

/*
************************************************************************************************************************************************
*/
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


	screen_menu = SDL_SetVideoMode(TamJanela_x,TamJanela_y,32,SDL_OPENGL|SDL_GL_DOUBLEBUFFER/*|SDL_FULLSCREEN*/);

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
/*
************************************************************************************************************************************************
*/
void bulletPosition (Bullet* bul, Car* c)
{
	
	bul->posY = (c->carY-c->carAlt/2);
	bul->posX = (c->carX + (c->carComp -14)/2);
}
void velocidade(Bullet* bul, int contadores)
{
	int i;
	for(i = 0; i < MAX_BALAS; i++)
	{
		if(i <= contadores)
			(bul+i)->posY -= (bul+i)->velY;
	}
}
void LimiteBala(Bullet* bul)
{
	if(bul->posX < 0 )
	{
		bul->vivo = false;
	}
	else if((bul->posX + bul->Comp) > TamJanela_x )
	{
		bul->vivo = false;
	}
	else if(bul->posY < 0)
	{
		bul->vivo = false;
	}
	else if((bul->posY + bul->Alt) > TamJanela_y )
	{
		bul->vivo = false;
	}
}
void MorteBala(Bullet* bul, Inimigos* ini)
{
	if(ColisionBulEnemy (ini, bul))
	{
		bul->vivo = false;
		ini->vivo = false;
	}
}

/*
************************************************************************************************************************************************
*/
bool LimiteEnemy2(Enemy2* enem)
{
	if(enem->vivo)
	{
		if((enem->y + enem->alt) > TamJanela_y )
		{
			return true;
		}	
	}
	return false;
}