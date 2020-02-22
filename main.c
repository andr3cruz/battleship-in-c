#include "battleship.h"

int main(void)
{
    int ROWS, COLS;
    Cell **playerOneBoard;
    Cell **playerTwoBoard;

    startScreen();
    printf("Choose number of rows on board\n");
    scanf("%d", &ROWS);
    printf("Choose number of columns on board\n");
    scanf("%d", &COLS);

    playerOneBoard = malloc(ROWS * sizeof(Cell *));
    playerTwoBoard = malloc(ROWS * sizeof(Cell *));

    for (int i = 0; i < ROWS; i++)
    {
        playerOneBoard[i] = malloc(COLS * sizeof(Cell));
        playerTwoBoard[i] = malloc(COLS * sizeof(Cell));
    }

    initializeBoard(ROWS, COLS, playerOneBoard);
    initializeBoard(ROWS, COLS, playerTwoBoard);
    printBoard(ROWS, COLS, playerOneBoard);
    printBoard(ROWS, COLS, playerTwoBoard);
    return 0;
}
