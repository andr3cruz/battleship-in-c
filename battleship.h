#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>

#define WATER '.'
#define HIT 'X'
#define MISS '#'

typedef struct cell
{
    char symbol;
    int row;
    int column;
} Cell;

typedef struct battleship
{
    int size;
};

#endif