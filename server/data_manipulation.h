#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cJSON.h"
#include "../model/profile.h"

#define FILENAME "json/perfil.json"

int create_profile(perfil *p) {
    FILE *fp = fopen(FILENAME, "r+");
    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo!\n");
        return -1;
    }

    // Ler o conteúdo do arquivo JSON
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);
    char *json_content = (char *)malloc(file_size + 1);
    fread(json_content, 1, file_size, fp);

    // Converter o conteúdo para um objeto JSON
    cJSON *root = cJSON_Parse(json_content);
    if (root == NULL) {
        fprintf(stderr, "Erro ao parsear conteúdo do arquivo!\n");
        fclose(fp);
        free(json_content);
        return -1;
    }

    // Verificar se o perfil já existe
    cJSON *profiles = cJSON_GetObjectItem(root, "perfis");
    if (profiles != NULL) {
        cJSON *profile = NULL;
        cJSON_ArrayForEach(profile, profiles) {
            if (strcmp(cJSON_GetObjectItem(profile, "email")->valuestring, p->email) == 0) {
                fprintf(stderr, "Perfil já existe!\n");
                cJSON_Delete(root);
                fclose(fp);
                free(json_content);
                return -1;
            }
        }
    } else {
        profiles = cJSON_CreateArray();
        cJSON_AddItemToObject(root, "perfis", profiles);
    }

    // Criar o objeto JSON do novo perfil
    cJSON *new_profile = cJSON_CreateObject();
    cJSON_AddStringToObject(new_profile, "email", p->email);
    cJSON_AddStringToObject(new_profile, "nome", p->nome);
    cJSON_AddStringToObject(new_profile, "sobrenome", p->sobrenome);
    cJSON_AddStringToObject(new_profile, "residencia", p->residencia);
    cJSON_AddStringToObject(new_profile, "formacaoacademica", p->formacaoacademica);
    cJSON_AddNumberToObject(new_profile, "anodeformatura", p->anodeformatura);

    cJSON *habilidades = cJSON_CreateArray();
    for (int i = 0; i < 10; i++) {
        if (p->habilidades[i][0] != '\0') {
            cJSON_AddItemToArray(habilidades, cJSON_CreateString(p->habilidades[i]));
        } else {
            break;
        }
    }
    cJSON_AddItemToObject(new_profile, "habilidades", habilidades);

    cJSON_AddItemToArray(profiles, new_profile);

    // Escrever o conteúdo atualizado no arquivo JSON
    char *json_updated = cJSON_Print(root);
    fseek(fp, 0, SEEK_SET);
    fwrite(json_updated, strlen(json_updated), 1, fp);

    // Liberar memória e fechar arquivo
    free(json_content);
    free(json_updated);
    cJSON_Delete(root);
    fclose(fp);

    return 0;
}
