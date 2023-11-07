#include "Imagery/Tools/rotate.h"

void draw(SDL_Renderer* renderer, SDL_Texture* texture,double angle)
{
    
    if (SDL_RenderCopyEx(renderer,texture,NULL,NULL,angle,NULL,SDL_FLIP_NONE)!=0)
    {
    	errx(EXIT_FAILURE,"%s",SDL_GetError());
    }
    SDL_RenderPresent(renderer);
}

// Event loop that calls the relevant event handler.
//
// renderer: Renderer to draw on.
// texture: Texture to display.
void event_loop(SDL_Renderer* renderer, SDL_Texture* texture, double angle)
{
    
    // Draws the fractal canopy (first draw).
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    
    draw(renderer,texture,angle);

    // Creates a variable to get the events.
    SDL_Event event;
    while (1)
    {
        // Waits for an event.
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            // If the "quit" button is pushed, ends the event loop.
            case SDL_QUIT:
                return;

            // If the window is resized, updates and redraws the diagonals.
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    draw(renderer, texture,angle);
                }
                break;
            case SDL_KEYDOWN:
                {
                    angle+=90;
                    SDL_RenderClear(renderer);
                    draw(renderer,texture,angle);
                    
                    break;
                }

        }
    }
}
int my_pow(int x, int pow)
{
    if (pow==0)
    {
        return 1;
    }
    
    int ret=x;
    for(int i=1;i<pow;i++)
    {
        ret*=x;
    }
    return ret;
}

double str_to_dou(char* to_conv)
{
    double ret=0;
    size_t i=0;
    int point=0;
    int nb_below_point=0;
    while (*(to_conv+i)!= '\0')
    {
        if (point)
        {
            if (*(to_conv+i)=='.')
            {
                errx(EXIT_FAILURE,"invalid format for argv[2]");
            }
            else if (*(to_conv+i)>=48 && *(to_conv+1)<=57)
            {
                nb_below_point++;
                ret+=(*(to_conv+i)-48)/my_pow(10,nb_below_point);
            }
            else
            {
                errx(EXIT_FAILURE,"invalid format for argv[2]");
            }
            
        }
        else
        {
            if (*(to_conv+i)=='.')
            {
                point=1;
            }
            else if (*(to_conv+i)>=48 && *(to_conv+1)<=57)
            {
                ret*=10;
                ret+=(*(to_conv+i)-48);
            }
            else
            {
                errx(EXIT_FAILURE,"invalid format for argv[2]");
            }
        }
        i++;
    }
    return ret;
}
