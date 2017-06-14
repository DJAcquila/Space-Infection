//gcc -o main main.c -lSDLmain -lSDL -lGL -lSDL_ttf -lSDL_mixer -lSDL_image -lGLU -lGL -lglut -lm
#include "menu.h"

#define TamJanela_x  1360
#define TamJanela_y 720

Mix_Chunk *bar_sound;
Mix_Chunk *bar_explosion;
Mix_Chunk *bar_cat;
Mix_Chunk *bul_sound;
Mix_Chunk *bul_recharge;
Mix_Chunk *alarme;
Mix_Chunk *enemy2_explosion;


int main(int argc, char *args[])

{
	char nome[124];
	static int N =  400;
	printf("Informe seu nome: ");
	scanf(" %[^\n]s", nome);

	FILE *ranking;
	
	char conteudo[N];
	
	ranking = fopen("ranking.txt","a+");
	
	if(ranking == NULL)
	{
		ranking = fopen("file.txt","a");
		fputs("NOME",ranking);
		fputs("\t",ranking);
		fputs("PONTOS",ranking);
		fputs("\n",ranking);
	}

	fputs(nome,ranking);
	fputs("\t",ranking);
	fread(&conteudo, sizeof(char), N,ranking);
	initScreen(argc,args);


	struct timeval inicio, final;
	int tmili;
   	gettimeofday(&inicio, NULL);

   	bar_sound = Mix_LoadWAV("Sound/PegarBarreira.ogg");
    bar_explosion = Mix_LoadWAV("Sound/barExplode.ogg");
   	bar_cat = Mix_LoadWAV("Sound/BarrierCat.ogg");
   	bul_sound = Mix_LoadWAV("Sound/plasma.ogg");
   	bul_recharge = Mix_LoadWAV("Sound/BalaRecarga.ogg");
   	alarme = Mix_LoadWAV("Sound/alarme.ogg");
   	enemy2_explosion = Mix_LoadWAV("Sound/Explosion.ogg");

	bool execut = true;

	int n;

	int r_menu = main_menu();
	if(r_menu == 1)
	{
		execut = false;
	}
	else if(r_menu == 0)
	{
		execut = true;
	}
	Recharge* rer;
	rer = (Recharge*)malloc(MAX_RECHARGE * sizeof(Recharge));

	if(rer == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	Bullet* bul;
	bul = (Bullet*)malloc(MAX_BALAS*sizeof(Bullet));

	if(bul == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	Inimigos* ini;
	ini = (Inimigos*)malloc((cont)*sizeof(Inimigos));
	if(ini == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	Barreira* b;
	b = (Barreira*)malloc((MAX_BARREIRAS) * sizeof(Barreira));

	if(b == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	Car* c;
	c = (Car*)malloc(sizeof(Car));

	if(c == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	Enemy2* enem;
	enem = (Enemy2*)malloc(MAX_ENEMY2 * sizeof(Enemy2));
	if(enem == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}

	int num_barreiras;

	SDL_Event event;

 	num_barreiras = 0; //Quantidade inicial de barreiras

	preSets(b, num_barreiras, bul, ini, rer, c, enem);

	bool esq = false, dir = false;
	bool baixo = false, cima = false;

	//Teturas
	unsigned int enemy_texture = 0;
	enemy_texture = createTexture("Textures/virus.png");
	unsigned int car_texture = 0;
	car_texture = createTexture("Textures/nave.png");
	unsigned int bar_texture = 0;
	bar_texture = createTexture("Textures/barreira.png");
	unsigned int car_bar_texture = 0;
	car_bar_texture = createTexture("Textures/Navebarreira.png");
	unsigned int back_texture = 0;
	back_texture = createTexture("Textures/space.png");

	unsigned int textureUp = 0;
	textureUp = createTexture("Textures/Bullet/bulletUp.png");

	//Contadores
	int contador = 0;
	int dead_enemies = 0;
	int points = 0;
	int contador_balas = 0;
	int num_balas = 0;
	int contador_recargas = 0;
	int contador_inimigos2 = 0;
	int dead_enemies2 = 0;
	int marcador = 1;

	c->car_bar = true;

	char pontos[20];
	while(execut)
	{


		float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		//Para contar o tempo decorrido

		gettimeofday(&final, NULL);
   		tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);

		char MensagemPontos[20];

    	sprintf(MensagemPontos, "Pontos : %2d", points);
		/*Transforma os pontos inteiros em string para inserir nos arquivos*/
    	sprintf(pontos,"%2d",points);
    	char MensagemBarreiras[20];
    	sprintf(MensagemBarreiras,"Barreiras : %2d", num_barreiras);
    	char MensagemBalas[20];
    	sprintf(MensagemBalas,"Balas : %2d", num_balas);

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				execut = false;
			}
			//Para Pausar o jogo com BACKSPACE
			if(event.type == SDL_KEYUP/*Tecal solta*/ && event.key.keysym.sym == SDLK_BACKSPACE)
			{
				/*Esta parte do programa realiza a troca de surfaces, do menu de pause e da tela do jogo*/
	
				r_menu = pause_menu();
				if(r_menu == 1)
				{
					execut = false;
				}
				else if(r_menu == 0)
				{
					execut = true;
				}
			
			}

			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_LEFT)
				{
					(bul + contador_balas)->tecla_atual = 3;
					esq = true;
				}
				else if(event.key.keysym.sym == SDLK_RIGHT)
				{
					(bul + contador_balas)->tecla_atual = 4;
					dir = true;
				}
				else if(event.key.keysym.sym == SDLK_UP)
				{
					(bul + contador_balas)->tecla_atual = 1;
					cima = true;
				}
				else if(event.key.keysym.sym == SDLK_DOWN)
				{
					(bul + contador_balas)->tecla_atual = 2;
					baixo = true;
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

					esq = false;
				}
				else if(event.key.keysym.sym == SDLK_RIGHT)
				{

					dir = false;
				}
				else if(event.key.keysym.sym == SDLK_UP)
				{
					cima = false;
				}
				else if(event.key.keysym.sym == SDLK_DOWN)
				{

					baixo = false;
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


		velocidade(bul,contador_balas);

		if((bul+contador_balas)->balaNeles)
		{
			bulletPosition((bul+contador_balas),c);
			contador_balas++;
			if(num_balas > 0)
				num_balas--;

		}

		LimiteBala(bul+contador_balas);



		//movimentos persoagem
		if(esq)
		{
			c->carX -= 10;
		}
		else if (dir)
		{
			c->carX += 10;
		}
		else if (cima)
		{
			c->carY -= 10;
		}
		else if (baixo)
		{
			c->carY += 10;
		}


		CarColision(c,event,esq,dir,cima,baixo);
		//movimentos do inimigo (Colisoes, movimento automatico)...
		EnemyMove(ini);
		//Nao esta pegando o personagem
 		int n;
		glClear(GL_COLOR_BUFFER_BIT);
		//Iniciar matriz
		glPushMatrix();

		//Matriz de desenho

		glOrtho(0, TamJanela_x, TamJanela_y, 0, -1, 1);/*Neste caso eh toda a regiao da janela*/

		ObjectTexture(0, 0, TamJanela_x, TamJanela_y, back_texture);//Texturizacao do plano de fundo

		int pera;


		int j;
		//Colisao das balas com os inimigos

		int k;
		for(pera = 0; pera < MAX_ENEMY2; pera++)
		{
			if((enem + pera)->vivo)
			{

				if(pera <= contador_inimigos2)
				{
					(enem + pera)->y += (enem + pera)->vel;

					ObjectTexture((enem+pera)->x, (enem+pera)->y, (enem+pera)->comp, (enem+pera)->alt, (enem + pera)->texture);
				}

			}
		}

		for(j = 0; j < MAX_BALAS; j++)
		{
			for(n = 0; n < cont; n++)
			{
				if(j < contador_balas)
				{
					if(ColisionBulEnemy (ini + n, bul + j))
					{
						Mix_PlayChannel(-1, bar_explosion, 0);
						points++;
						dead_enemies++;
						(ini+n)->vivo = true;
						(bul+j)->vivo = false;
						(ini+n)->inimigoX = -(ini+n)->inimigoX;
						(ini+n)->inimigoY = -(ini+n)->inimigoY;
						(bul+j)->velY = -20*(bul+j)->velY;
					}

				}
			}

			for(k = 0; k < MAX_ENEMY2; k++)
				if(j < contador_balas)
				{
					if((enem + k)->start)
					{
						if((enem + k)->vivo)
						{
							if(ColisionBulEnemy2 (enem + k, bul + j))
							{
								points += 2;
								(enem + k)->hits ++;
								(bul+j)->vivo = false;
								(bul+j)->velY = -20*(bul+j)->velY;

								if((enem + k)->hits == 4 )
								{
									Mix_PlayChannel(-1, enemy2_explosion, 0);
									dead_enemies2 ++;
									(enem + k)->vivo = false;
									(enem + k)->x = - 1300;
								}
							}

							if((enem + k)->hits == 1)
							{
								if(k < MAX_ENEMY2)
								{
									(enem + k + 1)->vivo = true;
									contador_inimigos2 ++;
								}
							}
							else if(ColisionCarEnemy2(enem + k, c) || LimiteEnemy2(enem + k))
							{
								execut = false;
							}
						}
					}
				}
		}


		//Colisao da barreira com os inimigos
		for(n = 0; n < (cont); n++)
 		{
 			if( ColisionEnemyCar((ini+n),c))
			{
				if(!(c->car_bar)) //se nao esta com a barreira
				{
					execut = false;
				}
				else // caso estiver com a barreira...
				{
					Mix_PlayChannel(-1, bar_explosion, 0); //Som da explosao da barreira

					points++;
					dead_enemies++;
					(ini+n)->vivo = true;
					(b+contador)->vivo =  true;
					c->car_bar = false;
					(ini+n)->inimigoX = -(ini+n)->inimigoX;
					(ini+n)->inimigoY = -(ini+n)->inimigoY;

				}

			}
		}

		if(marcador == 1)
		{
			if(dead_enemies == cont) //FIM DO JOGO
			{
				Mix_PlayChannel(-1, alarme, 0);
				marcador = 0;
				num_balas += 350;
				(enem)->vivo = true;
				for (pera = 0; pera < MAX_ENEMY2; pera++)
				{
					(enem + pera)->start = true;
				}

			}
		}
		if(dead_enemies2 == MAX_ENEMY2)
		{
			execut = false;
		}


		if(c->car_bar)
		{
			renderBitmapString(550, 20, "Barreira sendo usada"); // Identifica se a barreira esta sendo usada
		}

		renderBitmapString(1238, 20, MensagemBarreiras);

		renderBitmapString(1100, 20, MensagemBalas);

		renderBitmapString(1, 20, MensagemPontos);




		//So ira aparecer a barreira quando a barreira na estiver ativada na nave
		switch (contador)
		{
			case 0:
				if((tmili*0.001 >= 15 && tmili*0.001 <= 30))
				{
					(b+contador)->vivo = true;
					if((b+contador)->vivo = true)
						ObjectTexture((b+contador)->barreiraX, (b+contador)->barreiraY, (b+contador)->barreiraCA, (b+contador)->barreiraCA, bar_texture); //Texturizaçao da barreira
				}
				else
					(b+contador)->vivo = false;
				break;

			case 1:
				if(tmili*0.001 >= 45 && tmili*0.001 <= 65)
				{
					(b+contador)->vivo = true;
					if((b+contador)->vivo = true)
						ObjectTexture((b+contador)->barreiraX, (b+contador)->barreiraY, (b+contador)->barreiraCA, (b+contador)->barreiraCA, bar_texture); //Texturizaçao da barreira
				}
				else
					(b+contador)->vivo = false;
				break;
			case 2:
				if(tmili*0.001 >= 100 && tmili*0.001 <= 120)
				{
					(b+contador)->vivo = true;
					if((b+contador)->vivo = true)
						ObjectTexture((b+contador)->barreiraX, (b+contador)->barreiraY, (b+contador)->barreiraCA, (b+contador)->barreiraCA, bar_texture); //Texturizaçao da barreira
				}
				else
					(b+contador)->vivo = false;
				break;

		}

		//Se a barreira estiver "viva", o carro ira colidir com a barreira (pegar a barreira)
		if((b+contador)->vivo)
		{
			if(contador < MAX_BARREIRAS)
				if(ColisionCarBar ((b + contador),c))
				{
					Mix_PlayChannel(-1, bar_cat, 0);

					contador++;
					num_barreiras++;
				}
		}


		//Carro sem textura da barreira
		if(!(c->car_bar))
		{
			ObjectTexture(c->carX, c->carY, c->carComp, c->carAlt, car_texture);//Texturizaçao do carro sem a barreira
		}


		//Carro com textura da barreira

		else
		{
			ObjectTexture(c->carX, c->carY, c->carComp, c->carAlt, car_bar_texture);//Texturizaçao do carro com a barreira
		}


		switch (contador_recargas)
		{
			case 0:
				if(tmili*0.001 > 10 && tmili*0.001 <= 20)
				{
					(rer+contador_recargas)->vivo =  true;
					if((rer+contador_recargas)->vivo)
						ObjectTexture((rer+contador_recargas)->x, (rer+contador_recargas)->y, (rer+contador_recargas)->comp, (rer+contador_recargas)->alt, (rer+contador_recargas)->texture);
				}
				else
					(rer+contador_recargas)->vivo =  false;
				break;

			case 1:
				if(tmili*0.001 > 30 && tmili*0.001 <= 40)
				{
					(rer+contador_recargas)->vivo =  true;
					if((rer+contador_recargas)->vivo)
						ObjectTexture((rer+contador_recargas)->x, (rer+contador_recargas)->y, (rer+contador_recargas)->comp, (rer+contador_recargas)->alt, (rer+contador_recargas)->texture);
				}
				else
					(rer+contador_recargas)->vivo =  false;
				break;
			case 2:
				if(tmili*0.001 > 40 && tmili*0.001 <= 50)
				{
					(rer+contador_recargas)->vivo =  true;
					if((rer+contador_recargas)->vivo)
						ObjectTexture((rer+contador_recargas)->x, (rer+contador_recargas)->y, (rer+contador_recargas)->comp, (rer+contador_recargas)->alt, (rer+contador_recargas)->texture);
				}
				else
					(rer+contador_recargas)->vivo =  false;
				break;
		}



		if((rer+contador_recargas)->vivo)
			if(contador_recargas < MAX_RECHARGE)
				if(ColisionRechargeCar (rer + contador_recargas, c))
				{
					Mix_PlayChannel(-1,bul_recharge,0);
					(rer+contador_recargas)->vivo = false;
					switch (contador_recargas)
					{
						case 0:
							num_balas += -dead_enemies + cont ;
							break;
						case 1:
							num_balas += -dead_enemies + cont ;
							break;
						case 2:
							num_balas += dead_enemies + cont;
							break;

					}
					(rer + contador_recargas)->x = TamJanela_x + 50;
					(rer + contador_recargas)->y = TamJanela_y + 50;
					contador_recargas++;
				}


		for(n = 0; n < cont ; n++)
		{
			if((ini+n)->vivo)
			{
				ObjectTexture((ini+n)->inimigoX, (ini+n)->inimigoY, (ini+n)->inimigoCA, (ini+n)->inimigoCA, enemy_texture);//Texturizacao do inimigo
			}
		}


		for(pera = 0; pera < MAX_BALAS; pera++)
		{
			if((bul + pera)->vivo)
			{
				if(pera < contador_balas)
				{
					ObjectTexture((bul+pera)->posX, (bul+pera)->posY, (bul+pera)->Comp, (bul+pera)->Alt, textureUp);
				}
			}
		}






		//glDisable(GL_TEXTURE_2D);

		//Fechar a matriz
		glPopMatrix();

		SDL_GL_SwapBuffers();


	}

	free(b);
	free(c);
	free(ini);
	free(bul);
	free(enem);
	free(rer);
	Mix_FreeChunk(bar_sound);
	Mix_FreeChunk(bar_explosion);
	Mix_FreeChunk(bar_cat);
	Mix_FreeChunk(bul_recharge);
	Mix_FreeChunk(alarme);
	Mix_FreeChunk(enemy2_explosion);
	Mix_FreeChunk(bul_sound);

	fputs(pontos,ranking);
	fputs("\n",ranking);
	
	fread(&conteudo, sizeof(char), N,ranking);
	printf("%s",conteudo);

	//Sistema de Ranqueamento aqui
	/*
		*
		*
		*
		*
		*
	*/



}
