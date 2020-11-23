# include <stdio.h>
# include <stdlib.h>
# include <err.h>
# include <math.h>
# include "SDL/SDL.h"
# include "SDL/SDL_image.h"
# include "Tools/image.h"
# include "Tools/pixel_operations.h"


void circle(SDL_Surface *image, SDL_Surface *screen,int x, int y, int rayon)
{
	if(rayon < 1)
		return;
	
	
	Uint32 pixel = SDL_MapRGB(image->format, 255, 255, 255);

	for (int j = y-rayon; j < y+rayon; j++)
	{
		int distance =  sqrt(pow(rayon,2) - pow(abs(rayon-(j-(y-rayon))),2) ) ;

		put_pixel(image,j, x + distance,pixel);
		put_pixel(image,j, x - distance,pixel);
	}
	

	int size = (rayon*425)/1024;
	circle(image,screen,x,y+rayon-size,size);
	circle(image,screen,x,y-rayon+size,size);
	circle(image,screen,x+rayon-size,y,size);
        circle(image,screen,x-rayon+size,y,size);

	circle(image,screen,x,y,(size*425)/1024);
	circle(image,screen,x-rayon+size,y-rayon+size,(size*425)/1024);
        circle(image,screen,x+rayon-size,y+rayon-size,(size*425)/1024);
        circle(image,screen,x-rayon+size,y+rayon-size,(size*425)/1024);
        circle(image,screen,x+rayon-size,y-rayon+size,(size*425)/1024);


	update_surface(screen,image);
}

int main(int argc , char **argv)
{
	if (argc != 2)
		errx(EXIT_FAILURE,"Usage: ./CercleRecusion [size]");

	int rayon = atoi(argv[1]);
	if( rayon == 0)
		errx(EXIT_FAILURE,"Invalid size");
	
	SDL_Surface *image = SDL_CreateRGBSurface(0, rayon*2+20, rayon*2+10, 32, 0, 0, 0, 0);
	SDL_Surface *screen = display_image(image);

	circle(image,screen,image->h/2,image->w/2,rayon);

	update_surface(screen,image);
	wait_for_keypressed();

	SDL_FreeSurface(image);
	SDL_FreeSurface(screen);

	exit(EXIT_SUCCESS);


}
