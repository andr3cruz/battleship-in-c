/* FILE THAT CONTAINS THE INCLUDES,MACROS,STRUCTS AND FUNCTION PROTOTYPES TO THE MATRIX STRUCTURE */

#ifndef MATRIX
#define MATRIX_H

//INCLUDES
#include "battleship.h"

//STRUCTS
typedef struct player
{
    int hitpoints;
    Cell **board;
    Ship *ship;
} Player;

//PROTOTYPES
void printBoard(Cell **board, int DIM);
void printEnemyBoard(Cell **board, int DIM);
void initializeBoard(Cell **board, int DIM);
void initializePlayers(Player *player, int DIM, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int T_SHIP, int NUM_SHIPS);
Boolean checkPlacement(Player *player, int DIM, int i, int x, int y);
void placeShip(Player *player, int DIM, int i, int x, int y);
void manuallyPlaceShips(Player *player, int DIM, int NUM_SHIPS);
void randomlyPlaceShips(Player *player, int DIM, int NUM_SHIPS);
void play(Player *player1, Player *player2, int DIM, int *turn);

#endif