#ifndef PROFILE_H
#define PROFILE_H

#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

typedef struct
{
    char email[50];
    char nome[50];
    char sobrenome[100];
    char residencia[100];
    char formacaoacademica[100];
    int anodeformatura;
    char habilidades[10][50];
    char imagem_caminho[100];
} perfil;

#endif
