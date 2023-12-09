#include "Imagery/Tools/io.h"

SDL_Surface* Load_SDL_img(const char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
        {
            fprintf(stderr, "Couldn't load %s: %s\n", path, SDL_GetError());
            return NULL;
        }

    return surface;
}

int Save_SDL_img(SDL_Surface* image, const char* path, int i)
{
    char extension[] = ".result";
    char new_path[strlen(path) + strlen(extension) + 2];

    char* dot = strrchr(path, '.');

    strncpy(new_path, path, dot - path);

    char* x = &new_path[0];
    x += dot - path;

    for (int i = 0; extension[i]; i++)
        {
            *x = extension[i];
            x++;
        }
    
    *x = i + '0';
    x++;
    
    while (*dot != 0)
        {
            *x = *dot;
            dot++;
            x++;
        }
    *x = 0;

    if (SDL_SaveBMP(image, new_path) != 0)
        {
            printf("Error while saving new file : %s \n", SDL_GetError());
            return 1;
        }

    return 0;
}
