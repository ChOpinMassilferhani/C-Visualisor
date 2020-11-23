#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "./Tools/image.h"
#include "./Tools/pixel_operations.h"

struct thread_data
{
	long id;
	pthread_t sys_id;
	unsigned char *tab_start;
	long size;
}



int *generate_tab(int len)
{
	srand(time(NULL));
	int *tmp = calloc(len, sizeof(int));
	for (int i = 0; i < len; i++)
	{
		int random = rand() % len;
		if (tmp[random] == 0)
			tmp[random] = i;
		else
			i--;
	}
	return tmp;
}

void swap(SDL_Surface *image, SDL_Surface *screen, int *a, int index_a, int *b, int index_b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
	Uint32 white = SDL_MapRGB(image->format, 255, 255, 255);
	Uint32 black = SDL_MapRGB(image->format, 0, 0, 0);
	for (int j = 0; j < image->h; j++)
	{
		put_pixel(image, index_a, j, (image->h - j > *a) ? black : white);
		put_pixel(image, index_b, j, (image->h - j > *b) ? black : white);
	}
	update_surface(screen, image);
}

void BubbleSort(int *array, int len, SDL_Surface *image, SDL_Surface *screen)
{
	for (int i = 0; i < len; i++)
		for (int j = 0; j < len - i - 1; j++)
			if (array[j] > array[j + 1])
				swap(image, screen, &array[j], j, &array[j + 1], j + 1);
}

int partition(int array[], int low, int high, SDL_Surface *image, SDL_Surface *screen)
{

	int pivot = array[high];
	int i = (low - 1);

	for (int j = low; j < high; j++)
	{
		if (array[j] <= pivot)
		{
			i++;
			swap(image, screen, &array[i], i, &array[j], j);
		}
	}

	swap(image, screen, &array[i + 1], i + 1, &array[high], high);
	return (i + 1);
}

void quickSort(int array[], int low, int high, SDL_Surface *image, SDL_Surface *screen)
{
	if (low < high)
	{
		int pi = partition(array, low, high, image, screen);

		quickSort(array, low, pi - 1, image, screen);

		quickSort(array, pi + 1, high, image, screen);
	}
}

int main(int agrc, char **argv)
{
	if (agrc != 2)
		errx(EXIT_FAILURE, "Usage : ./Sort [size of array]");
	int len = atoi(argv[1]);
	if (len == 0)
		errx(EXIT_FAILURE, "Size is invalid");

	int *array = generate_tab(len);
	SDL_Surface *image = SDL_CreateRGBSurface(0, len, len, 32, 0, 0, 0, 0);
	SDL_Surface *screen = display_image(image);

	Uint32 white = SDL_MapRGB(image->format, 255, 255, 255);
	Uint32 black = SDL_MapRGB(image->format, 0, 0, 0);
	for (int i = 0; i < image->w; i++)
		for (int j = 0; j < image->h; j++)
			put_pixel(image, i, j, (image->h - j > array[i]) ? black : white);

	quickSort(array, 0, len - 1, image, screen);
	//sort(array,len,image,screen);

	free(array);
	SDL_FreeSurface(image);
	SDL_FreeSurface(screen);

	exit(EXIT_SUCCESS);
}
