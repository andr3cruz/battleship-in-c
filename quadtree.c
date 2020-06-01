/* FILE THAT CONTAINS THE FUNCTION CODE OF THE PROTOTYPES LISTED IN QUADTREE.H*/

#include "quadtree.h"

QD_Node *search(QD_Node *qtree, Point *p, Point sw_corner, double side)
{
    if (qtree->type == QDNODE)
    {
        Quadrant quadrant;
        side = side / 2;

        if (p->x >= sw_corner.x && p->x < sw_corner.x + side && p->y >= sw_corner.y && p->y < sw_corner.y + side)
            quadrant = NW;
        else if (p->x >= sw_corner.x && p->x < sw_corner.x + side && p->y >= sw_corner.y + side && p->y < sw_corner.y + 2 * side)
            quadrant = NE;
        else if (p->x >= sw_corner.x + side && p->x < sw_corner.x + 2 * side && p->y >= sw_corner.y && p->y < sw_corner.y + side)
            quadrant = SW;
        else
            quadrant = SE;

        switch (quadrant)
        {
        case NW:
            return search(qtree->node.quadrants[0], p, sw_corner, side);
            break;
        case NE:
            sw_corner.y = sw_corner.y + side;
            return search(qtree->node.quadrants[1], p, sw_corner, side);
            break;
        case SW:
            sw_corner.x = sw_corner.x + side;
            return search(qtree->node.quadrants[2], p, sw_corner, side);
            break;
        case SE:
            sw_corner.x = sw_corner.x + side;
            sw_corner.y = sw_corner.y + side;
            return search(qtree->node.quadrants[3], p, sw_corner, side); //SE
            break;
        default:
            break;
        }
    }
    printf("FOUND\n");
    return qtree;
}

void insert_node(QD_Node *qtree, Point *p, Cell *q, double side)
{
    Point lower;
    lower.x = 0;
    lower.y = 0;

    QD_Node *insert = search(qtree, p, lower, side);
    if (insert->node.leaf.cell == NULL)
    {
        printf("1\n");
        insert->node.leaf.coords = p;
        insert->node.leaf.cell = q;
        printf("%f %f\n", insert->node.leaf.coords->x, insert->node.leaf.coords->y);
    }
    else
    {
        printf("2\n");
        Point *coords = insert->node.leaf.coords;
        Cell *cell = insert->node.leaf.cell;
        insert->node.leaf.coords = NULL;
        insert->node.leaf.cell = NULL;
        insert->type = QDNODE;
        for (int i = 0; i < 4; i++)
        {
            insert->node.quadrants[i] = (QD_Node *)malloc(sizeof(QD_Node));
            insert->node.quadrants[i].type = QDLEAF;
            insert->node.quadrants[i]->node.leaf.cell = NULL;
            insert->node.quadrants[i]->node.leaf.coords = NULL;
        }
        insert_node(qtree, coords, cell, side);
        insert_node(qtree, p, q, side);
    }
}