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
    int x;
    int y;
} Point;

typedef struct qd_node
{
    QD_TNODE type;
    union {
        struct QD_NODE *quadrants[4];
        struct
        {
            Point coords;
            Cell *cell;
        } leaf;
    } node;
} QD_Node;

#endif
