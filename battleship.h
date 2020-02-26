#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <stdlib.h>

#define WATER '~'
#define HIT 'X'
#define MISS '*'

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

typedef struct ship
{
    int hitpoints;
    char *name;
    int player;
} Ship;

typedef struct player
{
    int hitpoints;
    Cell **board;
    Ship *ship;
} Player;

void startScreen(void);
void initializeBoard(int ROWS, int COLS, Cell **board);
void printBoard(int ROWS, int COLS, Player player);
void initializeShips(Ship *watership, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int NUM_SHIPS);

#endif