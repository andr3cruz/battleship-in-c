#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <stdlib.h>

#define WATER '~'
#define HIT 'X'
#define MISS 'M'

typedef enum
{
    FALSE,
    TRUE
} Boolean;

typedef struct cell
{
    char symbol;
    int row;
    int column;
} Cell;

typedef struct battleship
{
    int size;
    char *name;
} Battleship;

void startScreen(void);
void initializeBoard(int ROWS, int COLS, Cell **board);
void printBoard(int ROWS, int COLS, Cell **board);

#endif