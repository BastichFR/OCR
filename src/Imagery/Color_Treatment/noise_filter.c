#include "Imagery/Color_Treatment/noise_filter.h"

/// @brief Sorts an array of integers using the bubble sort algorithm
/// @param arr The array to be sorted. 
/// @param n The number of elements in the array. 
void bubble_sort(Uint8* arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already in place  
        for (j = 0; j < n - i - 1; j++) {
            if (*arr[j] > *arr[j + 1]) {
                Uint8* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/// @brief apply median filter to an image
/// @param image The image to which the filter is applied
void noise_filter(Image* image) {

    Uint8* red[9];
    Uint8* green[9];
    Uint8* blue[9];

    for (unsigned int y = 1; y < image->height - 1; y++) {
        for (unsigned int x = 1; x < image->width - 1; x++) {

            
            int index = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    red[index]   = &(image->pixels[y + i][x + j].red);
                    green[index] = &(image->pixels[y + i][x + j].green);
                    blue[index]  = &(image->pixels[y + i][x + j].blue);
                    index++;
                }
            }
            

            bubble_sort(red, 9);
            bubble_sort(green, 9);
            bubble_sort(blue, 9);
        }
    }
}


