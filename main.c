#include "battleship.h"

int main(void)
{
    int ROWS, COLS, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS;
    Cell **playerOneBoard;
    Cell **playerTwoBoard;
    Ship *watership;

    // DISPLAYS THE FIRST TEXT SCREEN
    startScreen();

    //GETS THE NUMBER OF ROWS AND COLUMNS FOR THE BOARDS
    printf("Choose number of rows on board\n");
    scanf("%d", &ROWS);
    printf("Choose number of columns on board\n");
    scanf("%d", &COLS);
    /*
    getchar();       // CLEANS BUFFER
    system("clear"); // CLEARS THE TERMINAL (ctrl + l)
    */

    // DINAMICALLY ALLOCATES MEMORY FOR EACH PLAYER BOARD
    playerOneBoard = malloc(ROWS * sizeof(Cell *));
    playerTwoBoard = malloc(ROWS * sizeof(Cell *));

    for (int i = 0; i < ROWS; i++)
    {
        playerOneBoard[i] = malloc(COLS * sizeof(Cell));
        playerTwoBoard[i] = malloc(COLS * sizeof(Cell));
    }

    // INITIALIZES THE BOARDS

    initializeBoard(ROWS, COLS, playerOneBoard);
    initializeBoard(ROWS, COLS, playerTwoBoard);

    /*printBoard(ROWS, COLS, playerTwoBoard);
    printBoard(ROWS, COLS, playerOneBoard);
    printf("Press <ENTER> to continue!");
    getchar();
    system("clear"); */

    // GETS HOW MANY SHIPS OF EACH KIND TO CREATE
    scanf("%d", &CARRIER);
    scanf("%d", &BATTLESHIP);
    scanf("%d", &CRUISER);
    scanf("%d", &SUBMARINE);
    scanf("%d", &DESTROYER);
    NUM_SHIPS = CARRIER + BATTLESHIP + CRUISER + SUBMARINE + DESTROYER;

    // DINAMICALLY ALLOCATES MEMORY FOR EACH SHIP
    watership = (Ship *)malloc(NUM_SHIPS * 2 * sizeof(Ship));

    // INITIALIZES THE SHIPS
    initializeShips(watership, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS);

    for (int i = 0; i < NUM_SHIPS * 2; i++)
    {
        printf("%d\n", watership[i].hitpoints);
        printf("%s\n", watership[i].name);
        printf("%d\n\n", watership[i].player);
    }

    return 0;
}
