/* FILE THAT CONTAINS THE INCLUDES,MACROS,STRUCTS AND FUNCTION PROTOTYPES TO THE BATTLESHIP GAME */

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//MACROS
#define WATER '~'
#define HIT 'X'
#define MISS 'M'
#define SHIP 'O'

//STRUCTS
typedef enum
{
    FALSE,
    TRUE
} Boolean;

typedef struct ship
{
    int hitpoints;
    char *name;
    char bitmap[5][5];
} Ship;

typedef struct cell
{
    char symbol;
    Ship *ship;
} Cell;

//PROTOTYPES
void startScreen(void);

void printShip(Ship *ship, int i);
void initializeShips(Ship *watership, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int T_SHIP, int NUM_SHIPS);
void rotateRight(Ship *ship, int i);
void rotateLeft(Ship *ship, int i);

#endif