#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "defs.h"
#include "set.h"

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

#endif 

