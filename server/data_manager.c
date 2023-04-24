#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <json-c/json.h>
#include "../model/profile.h"
#include <json-c/json.h>

#define FILENAME "../json/perfil.json"
#define MAX_LEN_RCV 100

void receive_message(int socket, char* message){

    while(1){
        int received = recv(socket, message, MAX_LEN_RCV-1, 0); //receive msg

        if (received == -1) {
            perror("Error receiving");
            return;
        }
        else if (received > MAX_LEN_RCV - 1){ //if overflow max defined
            perror("Error word is too long");
            return;
        }
        else if (received >= 0){ //ok
            message[received] = '\0';
            printf("Received: %s\n", message);
            return;
        }
    }
}

void send_message(int socket, char* message){

    if (strlen(message) > MAX_LEN_RCV - 1){
        perror("String is too big");
        return;
    }

    while(1){
        int sent = send(socket, message, strlen(message), 0);
        if (sent == -1) {
            perror("Error receiving email");
            return;
        }
        else if (sent >= 0){
            return;
        }
    }
}

//preenche a struct profile com dados do cliente
void fill_profile(int socket, perfil* profile){

    char email[50], nome[50], sobrenome[100], residencia[100], formacaoacademica[100], habilidades[510], anodeformatura[5];

    //email
    send_message(socket, "Insert email: \n");
    receive_message(socket, email);

    //name
    send_message(socket, "Insert name: \n");
    receive_message(socket, nome);

    //sobrenome
    send_message(socket, "Insert last name: \n");
    receive_message(socket, sobrenome);

    //residencia
    send_message(socket, "Insert residence: \n");
    receive_message(socket, residencia);

    //formacaoacademica
    send_message(socket, "Insert academic formation: \n");
    receive_message(socket, formacaoacademica);

    //habilidades
    send_message(socket, "Insert skills separated by comma (skill1,skill2...): \n");
    receive_message(socket, habilidades);

    //anodeformatura
    send_message(socket, "Insert graduation year: \n");
    receive_message(socket, anodeformatura);

    // copiar valores para a struct perfil
    strcpy(profile->email, email);
    strcpy(profile->nome, nome);
    strcpy(profile->sobrenome, sobrenome);
    strcpy(profile->residencia, residencia);
    strcpy(profile->formacaoacademica, formacaoacademica);
    strcpy(profile->habilidades[0], strtok(habilidades, ","));

    for (int i = 1; i < 10; i++){
        char* token = strtok(NULL, ",");
        if (token != NULL){
            strcpy(profile->habilidades[i], token);
        }
        else {
            strcpy(profile->habilidades[i], "");
        }
    }
    profile->anodeformatura = atoi(anodeformatura);
    return;
}

//==================FUNCTIONS TO BE PERFORMED BY THE SERVER==================

// cadastrar um novo perfil utilizando o email como identificador;
int create_profile(perfil *profile){

    if (profile == NULL)
    {
        printf("Error: profile is NULL!\n");

        return 1;
    }

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");

        return 1;
    }

    json_object *profiles = json_object_from_file(FILENAME);
    if (profiles == NULL)
    {
        printf("Error reading file!\n");
        fclose(file);

        return 1;
    }

    // print the profiles

    profiles = json_object_object_get(profiles, "profiles");

    int n_profiles = json_object_array_length(profiles);

    for (int i = 0; i < n_profiles; i++)
    {
        json_object *p = json_object_array_get_idx(profiles, i);
        json_object *email = json_object_object_get(p, "email");

        if (strcmp(json_object_get_string(email), profile->email) == 0)
        {
            printf("Error: email already exists!\n");
            fclose(file);
            json_object_put(profiles);

            return 1;
        }
    }

    json_object *new_profile = json_object_new_object();

    json_object_object_add(new_profile, "email", json_object_new_string(profile->email));
    json_object_object_add(new_profile, "nome", json_object_new_string(profile->nome));
    json_object_object_add(new_profile, "sobrenome", json_object_new_string(profile->sobrenome));
    json_object_object_add(new_profile, "residencia", json_object_new_string(profile->residencia));
    json_object_object_add(new_profile, "formacao_academica", json_object_new_string(profile->formacaoacademica));
    json_object_object_add(new_profile, "ano_de_formatura", json_object_new_int(profile->anodeformatura));

    json_object *habilidades_array = json_object_new_array();
    for (int i = 0; i < 10; i++)
    {
        json_object_array_add(habilidades_array, json_object_new_string(profile->habilidades[i]));
    }
    json_object_object_add(new_profile, "habilidades", habilidades_array);

    json_object_array_add(profiles, new_profile);

    // print the profiles

    json_object *new_profiles = json_object_new_object();

    json_object_object_add(new_profiles, "profiles", profiles);

    if (json_object_to_file(FILENAME, new_profiles) == -1)
    {
        printf("Error writing to file!\n");
        fclose(file);
        json_object_put(new_profiles);

        return 1;
    }

    fclose(file);

    printf("Profile created successfully with the email: %s\n", profile->email);

    return 0;
}

// remover um perfil a partir de seu identificador (email);
char* delete_profile(char *email){

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL){
        printf("Error opening file!\n");

        return NULL;
    }

    json_object *profiles = json_object_from_file(FILENAME);
    if (profiles == NULL){
        printf("Error reading file!\n");
        fclose(file);

        return NULL;
    }

    // print the profiles

    profiles = json_object_object_get(profiles, "profiles");

    int n_profiles = json_object_array_length(profiles);

    for (int i = 0; i < n_profiles; i++){
        json_object *p = json_object_array_get_idx(profiles, i);
        json_object *email_ = json_object_object_get(p, "email");

        if (strcmp(json_object_get_string(email_), email) == 0)
        {
            json_object_array_del_idx(profiles, i, 1);
            return ("Profile deleted successfully with the email: %s\n", email);
            json_object *new_profiles = json_object_new_object();

            json_object_object_add(new_profiles, "profiles", profiles);

            if (json_object_to_file(FILENAME, new_profiles) == -1)
            {
                printf("Error writing to file!\n");
                fclose(file);
                json_object_put(new_profiles);

                return NULL;
            }
            return NULL;
        }
    }

    fclose(file);

    return ("Profile not found with the email: %s\n", email);
}

// dado o email de um perfil, retornar suas informações;
char* get_profile_info(char* email) {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    json_object* profiles = json_object_from_file(FILENAME);
    if (profiles == NULL) {
        printf("Error reading file!\n");
        fclose(file);
        return NULL;
    }

    profiles = json_object_object_get(profiles, "profiles");
    int n_profiles = json_object_array_length(profiles);

    for (int i = 0; i < n_profiles; i++) {
        json_object* p = json_object_array_get_idx(profiles, i);
        json_object* email_ = json_object_object_get(p, "email");

        if (strcmp(json_object_get_string(email_), email) == 0) {

            char* info = malloc(sizeof(char) * 1000);
            snprintf(info, 1000, "Email: %s\nNome: %s\nSobrenome: %s\nResidencia: %s\nFormacao Academica: %s\nAno de Formatura: %d\nHabilidades:\n", 
                json_object_get_string(email_), json_object_get_string(json_object_object_get(p, "nome")),
                json_object_get_string(json_object_object_get(p, "sobrenome")), json_object_get_string(json_object_object_get(p, "residencia")),
                json_object_get_string(json_object_object_get(p, "formacao_academica")), json_object_get_int(json_object_object_get(p, "ano_de_formatura")));

            json_object* habilidades_array = json_object_object_get(p, "habilidades");
            int n_habilidades = json_object_array_length(habilidades_array);

            for (int i = 0; i < n_habilidades; i++) {
                char* habilidade = json_object_get_string(json_object_array_get_idx(habilidades_array, i));
                if (strcmp(habilidade, "") != 0) {
                    char* tmp = malloc(sizeof(char) * 1000);
                    snprintf(tmp, 1000, "\t%s\n", habilidade);
                    strncat(info, tmp, 1000 - strlen(info) - 1);
                    free(tmp);
                }
            }

            fclose(file);
            return info;
        }
    }

    fclose(file);
    return NULL;
}

// listar todas as pessoas (email e nome) formadas em um determinado curso;
char* list_profiles_by_course(char* course){
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL){
        printf("Error opening file!\n");
        return NULL;
    }

    json_object *profiles = json_object_from_file(FILENAME);
    if (profiles == NULL){
        printf("Error reading file!\n");
        fclose(file);
        return NULL;
    }

    // get the profiles array
    json_object *profiles_array = json_object_object_get(profiles, "profiles");

    int n_profiles = json_object_array_length(profiles_array);

    // allocate memory for the output string
    char* output = malloc(sizeof(char) * 10000);
    output[0] = '\0';

    for (int i = 0; i < n_profiles; i++){
        json_object *profile = json_object_array_get_idx(profiles_array, i);

        // check if the profile matches the course
        json_object *formacao_academica = json_object_object_get(profile, "formacao_academica");
        if (formacao_academica != NULL && strcmp(json_object_get_string(formacao_academica), course) == 0)
        {
            // concatenate email, name, and course into the output string
            json_object *email = json_object_object_get(profile, "email");
            json_object *nome = json_object_object_get(profile, "nome");
            sprintf(output + strlen(output), "Email: %s, Nome: %s, Curso: %s\n", json_object_get_string(email), json_object_get_string(nome), course);
        }
    }

    fclose(file);
    return output;
}

// listar todas as pessoas (email e nome) formadas em uma determinada habilidade;
char* list_profiles_by_skill(char *skill){
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL){
        printf("Error opening file!\n");
        return NULL;
    }

    json_object *profiles = json_object_from_file(FILENAME);
    if (profiles == NULL){
        printf("Error reading file!\n");
        fclose(file);
        return NULL;
    }

    profiles = json_object_object_get(profiles, "profiles");
    int n_profiles = json_object_array_length(profiles);

    char *result = malloc(sizeof(char) * 1000);
    strcpy(result, "");

    strcat(result, "Perfis com a habilidade ");
    strcat(result, skill);
    strcat(result, ":\n");

    for (int i = 0; i < n_profiles; i++){
        json_object *p = json_object_array_get_idx(profiles, i);
        json_object *email_ = json_object_object_get(p, "email");
        json_object *habilidades_ = json_object_object_get(p, "habilidades");

        int n_habilidades = json_object_array_length(habilidades_);
        int found = 0;

        for (int j = 0; j < n_habilidades; j++){
            json_object *h = json_object_array_get_idx(habilidades_, j);

            if (strcmp(json_object_get_string(h), skill) == 0){
                if (found == 0){
                    strcat(result, "Email: ");
                    strcat(result, json_object_get_string(email_));
                    strcat(result, "\n");
                    strcat(result, "Nome: ");
                    strcat(result, json_object_get_string(json_object_object_get(p, "nome")));
                    strcat(result, "\n");
                    found = 1;
                }
            }
        }
    }

    fclose(file);
    return result;
}

// listar todas as informações de todos os perfis;
char* get_all_profiles(){
    char* profiles = malloc(5000 * sizeof(char)); // allocate memory for the char array
    memset(profiles, 0, 5000); // initialize the array with null bytes

    FILE* file = fopen(FILENAME, "r");

    if (file == NULL){
        printf("Error opening file!\n");
        free(profiles); // free memory before returning
        return NULL;
    }

    json_object* root = json_object_from_file(FILENAME);
    if (root == NULL){
        printf("Error reading file!\n");
        fclose(file);
        free(profiles); // free memory before returning
        return NULL;
    }

    json_object* profiles_array = json_object_object_get(root, "profiles");
    int n_profiles = json_object_array_length(profiles_array);

    for (int i = 0; i < n_profiles; i++){
        json_object* profile = json_object_array_get_idx(profiles_array, i);
        char email[100], nome[100], sobrenome[100], residencia[100], formacao[100], habilidades[500];
        int ano_formatura;

        // get the values of each field in the profile object
        sprintf(email, "Email: %s\n", json_object_get_string(json_object_object_get(profile, "email")));
        sprintf(nome, "Nome: %s\n", json_object_get_string(json_object_object_get(profile, "nome")));
        sprintf(sobrenome, "Sobrenome: %s\n", json_object_get_string(json_object_object_get(profile, "sobrenome")));
        sprintf(residencia, "Residência: %s\n", json_object_get_string(json_object_object_get(profile, "residencia")));
        sprintf(formacao, "Formação Acadêmica: %s\n", json_object_get_string(json_object_object_get(profile, "formacao_academica")));
        ano_formatura = json_object_get_int(json_object_object_get(profile, "ano_de_formatura"));

        json_object* habilidades_array = json_object_object_get(profile, "habilidades");
        int n_habilidades = json_object_array_length(habilidades_array);

        memset(habilidades, 0, sizeof(habilidades)); // initialize the habilidades array with null bytes
        for (int j = 0; j < n_habilidades; j++){
            if (json_object_array_get_idx(habilidades_array, j) != NULL){
                strcat(habilidades, json_object_get_string(json_object_array_get_idx(habilidades_array, j)));
                strcat(habilidades, " ");
            }
        }

        // concatenate the values of each field into the profiles array
        strcat(profiles, email);
        strcat(profiles, nome);
        strcat(profiles, sobrenome);
        strcat(profiles, residencia);
        strcat(profiles, formacao);
        sprintf(profiles + strlen(profiles), "Ano de Formatura: %d\n", ano_formatura);
        strcat(profiles, "Habilidades: ");
        strcat(profiles, habilidades);
        strcat(profiles, "\n\n");
    }

    fclose(file);
    return profiles;
}

// listar todas as pessoas (email, nome e curso) formadas em um determinado ano;
char* list_profiles_by_year(int year)
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return NULL;
    }

    json_object *profiles_obj = json_object_from_file(FILENAME);
    if (profiles_obj == NULL)
    {
        printf("Error reading file!\n");
        fclose(file);
        return NULL;
    }

    char *profiles = malloc(5000 * sizeof(char)); // allocate memory for the profiles string
    profiles[0] = '\0'; // initialize the string to an empty string

    strcat(profiles, "Perfis com a formacao em ");
    char year_str[5];
    sprintf(year_str, "%d", year);
    strcat(profiles, year_str);
    strcat(profiles, ":\n");

    // concatenate the profiles
    json_object *profiles_array = json_object_object_get(profiles_obj, "profiles");
    int n_profiles = json_object_array_length(profiles_array);

    for (int i = 0; i < n_profiles; i++)
    {
        json_object *profile = json_object_array_get_idx(profiles_array, i);
        int profile_year = json_object_get_int(json_object_object_get(profile, "ano_de_formatura"));

        if (profile_year == year)
        {
            strcat(profiles, "Email: ");
            strcat(profiles, json_object_get_string(json_object_object_get(profile, "email")));
            strcat(profiles, "\n");
            strcat(profiles, "Nome: ");
            strcat(profiles, json_object_get_string(json_object_object_get(profile, "nome")));
            strcat(profiles, "\n");
            strcat(profiles, "Curso: ");
            strcat(profiles, json_object_get_string(json_object_object_get(profile, "formacao_academica")));
            strcat(profiles, "\n\n");
        }
    }

    fclose(file);
    return profiles;
}

