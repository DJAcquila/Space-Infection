#include "set.h"

int cont = 10;

int MAX_BALAS = 500; 

int MAX_RECHARGE = 3;

int MAX_BARREIRAS = 3;

int MAX_ENEMY2 = 40; 

typedef struct game Game ;

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
void keyEvents(int(*pause_menu)(void),bool* execut, bool* baixo, bool* cima, bool* dir,bool* esq, int num_barreiras, int num_balas, int contador_balas, int contador, Car* c, Barreira* b, Bullet* bul, Mix_Chunk *bar_sound, Mix_Chunk* bul_sound)
{
	int r_menu;
	SDL_Event event;
	while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				*execut = false;
			}
			//Para Pausar o jogo com BACKSPACE
			if(event.type == SDL_KEYUP/*Tecal solta*/ && event.key.keysym.sym == SDLK_BACKSPACE)
			{
				/*Esta parte do programa realiza a troca de surfaces, do menu de pause e da tela do jogo*/
	
				r_menu = pause_menu();
				if(r_menu == 1)
				{
					*execut = false;
				}
				else if(r_menu == 0)
				{
					*execut = true;
				}
			
			}

			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_LEFT)
				{	
					*esq = true;
				}
				else if(event.key.keysym.sym == SDLK_RIGHT)
				{	
					*dir = true;
				}
				else if(event.key.keysym.sym == SDLK_UP)
				{
					*cima = true;
				}
				else if(event.key.keysym.sym == SDLK_DOWN)
				{
					*baixo = true;
				}

				if(event.key.keysym.sym == SDLK_z)
				{
					if(num_barreiras > 0)
						if(!(c->car_bar))
						{
							c->car_bar = true;
							(b + contador)->vivo = false; //quando ativar a barreira no carro, a barreira para ser coletada ficara "morta"
							Mix_PlayChannel(-1, bar_sound, 0);
						}
				}
				if(event.key.keysym.sym == SDLK_LSHIFT)
				{

					if(num_balas > 0)
					{
						Mix_PlayChannel(-1, bul_sound, 0);
						(bul + contador_balas)->balaNeles = true;
						(bul + contador_balas)->vivo = true;
					}
				}

			}

			else if(event.type == SDL_KEYUP)
			{
				if(event.key.keysym.sym == SDLK_LEFT)
				{

					*esq = false;
				}
				else if(event.key.keysym.sym == SDLK_RIGHT)
				{

					*dir = false;
				}
				else if(event.key.keysym.sym == SDLK_UP)
				{
					*cima = false;
				}
				else if(event.key.keysym.sym == SDLK_DOWN)
				{

					*baixo = false;
				}

				if(event.key.keysym.sym == SDLK_z)
				{
					if(num_barreiras > 0)
					{
						num_barreiras--;
						c->car_bar = true;

					}
				}
				if(event.key.keysym.sym == SDLK_LSHIFT)
				{
					if(num_balas > 0)
					{
						(bul+contador_balas)->balaNeles = false;

					}
				}
			}

		}
		//movimentos persoagem
		if(*esq)
		{
			c->carX -= 10;
		}
		else if (*dir)
		{
			c->carX += 10;
		}
		else if (*cima)
		{
			c->carY -= 10;
		}
		else if (*baixo)
		{
			c->carY += 10;
		}


}
void alocarMemoria(Car** c, Bullet** bul, Barreira** b, Recharge** rer, Enemy2** enem, Inimigos** ini)
{
	
	*rer = (Recharge*)malloc(MAX_RECHARGE * sizeof(Recharge));
	if(*rer == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	
	*bul = (Bullet*)malloc(MAX_BALAS*sizeof(Bullet));
	if(*bul == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	
	*ini = (Inimigos*)malloc((cont)*sizeof(Inimigos));
	if(*ini == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	
	*b = (Barreira*)malloc((MAX_BARREIRAS) * sizeof(Barreira));
	if(*b == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	
	*c = (Car*)malloc(sizeof(Car));
	if(*c == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	
	*enem = (Enemy2*)malloc(MAX_ENEMY2 * sizeof(Enemy2));
	if(*enem == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

}