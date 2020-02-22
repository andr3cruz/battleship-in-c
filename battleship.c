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

void printBoard(int ROWS, int COLS, Cell **board)
{
    for (int i = 0; i < ROWS; i++)
    {

        for (int j = 0; j < COLS; j++)
        {
            printf(" %c ", board[i][j].symbol);
        }
        putchar('\n');
    }
    putchar('\n');
}