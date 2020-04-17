/* FILE THAT CONTAINS THE FUNCTION CODE OF THE PROTOTYPES
   LISTED IN BATTLESHIP.H*/

#include "battleship.h"

//PRINTS THE INITIAL SCREEN
void startScreen(void)
{
    system("clear");
    printf("Welcome to Battleship in C!\n\n");
}

//PRINTS THE BOARD GIVEN AS AN ARGUMENT
void printBoard(int DIM, Cell **board)
{
    for (int i = 0; i < DIM; i++)
    {

        for (int j = 0; j < DIM; j++)
        {
            printf("%c ", board[i][j].symbol);
        }
        putchar('\n');
    }
    putchar('\n');
}

//PRINTS THE BOARD GIVEN AS AN ARGUMENT AND HIDES THE SHIPS
void printEnemyBoard(int DIM, Cell **board)
{
    for (int i = 0; i < DIM; i++)
    {

        for (int j = 0; j < DIM; j++)
        {
            if (board[i][j].symbol == SHIP)
                printf("%c ", WATER);
            else
                printf("%c ", board[i][j].symbol);
        }
        putchar('\n');
    }
    putchar('\n');
}

//PRINTS THE SHIP BITMAP
void printShip(Player player, int i)
{
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            printf("%c ", player.ship[i].bitmap[j][k]);
        }
        putchar('\n');
    }
    putchar('\n');
}

//INITILIAZES THE BOARD GIVEN AS AN ARGUMENT WITH SIZE DIM BY DIM IN A 2D ARRAY
void initializeBoard(int DIM, Cell **board)
{
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
        {
            board[i][j].symbol = WATER;
        }
}

//INITILIAZES THE SHIPS GIVEN AS AN ARGUMENT PUTTING THEM IN AN ARRAY
void initializeShips(Ship *watership, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int T_SHIP, int NUM_SHIPS)
{

    for (int i = 0; i < NUM_SHIPS; i++) // PLAYER 1 SHIPS
    {
        if (CARRIER > 0)
        {
            watership[i].hitpoints = 5;
            watership[i].name = "Carrier";
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (j == 2)
                        watership[i].bitmap[j][k] = SHIP;
                    else
                        watership[i].bitmap[j][k] = WATER;
                }
            }
            CARRIER--;
        }
        else if (BATTLESHIP > 0)
        {
            watership[i].hitpoints = 4;
            watership[i].name = "Battleship";
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (j == 2 && k < 4)
                        watership[i].bitmap[j][k] = SHIP;
                    else
                        watership[i].bitmap[j][k] = WATER;
                }
            }
            BATTLESHIP--;
        }
        else if (CRUISER > 0)
        {
            watership[i].hitpoints = 3;
            watership[i].name = "Cruiser";
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (j == 2 && k > 0 && k < 4)
                        watership[i].bitmap[j][k] = SHIP;
                    else
                        watership[i].bitmap[j][k] = WATER;
                }
            }
            CRUISER--;
        }
        else if (SUBMARINE > 0)
        {
            watership[i].hitpoints = 3;
            watership[i].name = "Submarine";
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (j == 2 && k > 0 && k < 4)
                        watership[i].bitmap[j][k] = SHIP;
                    else
                        watership[i].bitmap[j][k] = WATER;
                }
            }
            SUBMARINE--;
        }
        else if (DESTROYER > 0)
        {
            watership[i].hitpoints = 2;
            watership[i].name = "Destroyer";
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (j == 2 && k > 0 && k < 3)
                        watership[i].bitmap[j][k] = SHIP;
                    else
                        watership[i].bitmap[j][k] = WATER;
                }
            }
            DESTROYER--;
        }
        else if (T_SHIP > 0)
        {
            watership[i].hitpoints = 2;
            watership[i].name = "T_ship";
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if ((j == 1 && k > 0 && k < 4) || (j == 2 && k == 2) || (j == 3 && k == 2))
                        watership[i].bitmap[j][k] = SHIP;
                    else
                        watership[i].bitmap[j][k] = WATER;
                }
            }
            T_SHIP--;
        }
    }
}

void initializePlayers(Player *player, int DIM, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int T_SHIP, int NUM_SHIPS)
{
    player->hitpoints = CARRIER * 5 + BATTLESHIP * 4 + CRUISER * 3 + SUBMARINE * 3 + DESTROYER * 2 + T_SHIP * 5;

    player->board = malloc(DIM * sizeof(Cell *));
    for (int i = 0; i < DIM; i++)
    {
        player->board[i] = malloc(DIM * sizeof(Cell));
    }

    player->ship = (Ship *)malloc(NUM_SHIPS * sizeof(Ship));

    initializeBoard(DIM, player->board);
    initializeShips(player->ship, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, T_SHIP, NUM_SHIPS);
}

//RETURNS TRUE IF THE PLAY IS POSSIBLE
Boolean checkPlacement(Player player, int DIM, int i, int x, int y)
{
    //CHECKS LEFT CORNER
    if (x <= 2)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 2 - x + 1; k++)
            {
                if (player.ship[i].bitmap[j][k] == SHIP)
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
                if (player.ship[i].bitmap[j][k] == SHIP)
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
                if (player.ship[i].bitmap[j][k] == SHIP)
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
                if (player.ship[i].bitmap[j][k] == SHIP)
                    return FALSE;
            }
        }
    }

    //CHECKS IF SHIP GOES ON TOP OF ANOTHER
    int xaux = x - 3;
    int yaux = y - 3;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            if (player.ship[i].bitmap[j][k] == SHIP)
                if (player.board[yaux][xaux++].symbol == SHIP)
                    return FALSE;
        }
        yaux++;
        xaux = x - 3;
    }

    return TRUE;
}

//ROTATES SHIP BITMAP RIGHT
void rotateRight(Player player, int i)
{
    char bitmap[5][5];
    int aux = 4;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            bitmap[k][aux] = player.ship[i].bitmap[j][k];
        }
        aux--;
    }

    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            player.ship[i].bitmap[j][k] = bitmap[j][k];
        }
    }
}

//ROTATES SHIP BITMAP LEFT
void rotateLeft(Player player, int i)
{
    char bitmap[5][5];
    int aux = 4;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            bitmap[aux - k][j] = player.ship[i].bitmap[j][k];
        }
    }

    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            player.ship[i].bitmap[j][k] = bitmap[j][k];
        }
    }
}

//PLACES THE SHIP IN THE BOARD
void placeShip(Player player, int DIM, int i, int x, int y)
{
    int xaux = x - 3;
    int yaux = y - 3;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            if (player.ship[i].bitmap[j][k] == SHIP)
                player.board[yaux][xaux].symbol = player.ship[i].bitmap[j][k];
            xaux++;
        }
        yaux++;
        xaux = x - 3;
    }
}

//FUNCTION TO ROTATE AND MANUALLY PLACE ALL SHIPS IN THE BOARD
void manuallyPlaceShips(int DIM, int NUM_SHIPS, Player player)
{
    int x, y, input;
    for (int i = 0; i < NUM_SHIPS; i++)
    {
        printBoard(DIM, player.board);
        printShip(player, i);

        printf("1) Rotate ship left\n");
        printf("2) Rotate ship right\n");
        printf("3) Place ship\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            rotateLeft(player, i);
            i--;
            break;

        case 2:
            rotateRight(player, i);
            i--;
            break;
        case 3:
            printf("Type the numerical coordinate X of where you want to place your %s\n", player.ship[i].name);
            scanf("%d", &x);
            getchar();
            printf("Type the numerical coordinate Y of where you want to place your %s\n", player.ship[i].name);
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
                placeShip(player, DIM, i, x, y);
            }
        }
    }
}

//RANDOMLY PLACES THE SHIPS IN THE BOARD OF THE PLAYER GIVEN AS ARGUMENT
void randomlyPlaceShips(int DIM, int NUM_SHIPS, Player player)
{
    for (int i = 0; i < NUM_SHIPS; i++)
    {
        int rotations = random() % 10;
        for (int j = 0; j < rotations; j++)
        {
            rotateLeft(player, i);
        }
        int x = random() % DIM + 1;
        int y = random() % DIM + 1;
        if (checkPlacement(player, DIM, i, x, y) == FALSE)
        {
            i--;
        }
        else
        {
            system("clear");
            placeShip(player, DIM, i, x, y);
        }
    }
}

//PLAY FUNCTION WHERE PLAYER1 IS THE ATTACKER AND PLAYER2 THE RECEIVER OF THE ATTACK
void play(Player *player1, Player *player2, int DIM, int *turn)
{
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
        switch (player2->board[y - 1][x - 1].symbol)
        {
        case WATER:
            player2->board[y - 1][x - 1].symbol = MISS;
            system("clear");
            printEnemyBoard(DIM, player2->board);
            printBoard(DIM, player1->board);
            printf("You MISSED!\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            if (*turn == 1)
                *turn = 2;
            else
                *turn = 1;
            break;

        case SHIP:
            player2->board[y - 1][x - 1].symbol = HIT;
            player2->board[y - 1][x - 1].ship->hitpoints--;
            player2->hitpoints--;
            if (player2->board[y - 1][x - 1].ship->hitpoints <= 0)
            {
                system("clear");
                printEnemyBoard(DIM, player2->board);
                printBoard(DIM, player1->board);
                printf("You destroyed the enemy's %s!\n", player2->board[y - 1][x - 1].ship->name);
                printf("Press <ENTER> to continue!");
                getchar();
                system("clear");
            }
            else
            {
                system("clear");
                printEnemyBoard(DIM, player2->board);
                printBoard(DIM, player1->board);
                printf("You HIT an enemy's ship!\n");
                printf("Press <ENTER> to continue!");
                getchar();
                system("clear");
            }
            if (*turn == 1)
                *turn = 2;
            else
                *turn = 1;
            break;

        default:
            system("clear");
            printEnemyBoard(DIM, player2->board);
            printBoard(DIM, player1->board);
            printf("INVALID PLAY!\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            break;
        }
    }
}