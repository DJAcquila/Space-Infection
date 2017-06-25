#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "defs.h"
#include "set.h"

/*
||==============================================================================================||
||				Acquila Santos Rocha - Instituto de Informática UFG								||
||																								||
||	Este é arquivo header as funções relativas as colisões									    ||
||		1. Colisão Recargas(Barreiras, Balas)													||
||		2. Colisão entre dois inimigos															||	
||		3. Colisão da nave com/sem a barreira													||
||		4. Colisao do inimigo com o carro														||
||		5. Colisão do carro e do inimigo com os limites da tela									||	
||		6. Movimentos do inimigo																||
||==============================================================================================||
*/

bool colisionBarreiraCar(Inimigos* iniA, Car* iniB);
bool ColisionCarBar (Barreira* ini, Car* c);
bool colision2Enemy(Inimigos* iniA, Inimigos* iniB);
bool colision2Enemy(Inimigos* iniA, Inimigos* iniB);
bool ColisionBulEnemy (Inimigos* ini, Bullet* bul);
bool ColisionRechargeCar (Recharge* rer, Car* c);
bool ColisionBulEnemy2 (Enemy2* ini, Bullet* bul);
bool ColisionCarEnemy2(Enemy2* rer,  Car*c);
bool EnemyColision(Inimigos* ini);
bool MesmaDirecao(Inimigos* iniA, Inimigos* iniB);
void EnemyMove (Inimigos* ini);
void CarColision (Car* c, bool esq, bool dir, bool cima, bool baixo);
bool ColisionEnemyCar (Inimigos* ini, Car* c);

#endif 

