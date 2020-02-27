#include "battleship.h"

int main(void)
{
    int input, ROWS, COLS, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS;
    Cell **playerOneBoard;
    Cell **playerTwoBoard;
    Ship *watership1;
    Ship *watership2;
    Player player1;
    Player player2;

    // DISPLAYS THE FIRST TEXT SCREEN
    startScreen();
    //GETS THE NUMBER OF ROWS AND COLUMNS FOR THE BOARDS
    printf("Choose number of rows on board\n");
    scanf("%d", &ROWS);
    printf("Choose number of columns on board\n");
    scanf("%d", &COLS);

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

    // GETS HOW MANY SHIPS OF EACH KIND TO CREATE
    printf("Choose number of Carriers\n");
    scanf("%d", &CARRIER);
    printf("Choose number of Battleships\n");
    scanf("%d", &BATTLESHIP);
    printf("Choose number of Cruisers\n");
    scanf("%d", &CRUISER);
    printf("Choose number of Submarines\n");
    scanf("%d", &SUBMARINE);
    printf("Choose number of Destroyers\n");
    scanf("%d", &DESTROYER);
    NUM_SHIPS = CARRIER + BATTLESHIP + CRUISER + SUBMARINE + DESTROYER;

    // DINAMICALLY ALLOCATES MEMORY FOR EACH SHIP
    watership1 = (Ship *)malloc(NUM_SHIPS * sizeof(Ship));
    watership2 = (Ship *)malloc(NUM_SHIPS * sizeof(Ship));

    // INITIALIZES THE SHIPS
    initializeShips(watership1, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS);
    initializeShips(watership2, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS);

    //ASSIGN EACH PLAYER HIS BOARD, SHIP AND HITPOINTS
    player1.hitpoints = CARRIER * 5 + BATTLESHIP * 4 + CRUISER * 3 + SUBMARINE * 3 + DESTROYER * 2;
    player2.hitpoints = CARRIER * 5 + BATTLESHIP * 4 + CRUISER * 3 + SUBMARINE * 3 + DESTROYER * 2;
    player1.board = playerOneBoard;
    player2.board = playerTwoBoard;
    player1.ship = watership1;
    player2.ship = watership2;

    //CHECKS IF SHIPS CAN FIT ON THE BOARD
    if (player1.hitpoints >= ROWS * COLS)
    {
        printf("ERROR: Ships don't fit on board size given\n");
        return 1;
    }

    //CHOOSE SHIP PLACEMENT MODE
    printf("1) Place ships MANUALLY\n");
    printf("2) Place ships RANDOMLY\n");
    scanf("%d", &input);
    system("clear");

    switch (input)
    {
    case 1:
        manuallyPlaceShips(ROWS, COLS, NUM_SHIPS, player1);
        manuallyPlaceShips(ROWS, COLS, NUM_SHIPS, player2);
        break;
    case 2:
        randomlyPlaceShips(ROWS, COLS, NUM_SHIPS, player1);
        randomlyPlaceShips(ROWS, COLS, NUM_SHIPS, player2);
        break;
    default:
        break;
    }

    printBoard(ROWS, COLS, player1);
    printBoard(ROWS, COLS, player2);

    // RESETS SYMBOLS TO WATER
    initializeBoard(ROWS, COLS, player1.board);
    initializeBoard(ROWS, COLS, player2.board);

    return 0;
}
