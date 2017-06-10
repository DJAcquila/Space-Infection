# Space-Infection
* For the game execution will be necessary some pre-settings
  - SDL1.2
     - sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
  - GLUT/OPENGL
    - sudo apt-get update
    - sudo apt-get install freeglut3 freeglut3-dev
    - sudo apt-get install libgl1-mesa-dev
    
* To compile just use this command
    - gcc -o main main.c -lSDLmain -lSDL -lGL -lSDL_ttf -lSDL_mixer -lSDL_image -lGLU -lGL -lglut -lm
* And than execute:
    - ./main
    




 By: Acquila Santos Rocha - Computer science student - 2017
