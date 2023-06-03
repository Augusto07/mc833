#include <stdio.h>
#include <stdlib.h>

typedef struct image_struct_handler
{
    unsigned char *content;
    long size;
} image_struct_handler;

image_struct_handler *open_image(char *path)
{
    image_struct_handler *img = (image_struct_handler *)malloc(sizeof(image_struct_handler));

    if (!img)
    {
        printf("Not possible to allocate memory to the image.\n");
        return NULL;
    }

    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        free(img);
        printf("Not possible to open the file.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    img->size = ftell(file);
    rewind(file);

    img->content = (unsigned char *)malloc(img->size);
    if (!(img->content))
    {
        fclose(file);
        free(img);
        printf("Not possible to allocate memory.\n");
        return NULL;
    }

    size_t loaded_image = fread(img->content, 1, img->size, file);
    if (loaded_image != img->size)
    {
        fclose(file);
        free(img->content);
        free(img);
        printf("Not possible to load the image.\n");
        return NULL;
    }

    fclose(file);
    return img;
}

int save_image(char *path, image_struct_handler *img)
{
    FILE *image = fopen(path, "wb");
    if (image == NULL)
    {
        printf("Not possible to open the file.\n");
        return 1;
    }

    long saved = fwrite(img->content, 1, img->size, image);
    if (saved != img->size)
    {
        printf("Not possible to save the file.\n");
        return 1;
    }

    fclose(image);
    return 0;
}
