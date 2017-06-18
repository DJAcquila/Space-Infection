#ifndef MENU_H
#define MENU_H

#include "defs.h"
#include "screen.h"
#include "collisions.h"
#include "set.h"
extern Mix_Chunk *menu_select;
extern Mix_Chunk *menu_move;

int main_menu (void);
int pause_menu (void);

#endif //MENU_H