#ifndef BATTLESHIP_H
#define BATTLESHIP_H

// INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// MACROS

#define WATER '~'
#define HIT 'X'
#define MISS '*'

// STRUCTS

typedef enum
{
    FALSE,
    TRUE
} Boolean;

typedef struct ship
{
    int hitpoints;
    char *name;
} Ship;

typedef struct cell
{
    char symbol;
    int row;
    int column;
    Ship ship;
} Cell;

typedef struct player
{
    int hitpoints;
    Cell **board;
    Ship *ship;
} Player;

// PROTOTYPES

void startScreen(void);
void initializeBoard(int ROWS, int COLS, Cell **board);
void printBoard(int ROWS, int COLS, Player player);
void initializeShips(Ship *watership, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int NUM_SHIPS);
Boolean checkSpotsUp(Player player, int i, int x, int y);
Boolean checkSpotsDown(Player player, int i, int x, int y);
Boolean checkSpotsLeft(Player player, int i, int x, int y);
Boolean checkSpotsRight(Player player, int i, int x, int y);
Boolean impossiblePlay(Player player, int ROWS, int COLS, int i, int x, int y);
void manuallyPlaceShips(int ROWS, int COLS, int NUM_SHIPS, Player player);
void randomlyPlaceShips(int ROWS, int COLS, int NUM_SHIPS, Player player);

#endif