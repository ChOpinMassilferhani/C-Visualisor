# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra  -std=c99 -g -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: Fractal 

Fractal: Fractal.c ./Tools/image.c ./Tools/pixel_operations.c

clean:
	${RM} *.o
	${RM} *.d
	${RM} Fractal

# END
