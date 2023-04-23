#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../model/profile.h"
#include <json-c/json.h>

#define FILENAME "../json/perfil.json"

// cadastrar um novo perfil utilizando o email como identificador;
int create_profile(perfil *profile)
{

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
int delete_profile(char *email)
{

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
        json_object *email_ = json_object_object_get(p, "email");

        if (strcmp(json_object_get_string(email_), email) == 0)
        {
            json_object_array_del_idx(profiles, i, 1);
            printf("Profile deleted successfully with the email: %s\n", email);
            json_object *new_profiles = json_object_new_object();

            json_object_object_add(new_profiles, "profiles", profiles);

            if (json_object_to_file(FILENAME, new_profiles) == -1)
            {
                printf("Error writing to file!\n");
                fclose(file);
                json_object_put(new_profiles);

                return 1;
            }
            return 0;
        }
        {
        }
    }

    fclose(file);

    printf("Profile not found with the email: %s\n", email);

    return 1;
}

// dado o email de um perfil, retornar suas informações;
int print_info_profile(char *email)
{
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
        json_object *email_ = json_object_object_get(p, "email");

        if (strcmp(json_object_get_string(email_), email) == 0)
        {
            printf("Email: %s\n", json_object_get_string(email_));
            printf("Nome: %s\n", json_object_get_string(json_object_object_get(p, "nome")));
            printf("Sobrenome: %s\n", json_object_get_string(json_object_object_get(p, "sobrenome")));
            printf("Residencia: %s\n", json_object_get_string(json_object_object_get(p, "residencia")));
            printf("Formacao Academica: %s\n", json_object_get_string(json_object_object_get(p, "formacao_academica")));
            printf("Ano de Formatura: %d\n", json_object_get_int(json_object_object_get(p, "ano_de_formatura")));
            printf("Habilidades: \n");
            json_object *habilidades_array = json_object_object_get(p, "habilidades");
            int n_habilidades = json_object_array_length(habilidades_array);
            for (int i = 0; i < n_habilidades; i++)
            {

                // print only the non-empty skills
                if (strcmp(json_object_get_string(json_object_array_get_idx(habilidades_array, i)), "") != 0)

                    printf("\t%s\n", json_object_get_string(json_object_array_get_idx(habilidades_array, i)));
            }

            return 0;
        }
    }

    fclose(file);

    printf("Profile not found with the email: %s\n", email);

    return 1;
}
// listar todas as pessoas (email e nome) formadas em um determinado curso;
int list_profiles_by_course(char *course)
{
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

    // get the profiles array
    json_object *profiles_array = json_object_object_get(profiles, "profiles");

    int n_profiles = json_object_array_length(profiles_array);

    for (int i = 0; i < n_profiles; i++)
    {
        json_object *profile = json_object_array_get_idx(profiles_array, i);

        // check if the profile matches the course
        json_object *formacao_academica = json_object_object_get(profile, "formacao_academica");
        if (formacao_academica != NULL && strcmp(json_object_get_string(formacao_academica), course) == 0)
        {
            // print email and name
            json_object *email = json_object_object_get(profile, "email");
            json_object *nome = json_object_object_get(profile, "nome");
            printf("Email: %s, Nome: %s\n", json_object_get_string(email), json_object_get_string(nome));
        }
    }

    fclose(file);
    return 0;
}
// listar todas as pessoas (email e nome) formadas em uma determinada habilidade;
int list_profiles_by_skill(char *skill)
{
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

    printf("Perfis com a habilidade %s:\n", skill);

    for (int i = 0; i < n_profiles; i++)
    {
        json_object *p = json_object_array_get_idx(profiles, i);
        json_object *email_ = json_object_object_get(p, "email");
        json_object *habilidades_ = json_object_object_get(p, "habilidades");

        int n_habilidades = json_object_array_length(habilidades_);

        for (int j = 0; j < n_habilidades; j++)
        {
            json_object *h = json_object_array_get_idx(habilidades_, j);

            if (strcmp(json_object_get_string(h), skill) == 0)
            {
                printf("Email: %s\n", json_object_get_string(email_));
                printf("Nome: %s\n", json_object_get_string(json_object_object_get(p, "nome")));
                break;
            }
        }
    }

    fclose(file);

    return 0;
}

// • listar todas as pessoas (email, nome e curso) formadas em um determinado ano;
int list_profiles_by_year(int year)
{
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

    printf("Perfis com a formacao em %d:\n", year);

    // print the profiles
    profiles = json_object_object_get(profiles, "profiles");
    int n_profiles = json_object_array_length(profiles);

    for (int i = 0; i < n_profiles; i++)
    {
        json_object *p = json_object_array_get_idx(profiles, i);
        int profile_year = json_object_get_int(json_object_object_get(p, "ano_de_formatura"));

        if (profile_year == year)
        {
            printf("Email: %s\n", json_object_get_string(json_object_object_get(p, "email")));
            printf("Nome: %s\n", json_object_get_string(json_object_object_get(p, "nome")));
            printf("Curso: %s\n", json_object_get_string(json_object_object_get(p, "formacao_academica")));
        }
    }

    fclose(file);
    return 0;
}

// listar todas as informações de todos os perfis;
void print_all_profiles()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    json_object *profiles = json_object_from_file(FILENAME);
    if (profiles == NULL)
    {
        printf("Error reading file!\n");
        fclose(file);
        return;
    }

    profiles = json_object_object_get(profiles, "profiles");
    int n_profiles = json_object_array_length(profiles);

    printf("Perfis cadastrados:\n");

    for (int i = 0; i < n_profiles; i++)
    {
        json_object *p = json_object_array_get_idx(profiles, i);
        printf("Email: %s\n", json_object_get_string(json_object_object_get(p, "email")));
        printf("Nome: %s\n", json_object_get_string(json_object_object_get(p, "nome")));
        printf("Sobrenome: %s\n", json_object_get_string(json_object_object_get(p, "sobrenome")));
        printf("Residência: %s\n", json_object_get_string(json_object_object_get(p, "residencia")));
        printf("Formação Acadêmica: %s\n", json_object_get_string(json_object_object_get(p, "formacao_academica")));
        printf("Ano de Formatura: %d\n", json_object_get_int(json_object_object_get(p, "ano_de_formatura")));

        json_object *habilidades = json_object_object_get(p, "habilidades");
        int n_habilidades = json_object_array_length(habilidades);

        printf("Habilidades: ");
        for (int j = 0; j < n_habilidades; j++)
        {
            // if habilidades is not empty
            if (json_object_array_get_idx(habilidades, j) != NULL)

                printf("%s ", json_object_get_string(json_object_array_get_idx(habilidades, j)));
        }
        printf("\n\n");
    }

    fclose(file);
}
