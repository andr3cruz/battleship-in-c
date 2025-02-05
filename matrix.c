/* FILE THAT CONTAINS THE FUNCTION CODE OF THE PROTOTYPES LISTED IN MATRIX.H*/

#include "matrix.h"

//PRINTS THE BOARD GIVEN AS AN ARGUMENT
void printBoard(Cell **board, int DIM)
{
    printf("    ");

    for (int i = 0; i < DIM; i++)
    {
        if (i + 1 < 10)
            printf(" %d  ", i + 1);
        else
            printf(" %d ", i + 1);
    }
    putchar('\n');

    for (int i = 0; i < DIM; i++)
    {
        if (i + 1 < 10)
            printf(" %d |", i + 1);
        else
            printf("%d |", i + 1);
        for (int j = 0; j < DIM; j++)
        {
            printf(" %c |", board[i][j].symbol);
        }
        putchar('\n');
    }
    putchar('\n');
}

//PRINTS THE BOARD GIVEN AS AN ARGUMENT AND HIDES THE SHIPS
void printEnemyBoard(Cell **board, int DIM)
{
    printf("    ");

    for (int i = 0; i < DIM; i++)
    {
        if (i + 1 < 10)
            printf(" %d  ", i + 1);
        else
            printf(" %d ", i + 1);
    }
    putchar('\n');

    for (int i = 0; i < DIM; i++)
    {
        if (i + 1 < 10)
            printf(" %d |", i + 1);
        else
            printf("%d |", i + 1);
        for (int j = 0; j < DIM; j++)
        {
            if (board[i][j].symbol == SHIP)
                printf(" %c |", WATER);
            else
                printf(" %c |", board[i][j].symbol);
        }
        putchar('\n');
    }
    printf("\n\n");
}

//INITILIAZES THE BOARD GIVEN AS AN ARGUMENT WITH SIZE DIM BY DIM IN A 2D ARRAY
void initializeBoard(Cell **board, int DIM)
{
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
        {
            board[i][j].symbol = WATER;
        }
}

//ALLOCATES THE MEMORY FOR THE BOARD AND THE SHIPS AND INITIALIZES ALL THE PLAYER VALUES
void initializePlayers(Player *player, int DIM, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int T_SHIP, int NUM_SHIPS)
{
    player->hitpoints = CARRIER * 5 + BATTLESHIP * 4 + CRUISER * 3 + SUBMARINE * 3 + DESTROYER * 2 + T_SHIP * 5;

    player->board = malloc(DIM * sizeof(Cell *));
    for (int i = 0; i < DIM; i++)
    {
        player->board[i] = malloc(DIM * sizeof(Cell));
    }

    player->ship = (Ship *)malloc(NUM_SHIPS * sizeof(Ship));

    initializeBoard(player->board, DIM);
    initializeShips(player->ship, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, T_SHIP, NUM_SHIPS);
}

//RETURNS TRUE IF THE PLAY IS POSSIBLE
Boolean checkPlacement(Player *player, int DIM, int i, int x, int y)
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
    int xaux = x - 3;
    int yaux = y - 3;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            if (player->ship[i].bitmap[j][k] == SHIP)
            {
                if (player->board[yaux][xaux].symbol == SHIP)
                    return FALSE;
            }
            xaux++;
        }
        yaux++;
        xaux = x - 3;
    }

    return TRUE;
}

//PLACES THE SHIP IN THE BOARD
void placeShip(Player *player, int DIM, int i, int x, int y)
{
    int xaux = x - 3;
    int yaux = y - 3;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            if (player->ship[i].bitmap[j][k] == SHIP)
            {
                player->board[yaux][xaux].symbol = player->ship[i].bitmap[j][k];
                player->board[yaux][xaux].ship = &player->ship[i];
            }
            xaux++;
        }
        yaux++;
        xaux = x - 3;
    }
}

//MANUALLY PLACES THE SHIPS IN THE BOARD OF THE PLAYER GIVEN AS ARGUMENT
void manuallyPlaceShips(Player *player, int DIM, int NUM_SHIPS)
{
    int x, y, input;
    for (int i = 0; i < NUM_SHIPS; i++)
    {
        printBoard(player->board, DIM);
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
void randomlyPlaceShips(Player *player, int DIM, int NUM_SHIPS)
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
            printEnemyBoard(player2->board, DIM);
            printBoard(player1->board, DIM);
            printf("You MISSED!\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            break;

        case SHIP:
            player2->board[y - 1][x - 1].symbol = HIT;
            player2->board[y - 1][x - 1].ship->hitpoints--;
            player2->hitpoints--;

            system("clear");
            printEnemyBoard(player2->board, DIM);
            printBoard(player1->board, DIM);
            if (player2->board[y - 1][x - 1].ship->hitpoints <= 0)
                printf("You destroyed the enemy's %s!\n", player2->board[y - 1][x - 1].ship->name);
            else
                printf("You HIT an enemy's ship!\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            break;

        default:
            system("clear");
            printEnemyBoard(player2->board, DIM);
            printBoard(player1->board, DIM);
            printf("INVALID PLAY!\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            break;
        }
    }
    if (*turn == 1)
        *turn = 2;
    else
        *turn = 1;
}