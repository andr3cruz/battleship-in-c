/* FILE THAT CONTAINS THE FUNCTION CODE OF THE PROTOTYPES LISTED IN QUADTREE.H*/
#include "quadtree.h"

//RETURNS THE NODE WHERE THE POINT P IS LOCATED
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

//INSERTS A CELL WHERE THE POINT P IS LOCATED
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

//ALLOCATES THE MEMORY FOR THE BOARD AND THE SHIPS AND INITIALIZES ALL THE PLAYER VALUES
void initializePlayersQuad(PlayerQuad *player, int DIM, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int T_SHIP, int NUM_SHIPS)
{
    player->hitpoints = CARRIER * 5 + BATTLESHIP * 4 + CRUISER * 3 + SUBMARINE * 3 + DESTROYER * 2 + T_SHIP * 5;

    player->board = (QD_Node *)malloc(sizeof(QD_Node));
    player->board->type = QDLEAF;
    player->board->node.leaf.cell = NULL;
    player->board->node.leaf.coords = NULL;

    player->ship = (Ship *)malloc(NUM_SHIPS * sizeof(Ship));

    initializeShips(player->ship, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, T_SHIP, NUM_SHIPS);
}

//MANUALLY PLACES THE SHIPS IN THE BOARD OF THE PLAYER GIVEN AS ARGUMENT
void manuallyPlaceShipsQuad(PlayerQuad *player, int DIM, int NUM_SHIPS)
{
    int x, y, input;

    for (int i = 0; i < NUM_SHIPS; i++)
    {
        printBoardQuad(player, DIM);
        putchar('\n');
        printShip(player->ship, i);

        printf("1) Rotate ship left\n");
        printf("2) Rotate ship right\n");
        printf("3) Place ship\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            rotateLeft(player->ship, i);
            i--;
            system("clear");
            break;

        case 2:
            rotateRight(player->ship, i);
            i--;
            system("clear");
            break;
        case 3:
            printf("Type the numerical coordinate X of where you want to place your %s\n", player->ship[i].name);
            scanf("%d", &x);
            getchar();
            printf("Type the numerical coordinate Y of where you want to place your %s\n", player->ship[i].name);
            scanf("%d", &y);
            getchar();
            if ((y > DIM) || (x > DIM) || (x < 1) || (y < 1) || (checkPlacementQuad(player, DIM, i, x, y) == FALSE))
            {
                i--;
                printf("Invalid operation\n");
                printf("Press <ENTER> to continue!");
                getchar();
                system("clear");
            }
            else
            {
                placeShipQuad(player, DIM, i, x, y);
                system("clear");
            }
            break;
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

//RANDOMLY PLACES THE SHIPS IN THE BOARD OF THE PLAYER GIVEN AS ARGUMENT
void randomlyPlaceShipsQuad(PlayerQuad *player, int DIM, int NUM_SHIPS)
{
    for (int i = 0; i < NUM_SHIPS; i++)
    {
        int rotations = random() % 10;
        for (int j = 0; j < rotations; j++)
        {
            rotateLeft(player->ship, i);
        }
        int x = random() % DIM + 1;
        int y = random() % DIM + 1;
        if (checkPlacementQuad(player, DIM, i, x, y) == FALSE)
        {
            i--;
        }
        else
        {
            system("clear");
            placeShipQuad(player, DIM, i, x, y);
        }
    }
}

//PRINTS THE BOARD GIVEN AS AN ARGUMENT
void printBoardQuad(PlayerQuad *player, int DIM)
{
    Point aux2;
    aux2.x = 0;
    aux2.y = 0;

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            Point *aux = (Point *)malloc(sizeof(Point));
            aux->x = i;
            aux->y = j;
            QD_Node *square = search(player->board, aux, aux2, DIM);
            if (square->node.leaf.coords != NULL && equalCoordinates(square->node.leaf.coords, aux) == TRUE)
                printf("%c ", square->node.leaf.cell->symbol);
            else
                printf("%c ", WATER);
        }
        putchar('\n');
    }
    printf("\n\n");
}

//PRINTS THE BOARD GIVEN AS AN ARGUMENT AND HIDES THE SHIPS
void printEnemyBoardQuad(PlayerQuad *player, int DIM)
{
    Point aux2;
    aux2.x = 0;
    aux2.y = 0;

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            Point *aux = (Point *)malloc(sizeof(Point));
            aux->x = i;
            aux->y = j;
            QD_Node *square = search(player->board, aux, aux2, DIM);
            if (square->node.leaf.coords != NULL && equalCoordinates(square->node.leaf.coords, aux) == TRUE && square->node.leaf.cell->symbol != SHIP)
                printf("%c ", square->node.leaf.cell->symbol);
            else
                printf("%c ", WATER);
        }
        putchar('\n');
    }
    printf("\n\n");
}

//RETURNS TRUE IF THE PLAY IS POSSIBLE
Boolean checkPlacementQuad(PlayerQuad *player, int DIM, int i, int x, int y)
{
    //CHECKS LEFT CORNER
    if (x <= 2)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 2 - x + 1; k++)
            {
                if (player->ship[i].bitmap[j][k] == SHIP)
                    return FALSE;
            }
        }
    }

    //CHECKS RIGHT CORNER
    else if (x >= DIM - 3)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 4; k > DIM - x + 2; k--)
            {
                if (player->ship[i].bitmap[j][k] == SHIP)
                    return FALSE;
            }
        }
    }

    //CHECKS TOP
    if (y <= 2)
    {
        for (int j = 0; j < 2 - y + 1; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if (player->ship[i].bitmap[j][k] == SHIP)
                    return FALSE;
            }
        }
    }

    //CHECKS BOTTOM
    else if (y >= DIM - 3)
    {
        for (int j = 4; j > DIM - y + 2; j--)
        {
            for (int k = 0; k < 5; k++)
            {
                if (player->ship[i].bitmap[j][k] == SHIP)
                    return FALSE;
            }
        }
    }

    //CHECKS IF A SHIP GOES ON TOP OF ANOTHER
    Point aux2;
    aux2.x = 0;
    aux2.y = 0;
    int xaux = y - 3;
    int yaux = x - 3;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            if (player->ship[i].bitmap[j][k] == SHIP)
            {
                Point *aux = (Point *)malloc(sizeof(Point));
                aux->x = xaux;
                aux->y = yaux;
                QD_Node *square = search(player->board, aux, aux2, DIM);
                if ((square->node.leaf.coords != NULL) && (equalCoordinates(square->node.leaf.coords, aux) == TRUE))
                {
                    return FALSE;
                }
            }
            yaux++;
        }
        xaux++;
        yaux = x - 3;
    }
    return TRUE;
}

//PLACES THE SHIP IN THE BOARD
void placeShipQuad(PlayerQuad *player, int DIM, int i, int x, int y)
{
    int xaux = y - 3;
    int yaux = x - 3;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            if (player->ship[i].bitmap[j][k] == SHIP)
            {
                Cell *aux = (Cell *)malloc(sizeof(Cell));
                aux->ship = &player->ship[i];
                aux->symbol = player->ship[i].bitmap[j][k];
                Point *point = (Point *)malloc(sizeof(Point));
                point->x = xaux;
                point->y = yaux;
                insert_node(player->board, point, aux, DIM);
            }
            yaux++;
        }
        xaux++;
        yaux = x - 3;
    }
}

//PLAY FUNCTION WHERE PLAYER1 IS THE ATTACKER AND PLAYER2 THE RECEIVER OF THE ATTACK
void playQuad(PlayerQuad *player1, PlayerQuad *player2, int DIM, int *turn)
{
    Point aux2;
    aux2.x = 0;
    aux2.y = 0;
    int x, y;
    printf("Type the numerical coordinate X of where you want to ATTACK\n");
    scanf("%d", &x);
    getchar();
    printf("Type the numerical coordinate Y of where you want to ATTACK\n");
    scanf("%d", &y);
    getchar();

    if (y > DIM || x > DIM || x < 1 || y < 1)
    {
        printf("Invalid operation, play again\n");
        printf("Press <ENTER> to continue!");
        getchar();
        system("clear");
    }
    else
    {
        Point *point = (Point *)malloc(sizeof(Point));
        point->x = y - 1;
        point->y = x - 1;

        QD_Node *square = search(player2->board, point, aux2, DIM);

        if (square->node.leaf.coords != NULL && equalCoordinates(square->node.leaf.coords, point) == TRUE && square->node.leaf.cell->symbol == SHIP)
        {
            square->node.leaf.cell->symbol = HIT;
            square->node.leaf.cell->ship->hitpoints--;
            player2->hitpoints--;

            system("clear");
            printEnemyBoardQuad(player2, DIM);
            printBoardQuad(player1, DIM);
            if (square->node.leaf.cell->ship->hitpoints <= 0)
                printf("You destroyed the enemy's %s!\n", square->node.leaf.cell->ship->name);
            else
                printf("You HIT an enemy's ship!\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
        }
        else if (square->node.leaf.coords != NULL && equalCoordinates(square->node.leaf.coords, point) == FALSE || square->node.leaf.coords == NULL)
        {
            Cell *aux = (Cell *)malloc(sizeof(Cell));
            aux->symbol = MISS;
            aux->ship = NULL;
            insert_node(player2->board, point, aux, DIM);
            system("clear");

            printEnemyBoardQuad(player2, DIM);
            printBoardQuad(player1, DIM);
            printf("You MISSED!\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
        }
        else
        {
            system("clear");
            printEnemyBoardQuad(player2, DIM);
            printBoardQuad(player1, DIM);
            printf("INVALID PLAY!\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
        }
    }
    if (*turn == 1)
        *turn = 2;
    else
        *turn = 1;
}

//RETURNS TRUE IF POINT A HAS THE SAME X AND Y VALUES AS POINT B
Boolean equalCoordinates(Point *a, Point *b)
{
    if ((a->x == b->x) && (a->y == b->y))
        return TRUE;
    else
        return FALSE;
}
