/* FILE THAT CONTAINS THE INCLUDES,MACROS,STRUCTS AND FUNCTION PROTOTYPES TO THE BATTLESHIP GAME */
#ifndef QUADTREE_H
#define QUADTREE_H

//INCLUDES
#include "battleship.h"

//STRUCTS
typedef enum
{
    NW,
    NE,
    SW,
    SE
} Quadrant;

typedef enum
{
    QDNODE,
    QDLEAF
} QD_TNODE;

typedef struct point
{
    double x;
    double y;
} Point;

typedef struct qd_node
{
    QD_TNODE type;
    union {
        struct qd_node *quadrants[4];
        struct
        {
            Point *coords;
            Cell *cell;
        } leaf;
    } node;
} QD_Node;

typedef struct PlayerQuad
{
    int hitpoints;
    QD_Node *board;
    Ship *ship;
} PlayerQuad;

//PROTOTYPES
QD_Node *search(QD_Node *qtree, Point *p, Point sw_corner, double side);
void insert_node(QD_Node *qtree, Point *p, Cell *q, double side);
void initializePlayersQuad(PlayerQuad player, int DIM, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int T_SHIP, int NUM_SHIPS);
void manuallyPlaceShipsQuad(PlayerQuad player, int DIM, int NUM_SHIPS);
void printBoardQuad(PlayerQuad player, int DIM);

#endif
