#ifndef SCREEN_H
#define SCREEN_H
#include "defs.h"

void renderBitmapString (float x, float y, char *string);
GLuint createTexture(const char nome[]);
void ObjectTexture(float X, float Y, float Comp, float Alt, unsigned int texture);
void initScreen(int argc, char *args[]);

#endif