#include "rank.h"
void abrir_arquivo()
{
    ranking = fopen("ranking.txt","a+b");
}
/*void realocar()
{
    u = (User*)realloc(u, ++contador_usuarios);
}*/
void cadastro()
{ 
    char nome[64];
    int senha[64];
    printf("Informe o nome de usuário prara cadastro\n");
    scanf(" %[^\n]s", nome);
    printf("Informe a senha desejada\n");
    scanf(" %[^\n]s", senha);
    while(buscar(nome) == 1)
    {
        printf("Usuário ja cadastrado\n");
        printf("Informe o nome de usuário prara cadastro\n");
        scanf(" %[^\n]s", nome);
        printf("Informe a senha desejada\n");
        scanf(" %[^\n]s", senha);
    }
    printf("Usuário cadastrado\n");
    strcpy(u.nome, nome);
    strcpy(u.senha, senha);
    rewind(ranking);
    fwrite(&u, sizeof(User), 1, ranking);
}
int buscar(char nome[])
{
    rewind(ranking);
    while(fread(&u, sizeof(User), 1, ranking) == 1)
    {
        if(strcmp(nome, u.nome) == 0)
        {
            return 1;
        }
    }
    return 0;
    
}
int mensagem1()
{
    int op;
    printf("Selecione uma opção\n");
    printf("(1) Cadastro\n");
    printf("(2) Login\n");
    do{
        scanf("%d",&op);
    }while(op != 1 && op != 2);
    return op;
}
void mensagem(User u)
{
    
    printf("Informe o nome de usuário\n");
    scanf(" %[^\n]s", u.nome);
   
}
int mostrar_logado()
{
    int op;
    printf("Selecione uma opção\n");
    printf("(1) Verificar pontuação\n");
    printf("(2) Jogar\n");
    do{
        scanf("%d",&op);
    }while(op != 1 && op != 2);
    return op;
}
void show(char nome[])
{
    rewind(ranking);
    while(fread(&u, sizeof(User), 1, ranking) == 1)
    {
        if(strcmp(nome, u.nome) == 0)
        {
            printf("Usuário: %s\n",u.nome);
            printf("Última pontuação: %d\n",u.points);  
        }
        
    }
}
int login()
{
    char nome[125];
    int senha;
    printf("Informe o nome de usuário\n");
    scanf(" %[^\n]s",nome);
    printf("Informe a senha do usuario\n");
    scanf(" %[^\n]s", senha);
    buscar(nome);
    if(buscar(nome) == 1)
    {
        printf("Logado no sistema\n");
        int aux = mostrar_logado();
        if(aux == 1)
        {
            show(nome);
        }

        return 1;
    }
    else
    {
        printf("Usuário não cadastrado\n");
        cadastro();
        return 0;
    }
}

