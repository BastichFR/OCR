#include "Imagery/Color_Treatment/blackandwhite.h"

void blackandwhite(Image *image){
	
	Pixel pixel;

	for(unsigned int y = 0; y < image->height; y++){
		for(unsigned int x = 0; x < image->width; x++){
			pixel = image->pixels[x][y];
			
			if((pixel.red + pixel.green + pixel.blue)/ 3 >= 127){
				image->pixels[x][y].red = 255;
				image->pixels[x][y].green = 255;
				image->pixels[x][y].blue = 255;
			} else {
				image->pixels[x][y].red = 0;
				image->pixels[x][y].green = 0;
				image->pixels[x][y].blue = 0;
			}
		}
	}
}
