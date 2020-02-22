#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <stdlib.h>

#define WATER '.'
#define HIT 'X'
#define MISS '#'

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

typedef struct
{
    int size;
    char *name;
} Battleship;

Cell initializeBoard();

#endif