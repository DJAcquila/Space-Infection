# Space-Infection
* Para a execução deste Jogo serão necessários alguns pré-requisitos
  - SDL1.2
     - sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
  - GLUT/OPENGL
    - sudo apt-get update
    - sudo apt-get install freeglut3 freeglut3-dev
    - sudo apt-get install libgl1-mesa-dev
    
* Para compilar, basta utilizar este comando
    - gcc -o main main.c -lSDLmain -lSDL -lGL -lSDL_ttf -lSDL_mixer -lSDL_image -lGLU -lGL -lglut -lm
* E assim executar com:
    - ./main
