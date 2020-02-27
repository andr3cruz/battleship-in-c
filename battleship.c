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

Boolean impossiblePlay(Player player, int ROWS, int COLS, int i, int x, int y)
{
    if ((player.ship[i].hitpoints > y || (checkSpotsUp(player, i, x, y) == FALSE)) &&
        ((player.ship[i].hitpoints > ROWS - y + 1) || (checkSpotsDown(player, i, x, y) == FALSE)) &&
        (player.ship[i].hitpoints > x || (checkSpotsLeft(player, i, x, y) == FALSE)) &&
        ((player.ship[i].hitpoints > COLS - x + 1) || (checkSpotsRight(player, i, x, y) == FALSE)))
        return TRUE;
    return FALSE;
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
        if ((player.board[y - 1][x - 1].symbol != WATER) || (impossiblePlay(player, ROWS, COLS, i, x, y) == TRUE))
        {
            printf("%s", "Invalid operation\n");
            i--;
        }
        else
        {
            player.board[y - 1][x - 1].symbol = HIT;
            player.board[y - 1][x - 1].ship = player.ship[i];
            printBoard(ROWS, COLS, player);
            printf("Place it:\n");
            if (player.ship[i].hitpoints <= y && (checkSpotsUp(player, i, x, y) == TRUE))
                printf("1) UP\n");
            if ((player.ship[i].hitpoints <= ROWS - y + 1) && (checkSpotsDown(player, i, x, y) == TRUE))
                printf("2) DOWN\n");
            if (player.ship[i].hitpoints <= x && (checkSpotsLeft(player, i, x, y) == TRUE))
                printf("3) LEFT\n");
            if ((player.ship[i].hitpoints <= COLS - x + 1) && (checkSpotsRight(player, i, x, y) == TRUE))
                printf("4) RIGHT\n");
            scanf("%d", &input);
            switch (input)
            {
            case 1:
                for (int j = 0; j < player.ship[i].hitpoints - 1; j++)
                {
                    player.board[y - 2][x - 1].symbol = HIT;
                    player.board[y - 2][x - 1].ship = player.ship[i];
                    y--;
                }
                break;
            case 2:
                for (int j = 0; j < player.ship[i].hitpoints - 1; j++)
                {
                    player.board[y][x - 1].symbol = HIT;
                    player.board[y][x - 1].ship = player.ship[i];
                    y++;
                }
                break;
            case 3:
                for (int j = 0; j < player.ship[i].hitpoints - 1; j++)
                {
                    player.board[y - 1][x - 2].symbol = HIT;
                    player.board[y - 1][x - 2].ship = player.ship[i];
                    x--;
                }
                break;
            case 4:
                for (int j = 0; j < player.ship[i].hitpoints - 1; j++)
                {
                    player.board[y - 1][x].symbol = HIT;
                    player.board[y - 1][x].ship = player.ship[i];
                    x++;
                }
                break;
            default:
                break;
            }
        }
    }
}