#include "Imagery/op.h"
#include <stdio.h>
/// @brief Initialize SDL
void init_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            errx(1, "Failed to init SDL : %s \n", SDL_GetError());
        }

    atexit(SDL_Quit);
}

/// @brief The main function of the program
/// @param path The path of the image to process
void exec_main(const char* path)
{
    init_sdl();

    SDL_Surface* surface = Load_SDL_img(path);

    if (!surface)
        {
            errx(EXIT_FAILURE, "Failed to load image");
        }


    // Create Image
    Image image = create_image(surface, ((char*)path));
    
    //grayscale
    grayscale(&image);
    surface = image_to_surface(&image);
    Save_SDL_img(surface, path, 0);
    printf("grayscale, id : 0\n");
    
    //contrast
    image_levels(&image, 10);
    image_invertion(&image);
    image_normalize_brightness(&image);
    surface = image_to_surface(&image);
    Save_SDL_img(surface, path, 1);
    printf("contrats, id : 1\n");
    
    //treshold
    image_adaptative_threshold(&image);
    surface = image_to_surface(&image);
    Save_SDL_img(surface, path, 2);
    printf("treshold, id : 2\n");
    
    //detection
    Image copy = copy_image(&image);
    Image simplifiedImage = copy_image(&image);
    edgeDetection(&copy);
    Image illustration = detection(&image, &copy, &simplifiedImage);
    surface = image_to_surface(&simplifiedImage);
    Save_SDL_img(surface, path, 3);
    printf("simplyfied, id : 3\n");
    surface = image_to_surface(&copy);
    Save_SDL_img(surface, path, 4);
    printf("List line, id : 4\n");
    surface = image_to_surface(&image);
    Save_SDL_img(surface, path, 5);
    printf("rotated, id : 5\n");
    surface = image_to_surface(&illustration);
    Save_SDL_img(surface, path, 6);
    printf("correct Perspective, id : 6\n");
    surface = image_to_surface(&image);
    Save_SDL_img(surface, path, 9);



    SDL_FreeSurface(surface);
    free_image(&image);
    free_image(&copy);
    free_image(&simplifiedImage);
    free_image(&illustration);
    SDL_Quit();
}
