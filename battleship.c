/* FILE THAT CONTAINS THE FUNCTION CODE OF THE PROTOTYPES LISTED IN BATTLESHIP.H*/

#include "battleship.h"

//PRINTS THE INITIAL SCREEN
void startScreen(void)
{
    system("clear");
    printf("Welcome to Battleship in C!\n");
}

//PRINTS THE SHIP BITMAP
void printShip(Ship *ship, int i)
{
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            printf("%c ", ship[i].bitmap[j][k]);
        }
        putchar('\n');
    }
    putchar('\n');
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
            watership[i].hitpoints = 5;
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

//ROTATES SHIP BITMAP RIGHT
void rotateRight(Ship *ship, int i)
{
    char bitmap[5][5];
    int aux = 4;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            bitmap[k][aux] = ship[i].bitmap[j][k];
        }
        aux--;
    }

    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            ship[i].bitmap[j][k] = bitmap[j][k];
        }
    }
}

//ROTATES SHIP BITMAP LEFT
void rotateLeft(Ship *ship, int i)
{
    char bitmap[5][5];
    int aux = 4;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            bitmap[aux - k][j] = ship[i].bitmap[j][k];
        }
    }

    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            ship[i].bitmap[j][k] = bitmap[j][k];
        }
    }
}