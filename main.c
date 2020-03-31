/* MAIN FUNCTION OF THE BATTLESHIP GAME */

#include "battleship.h"

int main(void)
{
    int input;                                                         //navigation auxiliary variable
    int DIM;                                                           //dimension of board
    int CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS; //individual and total ship counts
    int turn;                                                          //variable that determines whose turn it is, can take values 1 or 2
    Player player1;                                                    //player 1 struct
    Player player2;                                                    //player 2 struct

    //DISPLAYS THE FIRST TEXT SCREEN
    startScreen();

    //GETS THE DIMENSION OF THE BOARD
    printf("Choose dimension of board\n");
    scanf("%d", &DIM);

    //GETS HOW MANY SHIPS OF EACH KIND TO CREATE AND VERIFIES CONDITIONS
    printf("Choose number of Carriers: (minimum 1)\n");
    scanf("%d", &CARRIER);
    if (CARRIER < 1)
    {
        printf("ERROR: Invalid number of ships\n");
        return 0;
    }
    printf("Choose number of Battleships: (minimum 1)\n");
    scanf("%d", &BATTLESHIP);
    if (BATTLESHIP < 1)
    {
        printf("ERROR: Invalid number of ships\n");
        return 0;
    }
    printf("Choose number of Cruisers: (minimum 1)\n");
    scanf("%d", &CRUISER);
    if (CRUISER < 1)
    {
        printf("ERROR: Invalid number of ships\n");
        return 0;
    }
    printf("Choose number of Submarines: (minimum 1)\n");
    scanf("%d", &SUBMARINE);
    if (SUBMARINE < 1)
    {
        printf("ERROR: Invalid number of ships\n");
        return 0;
    }
    printf("Choose number of Destroyers: (minimum 1)\n");
    scanf("%d", &DESTROYER);
    if (DESTROYER < 1)
    {
        printf("ERROR: Invalid number of ships\n");
        return 0;
    }
    system("clear");

    //SAVES TOTAL NUMBER OF SHIPS
    NUM_SHIPS = CARRIER + BATTLESHIP + CRUISER + SUBMARINE + DESTROYER;

    //INITIALIZES EACH PLAYER
    initializePlayers(&player1, DIM, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS);
    initializePlayers(&player2, DIM, CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, NUM_SHIPS);

    //CHECKS IF SHIPS CAN FIT ON THE BOARD
    if (NUM_SHIPS > (DIM * DIM) / (5 * 5))
    {
        printf("ERROR: Max number of ships is %d for the board size given and you selected %d\n", ((DIM * DIM) / (5 * 5)), NUM_SHIPS);
        return 0;
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

    //RANDOMLY SELECTS A PLAYER TO START
    srandom(time(NULL));
    turn = random() % 2 + 1;

    //CHANGES TURNS BETWEEN PLAYERS
    while (player1.hitpoints > 0 && player2.hitpoints > 0)
    {
        if (turn == 1) //PLAYER 1 TURN
        {
            printf("WAITING FOR PLAYER 1\n");
            printf("Press <ENTER> to continue!");
            getchar();
            system("clear");
            printEnemyBoard(DIM, player2.board);
            printBoard(DIM, player1.board);
            printf("Player 1's turn!\n");
            play(&player1, &player2, DIM, &turn);
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
            play(&player2, &player1, DIM, &turn);
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

    //FREE THE ALLOCATED SPACE FOR EACH PLAYER
    free(player1.board);
    free(player2.board);
    free(player1.ship);
    free(player2.ship);

    return 0;
}
