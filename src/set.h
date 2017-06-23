#ifndef SET_H
#define SET_H
#include "defs.h"
#include "screen.h"
#include "collisions.h"
extern int cont;

extern int MAX_BALAS; 

extern int MAX_RECHARGE;

extern int MAX_BARREIRAS;

extern int MAX_ENEMY2;

void preSets(Barreira* b, int qtd_barreiras, Bullet* bul, Inimigos* ini, Recharge* rer, Car* c, Enemy2* enem);
void bulletPosition (Bullet* bul, Car* c);
void velocidade(Bullet* bul, int contadores);
void LimiteBala(Bullet* bul);
void MorteBala(Bullet* bul, Inimigos* ini);
bool LimiteEnemy2(Enemy2* enem);
void keyEvents(int(*pause_menu)(void),bool* execut, bool* baixo, bool* cima, bool* dir,bool* esq, int num_barreiras, int num_balas, int contador_balas, int contador, Car* c, Barreira* b, Bullet* bul, Mix_Chunk *bar_sound, Mix_Chunk* bul_sound);
void alocarMemoria(Car** c, Bullet** bul, Barreira** b, Recharge** rer, Enemy2** enem, Inimigos** ini);
void setAll(bool esq, bool dir, bool cima, bool baixo);


#endif