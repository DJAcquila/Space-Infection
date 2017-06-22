OUT = SpaceInfection
CXX = gcc
FLAGS = -lSDLmain -lSDL -lGL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_image -lGLU -lGL -lglut -lm

OBJECTS = main.o collisions.o screen.o set.o menu.o

all:	$(OUT)
$(OUT):	$(OBJECTS)
	$(CXX) -o $@ $^ ${FLAGS}

$(OBJECTS):	defs.h
clean:
	rm *.o
