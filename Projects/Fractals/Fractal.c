# include <stdio.h>
# include <stdlib.h>
# include "SDL/SDL.h"
# include "SDL/SDL_image.h"
# include "./Tools/image.h"
# include "./Tools/pixel_operations.h"
# include "unistd.h"

void printsquare(SDL_Surface *image, int x, int y, int square)
{
	for (int i = 0; i < square; i++)
	{
		for (int j = 0; j < square; j++)
		{
			Uint32 pixel = SDL_MapRGB(image->format, 255, 255, 255);
			put_pixel(image, y+j, x+i, pixel);
		}
	}
}

void flocon(SDL_Surface *image, SDL_Surface *surface, int step, int x, int y, int len)
{
	update_surface(surface, image);
	if(step == 0)
		return;

	int size = len/3;
	printsquare(image,x+size,y,size+1);
	printsquare(image,x,y+size,size+1);
	printsquare(image,x+size,y+size*2,size+1);
	printsquare(image,x+size*2,y+size,size+1);

	flocon(image,surface,step-1,x,y,size);
	flocon(image,surface,step-1,x+2*size,y,size);
	flocon(image,surface,step-1,x+size,y+size,size);
	flocon(image,surface,step-1,x,y+size*2,size);
	flocon(image,surface,step-1,x+size*2,y+size*2,size);
}

void sponge(SDL_Surface *image, SDL_Surface *surface, int step, int x, int y, int len)
{
	update_surface(surface, image);
        if(step == 0)
                return;

        int size = len/3;
        printsquare(image,x+size,y+size,size);
	
	step--;
        sponge(image,surface,step,x,y,size);
        sponge(image,surface,step,x,y+size,size);
	sponge(image,surface,step,x,y+2*size,size);

        sponge(image,surface,step,x+size,y,size);
	sponge(image,surface,step,x+size,y+2*size,size);
        
	sponge(image,surface,step,x+2*size,y,size);
        sponge(image,surface,step,x+2*size,y+size,size);
	sponge(image,surface,step,x+2*size,y+2*size,size);
}


int main()
{
	int square = 1000;
	SDL_Surface *image = SDL_CreateRGBSurface(0, square, square, 32, 0, 0, 0, 0);
	SDL_Surface *surface = display_image(image);
	sponge(image,surface,5,0,0,square);
	update_surface(surface, image);
	wait_for_keypressed();
	exit(EXIT_SUCCESS);
}
