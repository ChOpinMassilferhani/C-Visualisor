#include <stdio.h>
#include <stdlib.h>

struct Board
{
    int board **;
    // 0 board
    // 1 snake
    // 2 food
    int width;
    int height;
};

struct Board *BoardInit(int width, int height)
{
    struct Board *tmp = malloc(sizeof(struct Board));
    tmp->height = height;
    tmp->width = width;

    tmp->board = calloc(sizeof(int *), height);
    for (int i = 0; i < height; i++)
        tmp->board[i] = calloc(sizeof(int), width);

    return tmp;
}

void add_food(struct Board board, struct Snake snake)
{
    int x = 0;
    int y = 0;
    while (1)
    {
        int x = rand() % board->height;
        int y = rand() % board->weigth;
        struct LKList tmp = snake->head;
        while (tmp != NULL && (tmp->pos->x != x || tmp->pos->y != y))
            tmp->next;
        if (tmp == NULL)
            break;
    }
    board->board[x][y] = 2;
}