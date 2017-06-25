#include "collisions.h"

/*
||==============================================================================================||
||				Acquila Santos Rocha - Instituto de Informática UFG								||
||																								||
||	Este arquivo impelementa as funções relativas as colisões									||
||		1. Colisão Recargas(Barreiras, Balas)													||
||		2. Colisão entre dois inimigos															||	
||		3. Colisão da nave com/sem a barreira													||
||		4. Colisao do inimigo com o carro														||
||		5. Colisão do carro e do inimigo com os limites da tela									||	
||		6. Movimentos do inimigo																||
||==============================================================================================||
*/
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

				else if((ini+aux)->colisaoX || (ini+aux)->colisaoY)
				{	
					(ini+aux)->velx = -(ini+aux)->velx;
					(ini+aux)->colisaoX = false;
					(ini+aux)->vely = -(ini+aux)->vely;
					(ini+aux)->colisaoY = false;
				}
			}
		}
	}	
}



void CarColision (Car* c, bool esq, bool dir, bool cima, bool baixo)
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

}