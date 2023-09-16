#include "Imagery/Color_Treatment/blackandwhite.h"

void blackandwhite(Image *image){
	
	int height = image->height;
	int width  = image->width;;

	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			Pixel pixel = image->pixels[x][y];
			
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
