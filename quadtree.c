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
            return search(qtree->node.quadrants[3], p, sw_corner, side);
            break;
        default:
            break;
        }
    }
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
        insert->node.leaf.coords = p;
        insert->node.leaf.cell = q;
    }
    else
    {
        Point *coords = insert->node.leaf.coords;
        Cell *cell = insert->node.leaf.cell;
        insert->node.leaf.coords = NULL;
        insert->node.leaf.cell = NULL;
        insert->type = QDNODE;
        for (int i = 0; i < 4; i++)
        {
            insert->node.quadrants[i] = (QD_Node *)malloc(sizeof(QD_Node));
            insert->node.quadrants[i]->type = QDLEAF;
            insert->node.quadrants[i]->node.leaf.cell = NULL;
            insert->node.quadrants[i]->node.leaf.coords = NULL;
        }
        insert_node(qtree, coords, cell, side);
        insert_node(qtree, p, q, side);
    }
}

void initializePlayersQuad(PlayerQuad player, int DIM, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int T_SHIP, int NUM_SHIPS)
{
    player.hitpoints = CARRIER * 5 + BATTLESHIP * 4 + CRUISER * 3 + SUBMARINE * 3 + DESTROYER * 2 + T_SHIP * 5;

    player.board = (QD_Node *)malloc(sizeof(QD_Node));
    player.board->type = QDLEAF;
    player.board->node.leaf.cell = NULL;
    player.board->node.leaf.coords = NULL;

    player.ship = (Ship *)malloc(NUM_SHIPS * sizeof(Ship));

    initializeShips(player.ship, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, T_SHIP, NUM_SHIPS);
}

void manuallyPlaceShipsQuad(PlayerQuad player, int DIM, int NUM_SHIPS)
{
    int x, y, input;

    for (int i = 0; i < NUM_SHIPS; i++)
    {
        printBoardQuad(player, DIM);
        putchar('\n');
        printShip(player.ship, i);

        printf("1) Rotate ship left\n");
        printf("2) Rotate ship right\n");
        printf("3) Place ship\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            rotateLeft(player.ship, i);
            i--;
            system("clear");
            break;

        case 2:
            rotateRight(player.ship, i);
            i--;
            system("clear");
            break;
        /*
        case 3:
            printf("Type the numerical coordinate X of where you want to place your %s\n", player->ship[i].name);
            scanf("%d", &x);
            getchar();
            printf("Type the numerical coordinate Y of where you want to place your %s\n", player->ship[i].name);
            scanf("%d", &y);
            getchar();
            if ((y > DIM) || (x > DIM) || (x < 1) || (y < 1) || (checkPlacement(player, DIM, i, x, y) == FALSE))
            {
                i--;
                printf("Invalid operation\n");
                printf("Press <ENTER> to continue!");
                getchar();
                system("clear");
            }
            else
            {
                system("clear");
            }
            break;
        */
        default:
            i--;
            printf("Invalid operation\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            break;
        }
    }
}

void printBoardQuad(PlayerQuad player, int DIM)
{
    Point aux2;
    aux2.x = 0;
    aux2.y = 0;

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            Point *aux;
            aux->x = i;
            aux->y = j;
            QD_Node *square = search(player.board, aux, aux2, DIM);
            if (square->node.leaf.coords == NULL)
                printf("%c ", WATER);
            if (j == DIM - 1)
                putchar('\n');
        }
    }
}
