#include "battleship.h"

int main(void)
{
    int ROWS, COLS;
    Cell **playerOneBoard;
    Cell **playerTwoBoard;

    scanf("%d", &ROWS);
    scanf("%d", &COLS);

    playerOneBoard = malloc(ROWS * sizeof(Cell *));
    playerTwoBoard = malloc(ROWS * sizeof(Cell *));

    for (int i = 0; i < ROWS; i++)
    {
        playerOneBoard[i] = malloc(COLS * sizeof(Cell));
        playerTwoBoard[i] = malloc(COLS * sizeof(Cell));
    }

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            playerOneBoard[i][j].symbol = WATER;
            playerOneBoard[i][j].row = i;
            playerOneBoard[i][j].column = j;
            playerTwoBoard[i][j].symbol = WATER;
            playerTwoBoard[i][j].row = i;
            playerTwoBoard[i][j].column = j;
            if (j == COLS - 1)
            {
                printf("(%d,%d)\n", playerOneBoard[i][j].row, playerOneBoard[i][j].column);
            }
            else
                printf("(%d,%d)", playerOneBoard[i][j].row, playerOneBoard[i][j].column);
        }
    /*
    initializeBoard(playerOneBoard);
    initializeBoard(playerOneBoard);
    */
}
