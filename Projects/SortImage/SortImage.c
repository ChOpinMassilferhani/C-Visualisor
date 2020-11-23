#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Tools/image.h"
#include "Tools/pixel_operations.h"

int main(int argc, char **argv)
{
	if (2 != argc)
		errx(EXIT_FAILURE, "Usage ./SortImage [image_name]");

	SDL_Surface *image = load_image(argv[1]);
	SDL_Surface *screen = display_image(image);

	int len = image->h * image->w;
	for (int k = 0; k < len; k++)
	{
		int no_change = 0;
		for (int i = 0; i < image->h; i++)
		{
			for (int j = 0; j < image->w; j++)
			{
				if (j == image->w - 1)
				{
					
					if (get_pixel(image, 0, i + 1) < get_pixel(image, j, i))
					{
						no_change = 1;
						Uint32 pixel = get_pixel(image, j, i);
						Uint32 pixel2 = get_pixel(image, 0, i + 1);
						put_pixel(image, j, i, pixel2);
						put_pixel(image, 0, i + 1, pixel);
					}
				}
				else
				{
					if (get_pixel(image, j + 1, i) < get_pixel(image, j, i))
					{
						no_change = 1;
						Uint32 pixel = get_pixel(image, j, i);
						Uint32 pixel2 = get_pixel(image, j + 1, i);
						put_pixel(image, j, i, pixel2);
						put_pixel(image, j + 1, i, pixel);
					}
				}
			}
		}
		if (!no_change)
			break;
		printf("%d of %d\n", len, k);
		update_surface(screen, image);
	}
	update_surface(screen, image);
	wait_for_keypressed();

	exit(EXIT_SUCCESS);
}
