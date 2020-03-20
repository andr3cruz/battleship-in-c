/* MAIN FUNCTION OF THE BATTLESHIP GAME */

#include "battleship.h"

int main(void)
{
    int input;                                                         // navigation auxiliary variable
    int DIM;                                                           // dimension of board
    int CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS; // individual and total ship counts
    int turn = 1;                                                      // variable that determines whose turn it is, can take values 1 or 2
    Cell **playerOneBoard;                                             //board of player 1
    Cell **playerTwoBoard;                                             //board of player 2
    Ship *watership1;                                                  // array of ships of player 1
    Ship *watership2;                                                  // array of ships of player 2
    Player player1;                                                    // player 1 struct
    Player player2;                                                    // player 2 struct

    // DISPLAYS THE FIRST TEXT SCREEN
    startScreen();

    //GETS THE DIMENSION OF THE BOARD
    printf("Choose dimension of board\n");
    scanf("%d", &DIM);

    // DINAMICALLY ALLOCATES MEMORY FOR EACH PLAYER BOARD
    playerOneBoard = malloc(DIM * sizeof(Cell *));
    playerTwoBoard = malloc(DIM * sizeof(Cell *));

    for (int i = 0; i < DIM; i++)
    {
        playerOneBoard[i] = malloc(DIM * sizeof(Cell));
        playerTwoBoard[i] = malloc(DIM * sizeof(Cell));
    }

    // INITIALIZES THE BOARDS

    initializeBoard(DIM, playerOneBoard);
    initializeBoard(DIM, playerTwoBoard);

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
    system("clear");
    NUM_SHIPS = CARRIER + BATTLESHIP + CRUISER + SUBMARINE + DESTROYER;

    // DINAMICALLY ALLOCATES MEMORY FOR EACH SHIP
    watership1 = (Ship *)malloc(NUM_SHIPS * sizeof(Ship));
    watership2 = (Ship *)malloc(NUM_SHIPS * sizeof(Ship));

    // INITIALIZES THE SHIPS
    initializeShips(watership1, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS);
    initializeShips(watership2, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS);

    //ASSIGN EACH PLAYER HIS BOARDS, SHIP AND HITPOINTS
    player1.hitpoints = CARRIER * 5 + BATTLESHIP * 4 + CRUISER * 3 + SUBMARINE * 3 + DESTROYER * 2;
    player2.hitpoints = CARRIER * 5 + BATTLESHIP * 4 + CRUISER * 3 + SUBMARINE * 3 + DESTROYER * 2;
    player1.board = playerOneBoard;
    player2.board = playerTwoBoard;
    player1.ship = watership1;
    player2.ship = watership2;

    //CHECKS IF SHIPS CAN FIT ON THE BOARD
    if (player1.hitpoints >= DIM * DIM)
    {
        printf("ERROR: Ships don't fit on board size given\n");
        return 1;
    }

    //CHOOSE SHIP PLACEMENT MODE
    printf("1) Place ships MANUALLY\n");
    printf("2) Place ships RANDOMLY\n");
    scanf("%d", &input);
    getchar();
    system("clear");

    switch (input)
    {
    case 1: //PLACES THE SHIPS MANUALLY
        manuallyPlaceShips(DIM, NUM_SHIPS, player1);
        manuallyPlaceShips(DIM, NUM_SHIPS, player2);
        break;
    case 2: //PLACES THE SHIPS RANDOMLY
        randomlyPlaceShips(DIM, NUM_SHIPS, player1);
        randomlyPlaceShips(DIM, NUM_SHIPS, player2);
        break;
    default:
        break;
    }

    //CHANGES TURNS BETWEEN PLAYERS
    while (player1.hitpoints > 0 && player2.hitpoints > 0)
    {
        if (turn == 1) //PLAYER 1 TURN
        {
            printf("%d\n", player1.hitpoints);
            printf("WAITING FOR PLAYER 1\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            printEnemyBoard(DIM, player2.board);
            printBoard(DIM, player1.board);
            printf("Player 1's turn!\n");
            play(player1, player2, DIM, &turn);
        }
        else if (turn == 2) //PLAYER 2 TURN
        {
            printf("WAITING FOR PLAYER 2\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            printEnemyBoard(DIM, player1.board);
            printBoard(DIM, player2.board);
            printf("Player 2's turn!\n");
            play(player2, player1, DIM, &turn);
        }
    }

    //ENDGAME CONDITIONS
    if (player1.hitpoints <= 0) //PLAYER 2 WINS
    {
        system("clear");
        printf("CONGRATULATIONS, PLAYER 2 WINS!\n");
        printf("Press <ENTER> to end program!");
        getchar();
    }
    else if (player2.hitpoints <= 0) //PLAYER 1 WINS
    {
        system("clear");
        printf("CONGRATULATIONS, PLAYER 1 WINS!\n");
        printf("Press <ENTER> to end program!");
        getchar();
    }

    return 0;
}