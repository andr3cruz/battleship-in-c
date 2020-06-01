/* FILE THAT CONTAINS THE FUNCTION CODE OF THE PROTOTYPES LISTED IN QUADTREE.H*/

#include "quadtree.h"

QD_Node *search(QD_Node *qtree, Point *p, Point *sw_corner, double side)
{
    if (qtree->type == QDNODE)
    {
        Quadrant quadrant;
        side = side / 2;
        if (p->x >= sw_corner->x && p->x < sw_corner->x + side && p->y >= sw_corner->y && p->y < sw_corner->y + side)
        { //NW
            quadrant = NW;
        }
        else if (p->x >= sw_corner->x && p->x < sw_corner->x + side && p->y >= sw_corner->y + side && p->y < sw_corner->y + 2 * side)
        { //NE
            quadrant = NE;
        }
        else if (p->x >= sw_corner->x + side && p->x < sw_corner->x + 2 * side && p->y >= sw_corner->y && p->y < sw_corner->y + side)
        { //SW
            quadrant = SW;
        }
        else
        {
            quadrant = SE;
        }
        switch (quadrant)
        {
        case NW:
            return search(qtree->node.quadrants[0], p, sw_corner, side);
            break;
        case NE:
            sw_corner->y = sw_corner->y + side;
            return search(qtree->node.quadrants[1], p, sw_corner, side);
            break;
        case SW:
            sw_corner->x = sw_corner->x + side;
            return search(qtree->node.quadrants[2], p, sw_corner, side);
            break;
        case SE:
            sw_corner->x = sw_corner->x + side;
            sw_corner->y = sw_corner->y + side;
            return search(qtree->node.quadrants[3], p, sw_corner, side); //SE
            break;
        default:
            break;
        }
    }
    printf("FOUND\n");
    return qtree;
}