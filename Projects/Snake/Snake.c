# include <stdio.h>
# include <stdlib.h>

struct Tuple
{
    int x,y;
};

struct LKList
{
    struct Tuple* pos;
    struct LKList* next;
};

struct Snake
{
    struct LKList* head;
    int lenght;
};

void freeelm(struct LKList* cur)
{
    free(cur->next);
    free(cur->pos);
    free(cur);
}

void addHead(struct Snake* snake, struct Tuple* coordonate)
{
    snake->lenght += 1;
    struct LKList* new_head = malloc(sizeof(struct LKList));
    new_head->pos = coordonate;
    new_head->next = snake->head;
    snake->head = new_head;
}

void KillBut(struct Snake* snake)
{
    struct LKList * tmp = snake->head;
    while(tmp->next->next != NULL)
        tmp = tmp->next;
    freeelm(tmp->next);
    tmp->next = NULL;
}


void step(struct Snake* snake, struct Tuple* coordonate)
{
    KillBut(snake);
    addHead(snake,coordonate);
}