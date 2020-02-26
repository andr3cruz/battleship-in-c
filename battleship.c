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
    int CARRIER_TEMP = CARRIER;
    int BATTLESHIP_TEMP = BATTLESHIP;
    int CRUISER_TEMP = CRUISER;
    int SUBMARINE_TEMP = SUBMARINE;
    int DESTROYER_TEMP = DESTROYER;

    for (int i = 0; i < NUM_SHIPS; i++) // PLAYER 1 SHIPS
    {
        if (CARRIER_TEMP > 0)
        {
            watership[i].hitpoints = 5;
            watership[i].name = "Carrier";
            watership[i].player = 1;
            CARRIER_TEMP--;
        }
        else if (BATTLESHIP_TEMP > 0)
        {
            watership[i].hitpoints = 4;
            watership[i].name = "Battleship";
            watership[i].player = 1;
            BATTLESHIP_TEMP--;
        }
        else if (CRUISER_TEMP > 0)
        {
            watership[i].hitpoints = 3;
            watership[i].name = "Cruiser";
            watership[i].player = 1;
            CRUISER_TEMP--;
        }
        else if (SUBMARINE_TEMP > 0)
        {
            watership[i].hitpoints = 3;
            watership[i].name = "Submarine";
            watership[i].player = 1;
            SUBMARINE_TEMP--;
        }
        else if (DESTROYER_TEMP > 0)
        {
            watership[i].hitpoints = 2;
            watership[i].name = "Destroyer";
            watership[i].player = 1;
            DESTROYER_TEMP--;
        }
    }

    CARRIER_TEMP = CARRIER;
    BATTLESHIP_TEMP = BATTLESHIP;
    CRUISER_TEMP = CRUISER;
    SUBMARINE_TEMP = SUBMARINE;
    DESTROYER_TEMP = DESTROYER;

    for (int i = NUM_SHIPS; i < NUM_SHIPS * 2; i++) // PLAYER 2 SHIPS
    {
        if (CARRIER_TEMP > 0)
        {
            watership[i].hitpoints = 5;
            watership[i].name = "Carrier";
            watership[i].player = 2;
            CARRIER_TEMP--;
        }
        else if (BATTLESHIP_TEMP > 0)
        {
            watership[i].hitpoints = 4;
            watership[i].name = "Battleship";
            watership[i].player = 2;
            BATTLESHIP_TEMP--;
        }
        else if (CRUISER_TEMP > 0)
        {
            watership[i].hitpoints = 3;
            watership[i].name = "Cruiser";
            watership[i].player = 2;
            CRUISER_TEMP--;
        }
        else if (SUBMARINE_TEMP > 0)
        {
            watership[i].hitpoints = 3;
            watership[i].name = "Submarine";
            watership[i].player = 2;
            SUBMARINE_TEMP--;
        }
        else if (DESTROYER_TEMP > 0)
        {
            watership[i].hitpoints = 2;
            watership[i].name = "Destroyer";
            watership[i].player = 2;
            DESTROYER_TEMP--;
        }
    }
}
