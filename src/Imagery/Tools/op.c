#include "Imagery/Tools/op.h"

void init_sdl(){
	// Init SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		errx( 1, "Failed to init SDL : %s \n", SDL_GetError());
	}
}

void exec_main(const char *path){

	// TODO : tester une partie du code pour voir d'ou vient le core dumped

    init_sdl();

    // Load image
    SDL_Surface *surface = Load_SDL_img(path);

    if (!surface){
        errx(EXIT_FAILURE, "Failed to load image");
    }
	

    // Create Image
    Image image = create_image(surface);

    // Apply black n white filter
    
	// blackandwhite(&image);

    // Recreate surface
    
	// surface = image_to_surface(&image);

    // Save image
    
	// Save_SDL_img(surface, path);

    // Free image data
    
	// free_image(&image);

	

    // Free memory
    
	// SDL_FreeSurface(surface);
	

    SDL_Quit();
}

