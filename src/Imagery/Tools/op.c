#include "Imagery/Tools/op.h"

/// @brief Initialize SDL
void init_sdl(){

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		errx( 1, "Failed to init SDL : %s \n", SDL_GetError());
	}

    atexit(SDL_Quit);
}

/// @brief The main function of the program
/// @param path The path of the image to process
void exec_main(const char *path){

    init_sdl();

    SDL_Surface *surface = Load_SDL_img(path);
    
    if (!surface){
        errx(EXIT_FAILURE, "Failed to load image");
    }

    // Create Image
    Image image = create_image(surface);

    grayscale(&image);
  

    //blackandwhite(&image);
    edgeDetection(&image);

    //noise_filter(&image); 

    surface = image_to_surface(&image);
    Save_SDL_img(surface, path);	
    
    free_image(&image);

    SDL_FreeSurface(surface);
    
    SDL_Quit();
}