#include "battleship.h"

void startScreen(void)
{
    printf("Welcome to Battleship in C!\n");
}

void initializeBoard(int ROWS, int COLS, Cell **board)
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            board[i][j].symbol = WATER;
            board[i][j].row = i;
            board[i][j].column = j;
        }
}

void printBoard(int ROWS, int COLS, Player player)
{
    for (int i = 0; i < ROWS; i++)
    {

        for (int j = 0; j < COLS; j++)
        {
            printf(" %c ", player.board[i][j].symbol);
        }
        putchar('\n');
    }
    putchar('\n');
}

void initializeShips(Ship *watership, int CARRIER, int BATTLESHIP, int CRUISER, int SUBMARINE, int DESTROYER, int NUM_SHIPS)
{
    for (int i = 0; i < NUM_SHIPS; i++) // PLAYER 1 SHIPS
    {
        if (CARRIER > 0)
        {
            watership[i].hitpoints = 5;
            watership[i].name = "Carrier";
            CARRIER--;
        }
        else if (BATTLESHIP > 0)
        {
            watership[i].hitpoints = 4;
            watership[i].name = "Battleship";
            BATTLESHIP--;
        }
        else if (CRUISER > 0)
        {
            watership[i].hitpoints = 3;
            watership[i].name = "Cruiser";
            CRUISER--;
        }
        else if (SUBMARINE > 0)
        {
            watership[i].hitpoints = 3;
            watership[i].name = "Submarine";
            SUBMARINE--;
        }
        else if (DESTROYER > 0)
        {
            watership[i].hitpoints = 2;
            watership[i].name = "Destroyer";
            DESTROYER--;
        }
    }
}

Boolean checkSpotsUp(Player player, int i, int x, int y)
{
    for (int j = 0; j < player.ship[i].hitpoints - 1; j++)
    {
        if (player.board[y - 2][x - 1].symbol != WATER)
            return FALSE;
        y--;
    }
    return TRUE;
}

Boolean checkSpotsDown(Player player, int i, int x, int y)
{
    for (int j = 0; j < player.ship[i].hitpoints - 1; j++)
    {
        if (player.board[y][x - 1].symbol != WATER)
            return FALSE;
        y++;
    }
    return TRUE;
}

Boolean checkSpotsLeft(Player player, int i, int x, int y)
{
    for (int j = 0; j < player.ship[i].hitpoints - 1; j++)
    {
        if (player.board[y - 1][x - 2].symbol != WATER)
            return FALSE;
        x--;
    }
    return TRUE;
}

Boolean checkSpotsRight(Player player, int i, int x, int y)
{
    for (int j = 0; j < player.ship[i].hitpoints - 1; j++)
    {
        if (player.board[y - 1][x].symbol != WATER)
            return FALSE;
        x++;
    }
    return TRUE;
}

void manuallyPlaceShips(int ROWS, int COLS, int NUM_SHIPS, Player player)
{
    int x, y, input;
    for (int i = 0; i < NUM_SHIPS; i++)
    {
        printBoard(ROWS, COLS, player);
        printf("Type the numerical coordinate X of where you want to place your ship");
        scanf("%d", &x);
        printf("Type the numerical coordinate Y of where you want to place your ship");
        scanf("%d", &y);
        player.board[y - 1][x - 1].symbol = HIT;
        printBoard(ROWS, COLS, player);
        printf("Place it:\n");
        if (player.ship[0].hitpoints <= y && (checkSpotsUp(player, 0, x, y) == TRUE))
            printf("1) UP\n");
        if ((player.ship[0].hitpoints <= ROWS - y + 1) && (checkSpotsDown(player, 0, x, y) == TRUE))
            printf("2) DOWN\n");
        if (player.ship[0].hitpoints <= x && (checkSpotsLeft(player, 0, x, y) == TRUE))
            printf("3) LEFT\n");
        if ((player.ship[0].hitpoints <= COLS - x + 1) && (checkSpotsRight(player, 0, x, y) == TRUE))
            printf("4) RIGHT\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        default:
            break;
        }
    }
}