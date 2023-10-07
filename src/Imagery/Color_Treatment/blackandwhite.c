#include "Imagery/Color_Treatment/blackandwhite.h"

void blackandwhite(Image *image){
	
	Pixel pixel;

	for(unsigned int y = 0; y < image->height; y++){
		for(unsigned int x = 0; x < image->width; x++){
			pixel = image->pixels[x][y];
			
			// TODO set average
			if((pixel.red + pixel.green + pixel.blue)/ 3 >= 128){
				pixel.red = 255;
				pixel.green = 255;
				pixel.blue = 255;
			} else {
				pixel.red = 0;
				pixel.green = 0;
				pixel.blue = 0;
			}
		}
	}
}
