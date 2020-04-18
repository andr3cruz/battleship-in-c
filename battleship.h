/* FILE THAT CONTAINS THE INCLUDES,MACROS,STRUCTS AND FUNCTION
   PROTOTYPES TO THE BATTLESHIP GAME */

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

typedef struct player
{
    int hitpoints;
    Cell **board;
    Ship *ship;
} Player;

//PROTOTYPES
void startScreen(void);
void printBoard(Cell **board, int DIM);
void printEnemyBoard(Cell **board, int DIM);
void printShip(Player *player, int i);
void initializeBoard(Cell **board, int DIM);
void initializeShips(Ship *watership, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int T_SHIP, int NUM_SHIPS);
void initializePlayers(Player *player, int DIM, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int T_SHIP, int NUM_SHIPS);
Boolean checkPlacement(Player *player, int DIM, int i, int x, int y);
void rotateRight(Player *player, int i);
void rotateLeft(Player *player, int i);
void placeShip(Player *player, int DIM, int i, int x, int y);
void manuallyPlaceShips(Player *player, int DIM, int NUM_SHIPS);
void randomlyPlaceShips(Player *player, int DIM, int NUM_SHIPS);
void play(Player *player1, Player *player2, int DIM, int *turn);

#endif