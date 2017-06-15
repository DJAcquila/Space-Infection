#include "funcoes.h"
Mix_Chunk *menu_select = NULL;
Mix_Chunk *menu_move = NULL;

int main_menu ()
{


	bool execut = true; // Variavel auxiliar que define o processo de execuçao do loop principal

	

	int i;

	Menu men;
	Algarismos alg[2];

	menu_select = Mix_LoadWAV("Sound/MenuSelect.ogg");
	menu_move = Mix_LoadWAV("Sound/MenuMove.ogg");
	
	//Creditos para a musica de fundo
	
	for(i = 0; i < 3; i++)
	{
		men.op[i].X = 550;
		men.op[i].Comp = 332;
		men.op[i].Alt = 104;
	}
	//Coordenadas no eixo Y das opcoes do menu
	men.op[0].Y = 300;

	men.op[1].Y = 400;

	men.op[2].Y = 500;


	//Definicao das propriedades dos algarismos
	alg[0].X = 560;
	alg[1].X = alg[0].X + 50;
	alg[0].Comp = alg[1].Comp = 250;
	alg[0].Alt = alg[1].Alt = 80;
	alg[0].Y = alg[1].Y = 600;

	
	men.op[0].texture_uns = 0;
	men.op[0].texture_uns = createTexture("Textures/start.png");
	
	
	men.op[0].texture_sel = 0;
	men.op[0].texture_sel = createTexture("Textures/startazul.png");

	men.op[1].texture_uns = 0;
	men.op[1].texture_uns = createTexture("Textures/Exit.png");
	
	
	men.op[1].texture_sel = 0;
	men.op[1].texture_sel = createTexture("Textures/Exitazul.png");

	men.op[2].texture_uns = 0;
	men.op[2].texture_uns = createTexture("Textures/EnemiesNoSelected.png"); // Textura do inimigo nao selecionada

	men.op[2].texture_sel = 0;
	men.op[2].texture_sel = createTexture("Textures/EnemiesSelected.png"); //Textura do inimigo selecionada

	unsigned int right_texture_sel = 0;
	right_texture_sel = createTexture("Textures/EnemiesSelectedRight.png"); //Tecla para direita

	unsigned int left_texture_sel = 0;
	left_texture_sel = createTexture("Textures/EnemiesSelectedLeft.png"); //Tecla para esquerda

	unsigned int back_texture = 0;
	back_texture = createTexture("Textures/space.png"); //Textura do fundo

	unsigned int title_texture = 0;
	title_texture = createTexture("Textures/Title.png"); //Textura do titulo

	//Definicao das texturas dos algarismos

	unsigned int zero = 0;
	zero = createTexture("Textures/Algarism/zero.png"); 

	unsigned int um = 0;
	um = createTexture("Textures/Algarism/um.png");

	unsigned int dois = 0;
	dois = createTexture("Textures/Algarism/dois.png");

	unsigned int tres = 0;
	tres = createTexture("Textures/Algarism/tres.png");

	unsigned int quatro = 0;
	quatro = createTexture("Textures/Algarism/quatro.png");

	unsigned int cinco = 0;
	cinco = createTexture("Textures/Algarism/cinco.png");

	unsigned int seis = 0;
	seis = createTexture("Textures/Algarism/seis.png");

	unsigned int sete = 0;
	sete = createTexture("Textures/Algarism/sete.png");

	unsigned int oito = 0;
	oito = createTexture("Textures/Algarism/oito.png");

	unsigned int nove = 0;
	nove = createTexture("Textures/Algarism/nove.png");


	SDL_Event event;
	int contador = 0;
	int value;
	
	i = 0;

	men.op[0].flagSel = true;
	men.op[1].flagSel = false;
	men.op[2].flagSel = false;
	
	int contador_menu;

	bool direita = false;
	bool esquerda = false; 

	int j;
	bool flag;

	//Inicia execucao no menu
	while (execut)
	{
		//Vai definir o numero de inimigos (Transforma o numero em string, para ser identificada, pela funao creatTexture());
		char text[20];
    	sprintf(text, "%2d", cont);

    	//Eventos do teclado
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						//Logica para a mudanca nas texturas a medida que passa pelas opcoes do menu
						case SDLK_DOWN:
							if(i < 2)
							{
								Mix_PlayChannel(-1, menu_move, 0);
								i++;
								if(men.op[i-1].flagSel)
								{

									men.op[i-1].flagSel = false;
									men.op[i].flagSel = true;
								}
							}
						break;


						case SDLK_UP:
							if(i > 0)
							{
								Mix_PlayChannel(-1, menu_move, 0);
								i--;
								if(men.op[i+1].flagSel)
								{
									men.op[i+1].flagSel = false;
									men.op[i].flagSel = true; 
								}
							}
							
							break;

							case SDLK_RETURN:
								Mix_PlayChannel(-1, menu_select, 0);
								if(i != 2)
									return i;
								break;
							
					}
					//Caso estiver com a selecao da quantidade de inimigos selecionada...
					if(men.op[2].flagSel)
						{
							//Ativar o uso dos direcionais: esquerda e direita
							switch(event.key.keysym.sym)
							{
								case SDLK_RIGHT:
									Mix_PlayChannel(-1, menu_move, 0);
									direita = true;
									if(cont < 30)
										cont++;
									break;
								case SDLK_LEFT:
									Mix_PlayChannel(-1, menu_move, 0);
									esquerda = true;
									if(cont >= 11)
										cont--;		
									break;
							}
						}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{
						case SDLK_RIGHT:
						
							direita = false;
							break;
						case SDLK_LEFT:
						
							esquerda = false;
							break;
					}
			}


		}

		glClear(GL_COLOR_BUFFER_BIT);
 		
		//Iniciar matriz
		glPushMatrix();

		glOrtho(0, TamJanela_x, TamJanela_y, 0, -1, 1);
		
		//Textura do fundo
		glColor4ub(255, 255, 255, 255);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, back_texture);
		glBegin(GL_QUADS);
				glTexCoord2d(0,0);	glVertex2f(0, 0);
				glTexCoord2d(1,0);	glVertex2f(TamJanela_x, 0);
				glTexCoord2d(1,1);	glVertex2f(TamJanela_x, TamJanela_y);
				glTexCoord2d(0,1);	glVertex2f(0, TamJanela_y);
		glEnd();
		
		//Textura para o titulo
		ObjectTexture(290, 50, 806, 196, title_texture);

					
		//MUdancas de texturas do menu (selecionado ou nao selecionado)
		for(contador_menu = 0; contador_menu < 3; contador_menu++)
		{
			if(!men.op[contador_menu].flagSel)
			{	
				ObjectTexture(men.op[contador_menu].X, men.op[contador_menu].Y, men.op[contador_menu].Comp, men.op[contador_menu].Alt, men.op[contador_menu].texture_uns);
			}
			else
			{
				ObjectTexture(men.op[contador_menu].X, men.op[contador_menu].Y, men.op[contador_menu].Comp, men.op[contador_menu].Alt, men.op[contador_menu].texture_sel);
				
				if(contador_menu == 2)
				{
					if(direita)
						ObjectTexture(men.op[contador_menu].X, men.op[contador_menu].Y, men.op[contador_menu].Comp, men.op[contador_menu].Alt, right_texture_sel);
					
					else if(esquerda)
						ObjectTexture(men.op[contador_menu].X, men.op[contador_menu].Y, men.op[contador_menu].Comp, men.op[contador_menu].Alt, left_texture_sel);
				}
			}
		}
		//LOgica de texturizacao dos algarismos da quantidade de inimigos

		alg[0].parte = cont / 10;
		alg[1].parte = cont % 10;
		
		for(j = 0; j < 2; j++)
		{
			if(j == 0)
			{
				if(alg[j].parte != 0)
				{
					flag = true;
					alg[j].text = 0;
					switch(alg[j].parte)
					{
						case 0:
							alg[j].text = zero; 
							break;
						case 1:
							alg[j].text = um;
							break; 
						case 2:
							alg[j].text = dois; 
							break;
						case 3:
							alg[j].text = tres; 
							break;
						case 4:
							alg[j].text = quatro; 
							break;
						case 5:
							alg[j].text = cinco; 
							break;
						case 6:
							alg[j].text = seis; 
							break;
						case 7:
							alg[j].text = sete; 
							break;
						case 8:
							alg[j].text = oito; 
							break;
						case 9:
							alg[j].text = nove;
							break; 
					}
				}
				else flag = false;

			}
			else
			{		
				alg[j].text = 0;
				switch(alg[j].parte)
				{
					case 0:
						alg[j].text = zero; 
						break;
					case 1:
						alg[j].text = um;
						break; 
					case 2:
						alg[j].text = dois; 
						break;
					case 3:
						alg[j].text = tres; 
						break;
					case 4:
						alg[j].text = quatro; 
						break;
					case 5:
						alg[j].text = cinco; 
						break;
					case 6:
						alg[j].text = seis; 
						break;
					case 7:
						alg[j].text = sete; 
						break;
					case 8:
						alg[j].text = oito; 
						break;
					case 9:
						alg[j].text = nove;
						break; 
				}
			}
		}

		for(j = 0; j < 2; j++)
		{
			if(j == 0)
			{
				if(flag)
					ObjectTexture(alg[j].X, alg[j].Y, alg[j].Comp, alg[j].Alt, alg[j].text);
			}
			else
				ObjectTexture(alg[j].X, alg[j].Y, alg[j].Comp, alg[j].Alt, alg[j].text);
			
		}


		glPopMatrix();

		SDL_GL_SwapBuffers();
		
	}

	return 0;
}

//Menu de pausa do jogo 
	//A unca diferenca para o menu principal eh a ausencia da selecao da quantidade de inimigos
int pause_menu ()
{


	bool execut = true; // Variavel auxiliar que define o processo de execuçao do loop principal

	
	int i;

	Menu men;

	menu_select = Mix_LoadWAV("Sound/MenuSelect.ogg");
	menu_move = Mix_LoadWAV("Sound/MenuMove.ogg");

	for(i = 0; i < 2; i++)
	{
		men.op[i].X = 550;
		men.op[i].Comp = 332;
		men.op[i].Alt = 104;
	}
	//Coordenadas no eixo Y das opcoes do menu
	men.op[0].Y = 300;

	men.op[1].Y = 400;
	
	men.op[0].texture_uns = 0;
	men.op[0].texture_uns = createTexture("Textures/start.png");
	
	
	men.op[0].texture_sel = 0;
	men.op[0].texture_sel = createTexture("Textures/startazul.png");

	men.op[1].texture_uns = 0;
	men.op[1].texture_uns = createTexture("Textures/Exit.png");
	
	
	men.op[1].texture_sel = 0;
	men.op[1].texture_sel = createTexture("Textures/Exitazul.png");

	
	unsigned int right_texture_sel = 0;
	right_texture_sel = createTexture("Textures/EnemiesSelectedRight.png"); //Tecla para direita

	unsigned int left_texture_sel = 0;
	left_texture_sel = createTexture("Textures/EnemiesSelectedLeft.png"); //Tecla para esquerda

	unsigned int back_texture = 0;
	back_texture = createTexture("Textures/space.png"); //Textura do fundo

	unsigned int title_texture = 0;
	title_texture = createTexture("Textures/Title.png"); //Textura do titulo


	SDL_Event event;
	int contador = 0;
	int value;
	
	i = 0;

	men.op[0].flagSel = true;
	men.op[1].flagSel = false;
	men.op[2].flagSel = false;
	
	int contador_menu;

	bool direita = false;
	bool esquerda = false; 

	int j;
	bool flag;
	while (execut)
	{
		char text[20];
    	sprintf(text, "%2d", cont);

		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_DOWN:
							if(i == 0)
							{
								Mix_PlayChannel(-1, menu_move, 0);
								i++;
								if(men.op[i-1].flagSel)
								{

									men.op[i-1].flagSel = false;
									men.op[i].flagSel = true;
								}
							}
						break;


						case SDLK_UP:
							if(i == 1)
							{
								Mix_PlayChannel(-1, menu_move, 0);
								i--;
								if(men.op[i+1].flagSel)
								{
									men.op[i+1].flagSel = false;
									men.op[i].flagSel = true; 
								}
							}
							
							break;

							case SDLK_RETURN:
								Mix_PlayChannel(-1, menu_select, 0);
								return i;
								break;
						break;
					}
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT);
 		
		//Iniciar matriz
		glPushMatrix();

		glOrtho(0, TamJanela_x, TamJanela_y, 0, -1, 1);
		glColor4ub(255, 255, 255, 255);
	
		glEnable(GL_TEXTURE_2D);
		
		glBindTexture(GL_TEXTURE_2D, back_texture);
		
		glBegin(GL_QUADS);
				glTexCoord2d(0,0);	glVertex2f(0, 0);
				glTexCoord2d(1,0);	glVertex2f(TamJanela_x, 0);
				glTexCoord2d(1,1);	glVertex2f(TamJanela_x, TamJanela_y);
				glTexCoord2d(0,1);	glVertex2f(0, TamJanela_y);
		glEnd();
		
		ObjectTexture(290, 50, 806, 196, title_texture);

		

		for(contador_menu = 0; contador_menu < 2; contador_menu++)
		{
			if(!men.op[contador_menu].flagSel)
			{	
				ObjectTexture(men.op[contador_menu].X, men.op[contador_menu].Y, men.op[contador_menu].Comp, men.op[contador_menu].Alt, men.op[contador_menu].texture_uns);
			}
			else
			{
				ObjectTexture(men.op[contador_menu].X, men.op[contador_menu].Y, men.op[contador_menu].Comp, men.op[contador_menu].Alt, men.op[contador_menu].texture_sel);
				
			}
		}

		

		glPopMatrix();

		SDL_GL_SwapBuffers();
		
	}

	return 0;
}