#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>
#include <unistd.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "./Tools/image.h"
#include "./Tools/pixel_operations.h"


struct trajectoire
{
    int x;
    int y;
    double alpha;
    double beta;
    double gamma;
};

double tra(struct trajectoire *cur, double x)
{
    return -0.005*cur->alpha*x*x + cur->beta*x + cur->gamma;
}


void update(SDL_Surface *image, SDL_Surface *screen, struct trajectoire *cur)
{
    Uint32 white = SDL_MapRGB(image->format, 255, 255, 255);
    for (int j = 0; j < image->w; j++)
    {
        int y = tra(cur,j);
        if(image->h - y > image->h)
            break;
        put_pixel(image, j, image->h - 1 - y,white);
//        printf("%d\n",y);
        update_surface(screen,image);
        usleep(1000);
    }
    sleep(1);

}

int main(int argc, char **argv) // [alpha] [beta] [gamma]
{
    int len = 500;
    if(argc != 4)
        errx(EXIT_FAILURE,"Usage : ./balancier [alpha] [beta] [gamma]");
    SDL_Surface *image = SDL_CreateRGBSurface(0, len*3, len, 32, 0, 0, 0, 0);
    SDL_Surface *screen = display_image(image);

    struct trajectoire *cur = calloc(1,sizeof(struct trajectoire));

    cur->alpha = atof(argv[1]);
    cur->beta  = atof(argv[2]);
    cur->gamma = atof(argv[3]);

    update(image,screen,cur);

    SDL_FreeSurface(image);
    SDL_FreeSurface(screen);

    exit(EXIT_SUCCESS);
}
