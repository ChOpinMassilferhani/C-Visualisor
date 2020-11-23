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
	int y;
	double alpha;
};

void update(SDL_Surface *image, SDL_Surface *screen, struct trajectoire *cur)
{
	Uint32 white = SDL_MapRGB(image->format, 255, 255, 255);
	for(;;)
	{
		for (int j = 0; j < image->w; j++)
		{
			cur->y += cur->alpha;
			if(cur->y >= image->h || cur->y < 0)
			{
				cur->alpha = -cur->alpha;
				cur->y += cur->alpha;
			}
			put_pixel(image, j, cur->y,white);
			update_surface(screen,image);
			usleep(500);
		}
		for (int j = image->w-1; j > 0; j--)
		{
			cur->y += cur->alpha;
			if(cur->y >= image->h || cur->y < 0)
                        {
                                cur->alpha = -cur->alpha;
				cur->y += cur->alpha;
                        }
			put_pixel(image, j,  cur->y,white);
			update_surface(screen,image);
			usleep(500);
		}

	}

}

int main(int argc, char **argv) 
{
	int len = 75;
	if(argc != 3)
		errx(EXIT_FAILURE,"Usage : ./DvD [y] [alpha]");
	SDL_Surface *image = SDL_CreateRGBSurface(0, len*16, len*9, 32, 0, 0, 0, 0);
	SDL_Surface *screen = display_image(image);

	struct trajectoire *cur = calloc(1,sizeof(struct trajectoire));

	cur->y	   = atoi(argv[1]);
	cur->alpha = atof(argv[2]);

	update(image,screen,cur);

	SDL_FreeSurface(image);
	SDL_FreeSurface(screen);

	exit(EXIT_SUCCESS);
}
