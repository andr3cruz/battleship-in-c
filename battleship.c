#include "battleship.h"

void startScreen(void)
{
    system("clear");
    printf("Welcome to Battleship in C!\n\n");
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

void printBoard(int ROWS, int COLS, Cell **board)
{
    for (int i = 0; i < ROWS; i++)
    {

        for (int j = 0; j < COLS; j++)
        {
            printf("%c ", board[i][j].symbol);
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
        printBoard(ROWS, COLS, player.board);
        printf("Type the numerical coordinate X of where you want to place your ship\n");
        scanf("%d", &x);
        getchar();
        printf("Type the numerical coordinate Y of where you want to place your ship\n");
        scanf("%d", &y);
        getchar();
        if ((y > ROWS) || (x > COLS) || (x <= 0) || (y <= 0) || (player.board[y - 1][x - 1].symbol != WATER) || (impossiblePlay(player, ROWS, COLS, i, x, y) == TRUE))
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
            player.board[y - 1][x - 1].symbol = 'O';
            printBoard(ROWS, COLS, player.board);
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
            getchar();
            switch (input)
            {
            case 1:
                if (player.ship[i].hitpoints <= y && (checkSpotsUp(player, i, x, y) == TRUE))
                {
                    for (int j = 0; j < player.ship[i].hitpoints; j++)
                    {
                        player.board[y - 1][x - 1].symbol = 'O';
                        player.board[y - 1][x - 1].ship = i;
                        y--;
                    }
                }
                else
                {
                    player.board[y - 1][x - 1].symbol = WATER;
                    i--;
                    printf("Invalid operation\n");
                    printf("Press <ENTER> to continue!");
                    getchar();
                    system("clear");
                }
                break;
            case 2:
                if ((player.ship[i].hitpoints <= ROWS - y + 1) && (checkSpotsDown(player, i, x, y) == TRUE))
                {

                    for (int j = 0; j < player.ship[i].hitpoints; j++)
                    {
                        player.board[y - 1][x - 1].symbol = 'O';
                        player.board[y - 1][x - 1].ship = i;
                        y++;
                    }
                }
                else
                {
                    player.board[y - 1][x - 1].symbol = WATER;
                    i--;
                    printf("Invalid operation\n");
                    printf("Press <ENTER> to continue!");
                    getchar();
                    system("clear");
                }
                break;

            case 3:
                if (player.ship[i].hitpoints <= x && (checkSpotsLeft(player, i, x, y) == TRUE))
                {
                    for (int j = 0; j < player.ship[i].hitpoints; j++)
                    {
                        player.board[y - 1][x - 1].symbol = 'O';
                        player.board[y - 1][x - 1].ship = i;
                        x--;
                    }
                }
                else
                {
                    player.board[y - 1][x - 1].symbol = WATER;
                    i--;
                    printf("Invalid operation\n");
                    printf("Press <ENTER> to continue!");
                    getchar();
                    system("clear");
                }
                break;
            case 4:
                if ((player.ship[i].hitpoints <= COLS - x + 1) && (checkSpotsRight(player, i, x, y) == TRUE))
                {
                    for (int j = 0; j < player.ship[i].hitpoints; j++)
                    {
                        player.board[y - 1][x - 1].symbol = 'O';
                        player.board[y - 1][x - 1].ship = i;
                        x++;
                    }
                }
                else
                {
                    player.board[y - 1][x - 1].symbol = WATER;
                    i--;
                    printf("Invalid operation\n");
                    printf("Press <ENTER> to continue!");
                    getchar();
                    system("clear");
                }
                break;
            default:
                player.board[y - 1][x - 1].symbol = WATER;
                i--;
                printf("Invalid operation\n");
                printf("Press <ENTER> to continue!");
                getchar();
                system("clear");
                break;
            }
            system("clear");
        }
    }
}

void randomlyPlaceShips(int ROWS, int COLS, int NUM_SHIPS, Player player)
{
    int x, y;
    for (int i = 0; i < NUM_SHIPS; i++)
    {
        srandom(clock());
        int x = random() % COLS + 1;
        int y = random() % ROWS + 1;
        int option = random() % 4 + 1;
        if ((player.board[y - 1][x - 1].symbol != WATER) || (impossiblePlay(player, ROWS, COLS, i, x, y) == TRUE))
        {
            i--;
        }
        else
        {
            switch (option)
            {
            case 1:
                if (player.ship[i].hitpoints <= y && (checkSpotsUp(player, i, x, y) == TRUE))
                {
                    for (int j = 0; j < player.ship[i].hitpoints; j++)
                    {
                        player.board[y - 1][x - 1].symbol = 'O';
                        player.board[y - 1][x - 1].ship = i;
                        y--;
                    }
                }
                else
                {
                    i--;
                }
                break;
            case 2:
                if ((player.ship[i].hitpoints <= ROWS - y + 1) && (checkSpotsDown(player, i, x, y) == TRUE))
                {

                    for (int j = 0; j < player.ship[i].hitpoints; j++)
                    {
                        player.board[y - 1][x - 1].symbol = 'O';
                        player.board[y - 1][x - 1].ship = i;
                        y++;
                    }
                }
                else
                {
                    i--;
                }
                break;

            case 3:
                if (player.ship[i].hitpoints <= x && (checkSpotsLeft(player, i, x, y) == TRUE))
                {
                    for (int j = 0; j < player.ship[i].hitpoints; j++)
                    {
                        player.board[y - 1][x - 1].symbol = 'O';
                        player.board[y - 1][x - 1].ship = i;
                        x--;
                    }
                }
                else
                {
                    i--;
                }
                break;
            case 4:
                if ((player.ship[i].hitpoints <= COLS - x + 1) && (checkSpotsRight(player, i, x, y) == TRUE))
                {
                    for (int j = 0; j < player.ship[i].hitpoints; j++)
                    {
                        player.board[y - 1][x - 1].symbol = 'O';
                        player.board[y - 1][x - 1].ship = i;
                        x++;
                    }
                }
                else
                {
                    i--;
                }
                break;
            default:
                break;
            }
            system("clear");
        }
    }
}

void play(Player player1, Player player2, int ROWS, int COLS, int *turn)
{
    int x, y;
    printf("Type the numerical coordinate X of where you want to ATTACK\n");
    scanf("%d", &x);
    getchar();
    printf("Type the numerical coordinate Y of where you want to ATTACK\n");
    scanf("%d", &y);
    getchar();
    if (y > ROWS || x > COLS)
    {
        printf("Invalid operation\n");
        printf("Press <ENTER> to continue!");
        getchar();
        system("clear");
    }
    else
    {
        int i = player2.board[y - 1][x - 1].ship;

        switch (player2.board[y - 1][x - 1].symbol)
        {
        case WATER:
            player2.board[y - 1][x - 1].symbol = MISS;
            player1.auxboard[y - 1][x - 1].symbol = MISS;
            system("clear");
            printBoard(ROWS, COLS, player1.auxboard);
            printBoard(ROWS, COLS, player1.board);
            printf("You MISSED!\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            if (*turn == 1)
                *turn = 2;
            else
                *turn = 1;
            break;

        case 'O':
            player2.board[y - 1][x - 1].symbol = HIT;
            player1.auxboard[y - 1][x - 1].symbol = HIT;
            player2.ship[i].hitpoints--;
            player2.hitpoints--;
            if (player2.ship[i].hitpoints <= 0)
            {
                system("clear");
                printBoard(ROWS, COLS, player1.auxboard);
                printBoard(ROWS, COLS, player1.board);
                printf("You destroyed the enemy's %s!\n", player2.ship[i].name);
                printf("Press <ENTER> to continue!");
                getchar();
                system("clear");
            }
            else
            {
                system("clear");
                printBoard(ROWS, COLS, player1.auxboard);
                printBoard(ROWS, COLS, player1.board);
                printf("You HIT an enemy's ship!\n", player2.ship[i].hitpoints);
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
            printBoard(ROWS, COLS, player1.auxboard);
            printBoard(ROWS, COLS, player1.board);
            printf("INVALID PLAY!\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            break;
        }
    }
}