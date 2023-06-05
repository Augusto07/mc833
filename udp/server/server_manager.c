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
#include "../model/profile.h"

#define FILENAME "../json/perfil.json"
#define MAX_LEN_RCV 16384

// check and recv msg
void receive_message(int socket, char *message)
{

    while (1)
    {
        int received = recv(socket, message, MAX_LEN_RCV - 1, 0); // receive msg

        if (received == -1) // error recv
        {
            perror("Error receiving");
            return;
        }
        else if (received > MAX_LEN_RCV - 1) // overflow
        { 
            perror("Error word is too long");
            return;
        }
        else if (received >= 0) // ok
        { 
            message[received] = '\0';
            printf("Received: %s\n", message);
            return;
        }
    }
}

// check and send msg
void send_message(int socket, char *message)
{

    if (strlen(message) > MAX_LEN_RCV - 1) //overflow
    {
        perror("String is too big");
        return;
    }

    while (1)
    {
        int sent = send(socket, message, strlen(message), 0);
        if (sent == -1) // error send
        { 
            perror("Error sending");
            return;
        }
        else if (sent >= 0) // ok
        {
            return;
        }
    }
}

// fill profile struct with info from client
void fill_profile(int socket, perfil *profile)
{

    char email[50], nome[50], sobrenome[50], residencia[50], formacaoacademica[50], habilidades[512], anodeformatura[5];

    // email
    send_message(socket, "Insert email: \n");
    receive_message(socket, email);

    // name
    send_message(socket, "Insert name: \n");
    receive_message(socket, nome);

    // sobrenome
    send_message(socket, "Insert last name: \n");
    receive_message(socket, sobrenome);

    // residencia
    send_message(socket, "Insert residence: \n");
    receive_message(socket, residencia);

    // formacaoacademica
    send_message(socket, "Insert academic formation: \n");
    receive_message(socket, formacaoacademica);

    // habilidades
    send_message(socket, "Insert skills separated by comma (skill1,skill2...): \n");
    receive_message(socket, habilidades);

    // anodeformatura
    send_message(socket, "Insert graduation year: \n");
    receive_message(socket, anodeformatura);

    // copy values to struct
    strcpy(profile->email, email);
    strcpy(profile->nome, nome);
    strcpy(profile->sobrenome, sobrenome);
    strcpy(profile->residencia, residencia);
    strcpy(profile->formacaoacademica, formacaoacademica);
    strcpy(profile->habilidades[0], strtok(habilidades, ","));

    for (int i = 1; i < 10; i++)
    {
        char *token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(profile->habilidades[i], token);
        }
        else
        {
            strcpy(profile->habilidades[i], "");
        }
    }
    profile->anodeformatura = atoi(anodeformatura); // fix if given is char*
    return;
}

//==================FUNCTIONS TO BE PERFORMED BY THE SERVER==================

// create a new profile with info from struct
char *create_profile(perfil *profile)
{

    char *response;

    // error handling

    if (profile == NULL)
    {
        response = "Error, profile is NULL!\n";
        return response;
    }

    FILE *file = fopen(FILENAME, "r");

    if (file == NULL)
    {
        response = "Error, can't open file!\n";
        return response;
    }

    json_object *profiles = json_object_from_file(FILENAME); //get all obj from JSON

    if (profiles == NULL)
    {
        response = "Error, can't read file!\n";
        return response;
    }

    profiles = json_object_object_get(profiles, "profiles"); //get all profiles from JSON
    int n_profiles = json_object_array_length(profiles); // get how many profiles

    for (int i = 0; i < n_profiles; i++)
    {
        json_object *p = json_object_array_get_idx(profiles, i);
        json_object *email = json_object_object_get(p, "email");

        if (strcmp(json_object_get_string(email), profile->email) == 0)
        { // check if profile's email == given email
            fclose(file);
            json_object_put(profiles);
            response = "Error, profile with that email already exists!\n";
            return response;
        }
    }

    //create new JSON obj
    json_object *new_profile = json_object_new_object();

    //add to obj
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
    json_object_array_add(profiles, new_profile); //add new profile to profiles

    json_object *new_profiles = json_object_new_object(); //create new object

    //add the updated list of profiles to the new obj
    json_object_object_add(new_profiles, "profiles", profiles);

    if (json_object_to_file(FILENAME, new_profiles) == -1) //transform the new obj to file
    {
        fclose(file);
        json_object_put(new_profiles);
        response = "Error, can't write file!\n";
        return response;
    }

    fclose(file);
    response = "Profile created!\n";
    return response;
}

// delete a profile by email from client
char *delete_profile(char *email)
{

    char *response;

    FILE *file = fopen(FILENAME, "r");

    // error handling

    if (file == NULL)
    {
        response = "Error, can't open file!\n";
        return response;
    }

    json_object *profiles = json_object_from_file(FILENAME); //get all obj from JSON

    if (profiles == NULL)
    {
        fclose(file);
        response = "Error, can't read file!\n";
        return response;
    }

    profiles = json_object_object_get(profiles, "profiles"); //get all profiles from JSON

    int n_profiles = json_object_array_length(profiles); // get how many profiles

    for (int i = 0; i < n_profiles; i++) // search profile
    {
        json_object *p = json_object_array_get_idx(profiles, i);
        json_object *email_ = json_object_object_get(p, "email");

        if (strcmp(json_object_get_string(email_), email) == 0) //compare if given email == profile's email
        {
            json_object_array_del_idx(profiles, i, 1); // delete it
            json_object *new_profiles = json_object_new_object(); // make a new object
            json_object_object_add(new_profiles, "profiles", profiles); // save updated profiles to new obj

            if (json_object_to_file(FILENAME, new_profiles) == -1) //transform in file
            {
                fclose(file);
                json_object_put(new_profiles);
                response = "Error, can't write file!\n";
                return response;
            }
            response = "Profile deleted!\n";
            return response;
        }
    }

    fclose(file);
    response = "Can't find profile with that email!\n";
    return response;
}

// retrieve a profile by email from client
char *get_profile_info(char *email)
{
    char *response;

    FILE *file = fopen(FILENAME, "r");

    //error handling
    if (file == NULL)
    {
        response = "Error, can't open file!\n";
        return response;
    }

    json_object *profiles = json_object_from_file(FILENAME);
    if (profiles == NULL)
    {
        fclose(file);
        response = "Error, can't read file!\n";
        return response;
    }

    profiles = json_object_object_get(profiles, "profiles");
    int n_profiles = json_object_array_length(profiles);

    for (int i = 0; i < n_profiles; i++)
    {

        json_object *p = json_object_array_get_idx(profiles, i);
        json_object *email_ = json_object_object_get(p, "email");

        if (strcmp(json_object_get_string(email_), email) == 0) //if given email == profile's email
        {

            char *info = malloc(sizeof(char) * 1024); // alloc space to save string

            snprintf(info, 1024, "Email: %s\nName: %s\nSurname: %s\nResidence: %s\nCourse: %s\nGraduation Year: %d\nSkills: ",
                     json_object_get_string(email_), json_object_get_string(json_object_object_get(p, "nome")),
                     json_object_get_string(json_object_object_get(p, "sobrenome")), json_object_get_string(json_object_object_get(p, "residencia")),
                     json_object_get_string(json_object_object_get(p, "formacao_academica")), json_object_get_int(json_object_object_get(p, "ano_de_formatura"))); //concatenate info in one string
            

            json_object *habilidades_array = json_object_object_get(p, "habilidades");
            int n_habilidades = json_object_array_length(habilidades_array);

            for (int i = 0; i < n_habilidades; i++)
            {
                const char *habilidade = json_object_get_string(json_object_array_get_idx(habilidades_array, i));

                if (strcmp(habilidade, "") != 0)
                { // if hab isn't null
                    char *tmp = malloc(sizeof(char) * 100);
                    strcpy(tmp, "");
                    strcat(tmp, habilidade);
                    strcat(tmp, ", ");
                    strcat(info, tmp);
                    free(tmp);
                }
            }

            strcat(info, "\n\n");

            fclose(file);
            return info;
        }
    }

    fclose(file);
    response = "Error, profile doesn't exists!\n";
    return response;
}

// retrieve all profiles with course from client
char *list_profiles_by_course(char *course)
{

    char *response;

    FILE *file = fopen(FILENAME, "r");

    //error handling

    if (file == NULL)
    {
        response = "Error, can't open file!\n";
        return response;
    }

    json_object *profiles = json_object_from_file(FILENAME);
    if (profiles == NULL)
    {
        fclose(file);
        response = "Error, can't read file!\n";
        return response;
    }

    json_object *profiles_array = json_object_object_get(profiles, "profiles"); //get profiles

    int n_profiles = json_object_array_length(profiles_array);

    // allocate memory for the output string
    char *output = malloc(sizeof(char) * MAX_LEN_RCV);
    strcpy(output, "");

    strcat(output, "Profiles with course ");
    strcat(output, course);
    strcat(output, ":\n");
    strcat(output, "\n");

    for (int i = 0; i < n_profiles; i++)
    {
        json_object *profile = json_object_array_get_idx(profiles_array, i);

        // check if the profile matches the course
        json_object *formacao_academica = json_object_object_get(profile, "formacao_academica");

        if (formacao_academica != NULL && strcmp(json_object_get_string(formacao_academica), course) == 0)
        {
            // concatenate email, name, and course into the output string
            json_object *email = json_object_object_get(profile, "email");
            json_object *nome = json_object_object_get(profile, "nome");
            strcat(output, "Email: ");
            strcat(output, json_object_get_string(email));
            strcat(output, "\n");
            strcat(output, "Name: ");
            strcat(output, json_object_get_string(nome));
            strcat(output, "\n");
            strcat(output, "Course: ");
            strcat(output, course);
            strcat(output, "\n\n");
        }
    }

    if (strcmp(output, "") == 0)
    {
        fclose(file);
        response = "Profiles not found!\n";
        return response;
    }
    else
    {
        fclose(file);
        return output;
    }
}

// retrieve all profiles with skill from client
char *list_profiles_by_skill(char *skill)
{

    char *response;

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        response = "Error, can't open file!\n";
        return response;
    }

    json_object *profiles = json_object_from_file(FILENAME);

    if (profiles == NULL)
    {
        response = "Error, can't read file!\n";
        return response;
    }

    profiles = json_object_object_get(profiles, "profiles");
    int n_profiles = json_object_array_length(profiles);

    char *result = malloc(sizeof(char) * 5000);
    strcpy(result, "");

    strcat(result, "Profiles with skill ");
    strcat(result, skill);
    strcat(result, ":\n");
    strcat(result, "\n");

    printf("entrou\n");

    for (int i = 0; i < n_profiles; i++)
    {

        char *preresult = malloc(sizeof(char) * 300);
        strcpy(preresult, "");

        json_object *p = json_object_array_get_idx(profiles, i);
        json_object *email_ = json_object_object_get(p, "email");
        json_object *nome_ = json_object_object_get(p, "nome");
        json_object *habilidades_ = json_object_object_get(p, "habilidades");

        strcat(preresult, "Email: ");
        strcat(preresult, json_object_get_string(email_));
        strcat(preresult, "\n");
        strcat(preresult, "Name: ");
        strcat(preresult, json_object_get_string(nome_));
        strcat(preresult, "\n");
        strcat(preresult, "Skill: ");

        int n_habilidades = json_object_array_length(habilidades_);
        int have_skill = 0;

        for (int j = 0; j < n_habilidades; j++)
        {

            json_object *h = json_object_array_get_idx(habilidades_, j);

            if (strcmp(json_object_get_string(h), "") != 0 &&
                strstr(json_object_get_string(h), skill) != NULL) // if skill not empty and contains given skill
            {
                printf("habilidade %s\n", json_object_get_string(h));
                have_skill = 1;
                strcat(preresult, json_object_get_string(h));
                strcat(preresult, ", ");
            }
        }

        if (have_skill == 1)
        {
            strcat(result, preresult);
            strcat(result, "\n\n");
        }
        have_skill = 0;
        free(preresult);
    }

    if (strcmp(result, "") == 0)
    {
        fclose(file);
        response = "Profiles not found!\n";
        return response;
    }
    else
    {
        fclose(file);
        return result;
    }
}

// retrieve all profiles
char *get_all_profiles()
{
    char *response;

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        response = "Error, can't open file!\n";
        return response;
    }

    json_object *profiles_obj = json_object_from_file(FILENAME);
    if (profiles_obj == NULL)
    {
        fclose(file);
        response = "Error, can't read file!\n";
        return response;
    }

    json_object *profiles_array = json_object_object_get(profiles_obj, "profiles");
    int n_profiles = json_object_array_length(profiles_array);
    response = malloc(MAX_LEN_RCV * sizeof(char));
    strcpy(response, "");

    for (int i = 0; i < n_profiles; i++)
    {
        json_object *profile = json_object_array_get_idx(profiles_array, i);
        json_object *email = json_object_object_get(profile, "email");
        json_object *nome = json_object_object_get(profile, "nome");
        json_object *sobrenome = json_object_object_get(profile, "sobrenome");
        json_object *residencia = json_object_object_get(profile, "residencia");
        json_object *formacao_academica = json_object_object_get(profile, "formacao_academica");
        json_object *ano_de_formatura = json_object_object_get(profile, "ano_de_formatura");
        json_object *habilidades = json_object_object_get(profile, "habilidades");

        char *info = malloc(1024 * sizeof(char));
        snprintf(info, 1024, "Email: %s\nName: %s\nSurname: %s\nResidence: %s\nCourse: %s\nGraduation Year: %d\nSkills: ",
                 json_object_get_string(email), json_object_get_string(nome), json_object_get_string(sobrenome),
                 json_object_get_string(residencia), json_object_get_string(formacao_academica), json_object_get_int(ano_de_formatura));

        int n_habilidades = json_object_array_length(habilidades);
        for (int j = 0; j < n_habilidades; j++)
        {
            const char *habilidade = json_object_get_string(json_object_array_get_idx(habilidades, j));
            if (strcmp(habilidade, "") != 0)
            { // se hab não é vazia
                char *tmp = malloc(100 * sizeof(char));
                strcpy(tmp, "");
                strcat(tmp, habilidade);
                strcat(tmp, ", ");
                strcat(info, tmp);
                free(tmp);
            }
        }

        strcat(info, "\n\n");
        strcat(response, info);
        free(info);
    }

    fclose(file);
    if (strcmp(response, "") == 0)
    {
        response = "There are no profiles!\n";
    }
    return response;
}

// retrieve all profiles with grad year from client
char *list_profiles_by_year(char *year)
{

    char *response;
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL)
    {
        response = "Error, can't open file!\n";
        return response;
    }

    json_object *profiles_obj = json_object_from_file(FILENAME);

    if (profiles_obj == NULL)
    {
        fclose(file);
        response = "Error, can't read file!\n";
        return response;
    }

    char *profiles = malloc(MAX_LEN_RCV * sizeof(char)); // allocate memory for the profiles string
    strcpy(profiles, "");                          // initialize the string to an empty string
    strcat(profiles, "Profiles graduated in ");
    strcat(profiles, year);
    strcat(profiles, ":\n\n");

    // concatenate the profiles
    json_object *profiles_array = json_object_object_get(profiles_obj, "profiles");
    int n_profiles = json_object_array_length(profiles_array);

    for (int i = 0; i < n_profiles; i++)
    {
        json_object *profile = json_object_array_get_idx(profiles_array, i);
        int profile_year = json_object_get_int(json_object_object_get(profile, "ano_de_formatura"));

        if (profile_year == atoi(year))
        {
            strcat(profiles, "Email: ");
            strcat(profiles, json_object_get_string(json_object_object_get(profile, "email")));
            strcat(profiles, "\n");
            strcat(profiles, "Name: ");
            strcat(profiles, json_object_get_string(json_object_object_get(profile, "nome")));
            strcat(profiles, "\n");
            strcat(profiles, "Course: ");
            strcat(profiles, json_object_get_string(json_object_object_get(profile, "formacao_academica")));
            strcat(profiles, "\n\n");
        }
    }

    if (strcmp(profiles, "") == 0)
    {
        fclose(file);
        response = "Profiles not found!\n";
        return response;
    }
    else
    {
        fclose(file);
        return profiles;
    }
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}