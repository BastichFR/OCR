#include "Imagery/Color_Treatment/noise_filter.h"

#define windowSize 3

// Fonction pour calculer la médiane
int median(int values[], int size) {
    // Triez les valeurs en ordre croissant
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (values[j] > values[j + 1]) {
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }

    // Calculez la médiane
    if (size % 2 == 0) {
        return (values[size / 2] + values[size / 2 - 1]) / 2;
    } else {
        return values[size / 2];
    }
}

// Fonction pour appliquer le filtre médian à une image
void noise_filter(Image *image) {
    int window[windowSize * windowSize];

    for (unsigned int y = windowSize / 2; y < image->height - windowSize / 2; y++) {
        for (unsigned int x = windowSize / 2; x < image->width - windowSize / 2; x++) {
            int index = 0;

            // Extraire les valeurs des pixels voisins dans la fenêtre
            for (int i = -windowSize / 2; i <= windowSize / 2; i++) {
                for (int j = -windowSize / 2; j <= windowSize / 2; j++) {
                    Pixel pixel = image->pixels[x + i][y + j];
                    window[index] = (pixel.red + pixel.green + pixel.blue) / 3; // Convertir en niveaux de gris pour simplifier
                    index++;
                }
            }

            // Appliquer le filtre médian
            int medianValue = median(window, windowSize * windowSize);

            // Mettre à jour la valeur du pixel actuel
            image->pixels[x][y].red = medianValue;
            image->pixels[x][y].green = medianValue;
            image->pixels[x][y].blue = medianValue;
        }
    }
}
