/* Program #6: Tic Tac Two
 *
 * Class:  CS 141, Fall 2015
 * Lab:    Nianzu Ma, Tuesday. 10:00 AM
 * System: Mac OS X, Qt Creator
 * Author: Usman Siddiqui
 *
 * 2 player game of Tic Tac Two where the players can move the 3x3 tic tac toe
 * grid around a bigger 5x5 board.
 *
 *  The start of the program should print out the following
 *
    Author: Joshua Evangelista
    Program 5: Tic Tac Two
    Lab: Nianzu Ma, Tuesday. 10:00 AM
    System:  Mac OS X, Qt Creator
    UIC CS 141, Novemenber 2015

     -------------------
    | .   .   .   .   . |   Pieces remaining for:
    |                   |      Player 1: A B C D
    | .   . | . | .   . |      Player 2: a b c d
    |     ---------     |
    | .   . | . | .   . |   Grid destination squares:
    |     ---------     |      1 2 3
    | .   . | . | .   . |      4 5 6
    |                   |      7 8 9
    | .   .   .   .   . |
     -------------------

    1. Player 1: Enter piece to move and destination number:

 * */

#include <iostream>
#include <cstdlib>      // for the system command
#include <cctype>       // For the letter checking functions, e.g. toupper( )
#include <fstream>      // For file input and output
#include <cstring>
#include <string.h>

using namespace std;

const int CENTER = 0;
const int LEFT   = 1;    // to reference the left wall character, such as in: theBoard[ i][ LEFT]
const int ABOVE  = 2;    // to reference the above wall character, such as in: theBoard[ i][ ABOVE]
const int RIGHT  = 3;    // to reference the right wall character, such as in: theBoard[ i][ RIGHT]
const int BELOW  = 4;    // to reference the below wall character, such as in: theBoard[ i][ BELOW]

const int START = 6;     // the starting point of the grid, 6 for the standard beginning

const int boardEdge = 5;
const int boardSize = boardEdge * boardEdge;


/* ------------------------------------------------
 * Displays the program and author information
 * at the start of the program
 *
 * No Parameters
 *
 * Does not return a value
 * ------------------------------------------------
*/
void displayIdInformation()
{
    // Display identifying information
    cout << "Author: Usman Siddiqui Program 5 credit goes to: Joshua Evangelista\n"
         << "Program 6: Tic Tac Two Undo\n"
         << "System:  Windows 8.1, Qt Creator\n"
         << "UIC CS 141, November 2015\n"
         << endl;
}//end displayIdInformation()


/* ------------------------------------------------
 * Creates the boards and their information
 *
 * it takes two char 2D arrays for the pieces and the grid
 *
 * Does not return a value
 * ------------------------------------------------
*/
void initializeBoard (char thePieces[][5], char theBoard[][5]) {

    int i = 0;
    for (i = 0; i < 25; i++) {

        // sets up the original items in the pieces array
        thePieces[i][CENTER] = '.';
        thePieces[i][LEFT]   = ' ';
        thePieces[i][ABOVE]  = ' ';
        thePieces[i][RIGHT]  = ' ';
        thePieces[i][BELOW]  = ' ';

        // sets up the original grid for the tic tac toe board (Nothing at this point)
        theBoard[i][CENTER] = ' ';
        theBoard[i][LEFT]   = ' ';
        theBoard[i][ABOVE]  = ' ';
        theBoard[i][RIGHT]  = ' ';
        theBoard[i][BELOW]  = ' ';

        // not used for display, used for board functions later
        // to keep the board form going off the edge of the grid
        if (i < 5) {

            theBoard[i][ABOVE] = '-';

        }
        if (i % 5 == 4) {

            theBoard[i][CENTER] = '|';
            theBoard[i][BELOW] = '|';

        }
        if (i >= 20) {

            theBoard[i][BELOW] = '-';

        }

    }

} //end initializeBoard(...)


/* ------------------------------------------------
 * Checks the grid for any win condition and
 * determines the winner and updates the winner int
 * and determines that the game is finished
 *
 * Takes a 2D char array, an int array, and 3 int varaibles
 *
 * Does not return a value
 * ------------------------------------------------
*/
typedef struct Node{// Linked list containing the destination the piece and next element
    int destination;
    char piece;
    int turn;
    Node* next;
}Node;

void winCheck (char thePieces[][5], int gridIndex[], int &turn, int &winner, int &finished) {

    int player1Win = 0;
    int player2Win = 0;

    // check if player 1 won
    if (isupper(thePieces[gridIndex[0]][CENTER]) && isupper(thePieces[gridIndex[1]][CENTER]) && isupper(thePieces[gridIndex[2]][CENTER])) {

        player1Win = 1;

    }
    if (isupper(thePieces[gridIndex[3]][CENTER]) && isupper(thePieces[gridIndex[4]][CENTER]) && isupper(thePieces[gridIndex[5]][CENTER])) {

        player1Win = 1;

    }
    if (isupper(thePieces[gridIndex[6]][CENTER]) && isupper(thePieces[gridIndex[7]][CENTER]) && isupper(thePieces[gridIndex[8]][CENTER])) {

        player1Win = 1;

    }
    if (isupper(thePieces[gridIndex[0]][CENTER]) && isupper(thePieces[gridIndex[3]][CENTER]) && isupper(thePieces[gridIndex[6]][CENTER])) {

        player1Win = 1;

    }
    if (isupper(thePieces[gridIndex[1]][CENTER]) && isupper(thePieces[gridIndex[4]][CENTER]) && isupper(thePieces[gridIndex[7]][CENTER])) {

        player1Win = 1;

    }
    if (isupper(thePieces[gridIndex[2]][CENTER]) && isupper(thePieces[gridIndex[5]][CENTER]) && isupper(thePieces[gridIndex[8]][CENTER])) {

        player1Win = 1;

    }
    if (isupper(thePieces[gridIndex[0]][CENTER]) && isupper(thePieces[gridIndex[4]][CENTER]) && isupper(thePieces[gridIndex[8]][CENTER])) {

        player1Win = 1;

    }
    if (isupper(thePieces[gridIndex[2]][CENTER]) && isupper(thePieces[gridIndex[4]][CENTER]) && isupper(thePieces[gridIndex[6]][CENTER])) {

        player1Win = 1;

    }

    // check if player 2 won
    if (islower(thePieces[gridIndex[0]][CENTER]) && islower(thePieces[gridIndex[1]][CENTER]) && islower(thePieces[gridIndex[2]][CENTER])) {

        player2Win = 1;

    }
    if (islower(thePieces[gridIndex[3]][CENTER]) && islower(thePieces[gridIndex[4]][CENTER]) && islower(thePieces[gridIndex[5]][CENTER])) {

        player2Win = 1;

    }
    if (islower(thePieces[gridIndex[6]][CENTER]) && islower(thePieces[gridIndex[7]][CENTER]) && islower(thePieces[gridIndex[8]][CENTER])) {

        player2Win = 1;

    }
    if (islower(thePieces[gridIndex[0]][CENTER]) && islower(thePieces[gridIndex[3]][CENTER]) && islower(thePieces[gridIndex[6]][CENTER])) {

        player2Win = 1;

    }
    if (islower(thePieces[gridIndex[1]][CENTER]) && islower(thePieces[gridIndex[4]][CENTER]) && islower(thePieces[gridIndex[7]][CENTER])) {

        player2Win = 1;

    }
    if (islower(thePieces[gridIndex[2]][CENTER]) && islower(thePieces[gridIndex[5]][CENTER]) && islower(thePieces[gridIndex[8]][CENTER])) {

        player2Win = 1;

    }
    if (islower(thePieces[gridIndex[0]][CENTER]) && islower(thePieces[gridIndex[4]][CENTER]) && islower(thePieces[gridIndex[8]][CENTER])) {

        player2Win = 1;

    }
    if (islower(thePieces[gridIndex[2]][CENTER]) && islower(thePieces[gridIndex[4]][CENTER]) && islower(thePieces[gridIndex[6]][CENTER])) {

        player2Win = 1;

    }


    //if both won, the player who's tur nit is wins
    if (player1Win == 1 && player2Win == 1) {

        winner = turn % 2 + 1;
        finished = 1;

    }
    else if (player1Win == 1) {

        winner = 1;
        finished = 1;

    }
    else if (player2Win == 1) {

        winner = 2;
        finished = 1;

    }

} // end winCheck(...)


/* ------------------------------------------------
 * Updates the game info that displays right of the board
 *
 * Takes 2 char 2D arrays
 *
 * Does not return a value
 * ------------------------------------------------
*/
void updateGameInfo (char gameInfo[][50], char gamePieces[][4]) {

    // for displaying pieces that the players can use
    strcpy(gameInfo[0], "Pieces remaining for:");

    // update the pieces usable for player 1
    strcpy(gameInfo[1], "   Player 1: ");
    gameInfo[1][13] = gamePieces[0][0];
    gameInfo[1][14] = ' ';
    gameInfo[1][15] = gamePieces[0][1];
    gameInfo[1][16] = ' ';
    gameInfo[1][17] = gamePieces[0][2];
    gameInfo[1][18] = ' ';
    gameInfo[1][19] = gamePieces[0][3];
    gameInfo[1][20] = '\0';

    // update the pieces usable for player 1
    strcpy(gameInfo[2], "   Player 2: ");
    gameInfo[2][13] = gamePieces[1][0];
    gameInfo[2][14] = ' ';
    gameInfo[2][15] = gamePieces[1][1];
    gameInfo[2][16] = ' ';
    gameInfo[2][17] = gamePieces[1][2];
    gameInfo[2][18] = ' ';
    gameInfo[2][19] = gamePieces[1][3];
    gameInfo[2][20] = '\0';

    // makes a new line
    gameInfo[3][0] = '\0';

    // displays the potential positions for the grid placements
    strcpy(gameInfo[4], "Grid destination squares:");
    strcpy(gameInfo[5], "   1 2 3");
    strcpy(gameInfo[6], "   4 5 6");
    strcpy(gameInfo[7], "   7 8 9");
    for(int i = 8; i < 50; i++){
        strcpy(gameInfo[i], "");
    }
} //end updateGameInfo(...)


/* ------------------------------------------------
 * Displays the the board the game info
 *
 * Takes 3 2D char arrrays
 *
 * Does not return a value
 * ------------------------------------------------
*/
void printBoard(char thePieces[][5], char theBoard[][5], char gameInfo[][50]) {

    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    // printing top of board
    printf(" ");
    for (i = 0; i < 19; i++) {

        printf("-");

    }
    printf("\n");

    // printing the pieces and board body
    for (i = 0; i < boardSize; i += boardEdge) {

        printf("| ");

        for (k = 0; k < boardEdge; k++) {
           printf("%c", thePieces[i + k][CENTER]);
           printf("%c", thePieces[i + k][LEFT]);
           if (k != boardEdge - 1) {
               printf("%c", theBoard[i + k][CENTER]);
               printf("%c", theBoard[i + k][LEFT]);
           }
        }
        printf("|");
        //prints out game information and rules from gameInfo array
        printf("   %s", gameInfo[l]);
        l++;
        printf("\n");
        // prints out the grid
        if (i < 20) {
            printf("|");
            for(j = 0; j < boardEdge; j++) {

                if ((thePieces[i + j - 1][BELOW] == '-' && theBoard[i + j - 1][BELOW] == '-')) {
                    printf("-");
                }
                else {

                    printf(" ");
                }

                printf("%c", thePieces[i + j][BELOW]);

                if ((thePieces[i + j][BELOW] == '-' && theBoard[i + j][BELOW] == '-')) {
                    printf("-");
                }
                else {

                    printf(" ");
                }
                printf("%c", theBoard[i + j][BELOW]);
            }
            //prints out game information and rules from gameInfo array
            printf("   %s", gameInfo[l]);
            l++;
            printf("\n");
        }


    }

    // printing bottom of board
    printf(" ");
    for (i = 0; i < 19; i++) {

        printf("-");

    }
    printf("\n");

} // end printBoard()


/* ------------------------------------------------
 * Updates the locations on the board that the
 * grid corresponds
 *
 * Takes the gridIndex array, an int array
 *
 * Does not return a value
 * ------------------------------------------------
*/
void updateIndex(int gridIndex[]) {

    gridIndex[1] = gridIndex[0] + 1;
    gridIndex[2] = gridIndex[0] + 2;
    gridIndex[3] = gridIndex[0] + 5;
    gridIndex[4] = gridIndex[0] + 6;
    gridIndex[5] = gridIndex[0] + 7;
    gridIndex[6] = gridIndex[0] + 10;
    gridIndex[7] = gridIndex[0] + 11;
    gridIndex[8] = gridIndex[0] + 12;

} //end updateIndex()


/* ------------------------------------------------
 * Decides on the location of the grid based on the gridIndex
 *
 * Takes 2 2D char arrays and an int array
 *
 * Does not return a value
 * ------------------------------------------------
*/
void positionBoard (char theBoard[][5], char thePieces[][5], int gridIndex[]) {

    // makes sure that the gridIndex is correctly positioned
    updateIndex(gridIndex);

    // the vertical walls
    theBoard[gridIndex[0]][CENTER]  = '|';
    theBoard[gridIndex[1]][CENTER]  = '|';
    theBoard[gridIndex[3]][CENTER] = '|';
    theBoard[gridIndex[4]][CENTER] = '|';
    theBoard[gridIndex[6]][CENTER] = '|';
    theBoard[gridIndex[7]][CENTER] = '|';

    // horizontal walls
    theBoard[gridIndex[0]][BELOW]  = '-';
    theBoard[gridIndex[1]][BELOW]  = '-';
    theBoard[gridIndex[3]][BELOW] = '-';
    theBoard[gridIndex[4]][BELOW] = '-';

    // horizontal walls
    thePieces[gridIndex[0]][BELOW]  = '-';
    thePieces[gridIndex[1]][BELOW]  = '-';
    thePieces[gridIndex[2]][BELOW]  = '-';
    thePieces[gridIndex[3]][BELOW] = '-';
    thePieces[gridIndex[4]][BELOW] = '-';
    thePieces[gridIndex[5]][BELOW] = '-';

} //end positionBoard()


/* ------------------------------------------------
 * Clears the grid's current positon and allows for moving
 * it to other positions
 *
 * Takes 2 2D char arrays and an int array
 *
 * Does not return a value
 * ------------------------------------------------
*/
void clearGrid (char theBoard[][5], char thePieces[][5], int gridIndex[]) {

    int i = 0;
    for (i = 0; i < 9; i++) {

        // clears grid but keeps certain positoins for keeping it the board within boundaries
        if (gridIndex[i] % 5 != 4) {
            theBoard[gridIndex[i]][CENTER] = ' ';
            if (gridIndex[i] < 20) {
                theBoard[gridIndex[i]][BELOW] = ' ';
            }
        }
        thePieces[gridIndex[i]][BELOW] = ' ';

    }

} // end clearGrid ();


/* ------------------------------------------------
 * Moves the grid up by updating the first
 * index and checking where it is moving
 *
 * Takes 1 2D char arrays, an int array and 2 ints
 *
 * Does not return a value
 * ------------------------------------------------
*/
void moveGridUp (char theBoard[][5], int gridIndex[9], int &outOfBounds, int &gridCameFrom) {

    if (theBoard[gridIndex[1]][ABOVE] != ' ') {
        printf("*** Grid may not be moved off of board.  Please retry.\n");
        outOfBounds = 1;
    }
    else if (gridIndex[0] - 5 == gridCameFrom) {

        printf("*** Grid cannot be immediately moved back to original position.  Please retry.\n");
        outOfBounds = 1;

    }
    else {
        gridCameFrom = gridIndex[0];
        //clearGrid(theBoard, thePieces, gridIndex);      // clears grid before display
        gridIndex[0] = gridIndex[0] - 5;
        updateIndex(gridIndex);
        //positionBoard(theBoard, thePieces, gridIndex);  // set up the position of the grid after moves
    }
} //end moveGridUp


/* ------------------------------------------------
 * Moves the grid down by updating the first
 * index and checking where it is moving
 *
 * Takes 1 2D char arrays, an int array and 2 ints
 *
 * Does not return a value
 * ------------------------------------------------
*/
void moveGridDown (char theBoard[][5], int gridIndex[9], int &outOfBounds, int &gridCameFrom) {

    if (theBoard[gridIndex[7]][BELOW] != ' ') {
        printf("*** Grid may not be moved off of board.  Please retry.\n");
        outOfBounds = 1;
    }
    else if (gridIndex[0] + 5 == gridCameFrom) {
        printf("*** Grid cannot be immediately moved back to original position.  Please retry.\n");
        outOfBounds = 1;
    }
    else {
        gridCameFrom = gridIndex[0];
        gridIndex[0] = gridIndex[0] + 5;
        updateIndex(gridIndex);
    }
} //end moveGridDown


/* ------------------------------------------------
 * Moves the grid left by updating the first
 * index and checking where it is moving
 *
 * Takes 1 2D char arrays, an int array and 2 ints
 *
 * Does not return a value
 * ------------------------------------------------
*/
void moveGridLeft (char theBoard[][5], int gridIndex[9], int &outOfBounds, int &gridCameFrom) {

    if (theBoard[gridIndex[3] - 1][CENTER] != ' ') {
        printf("*** Grid may not be moved off of board.  Please retry.\n");
        outOfBounds = 1;
    }
    else if (gridIndex[0] - 1  == gridCameFrom) {
        printf("*** Grid cannot be immediately moved back to original position.  Please retry.\n");
        outOfBounds = 1;
    }
    else {
        gridCameFrom = gridIndex[0];
        gridIndex[0] = gridIndex[0] - 1;
        updateIndex(gridIndex);
    }
} //end moveGridLeft


/* ------------------------------------------------
 * Moves the grid right by updating the first
 * index and checking where it is moving
 *
 * Takes 1 2D char arrays, an int array and 2 ints
 *
 * Does not return a value
 * ------------------------------------------------
*/
void moveGridRight (char theBoard[][5], int gridIndex[9], int &outOfBounds, int &gridCameFrom) {

    if (theBoard[gridIndex[5]][CENTER] != ' ') {
        printf("*** Grid may not be moved off of board.  Please retry.\n");
        outOfBounds = 1;
    }
    else if (gridIndex[0] + 1  == gridCameFrom) {
        printf("*** Grid cannot be immediately moved back to original position.  Please retry.\n");
        outOfBounds = 1;
    }
    else {
        gridCameFrom = gridIndex[0];
        gridIndex[0] = gridIndex[0] + 1;
        updateIndex(gridIndex);
    }
} // end moveGridRight


/* ------------------------------------------------
 * Moves the grid up and left by updating the first
 * index and checking where it is moving
 *
 * Takes 1 2D char arrays, an int array and 2 ints
 *
 * Does not return a value
 * ------------------------------------------------
*/
void moveGridUpLeft (char theBoard[][5], int gridIndex[9], int &outOfBounds, int &gridCameFrom) {

    if (theBoard[gridIndex[3] - 1][CENTER] != ' ' || theBoard[gridIndex[1]][ABOVE] != ' ') {
        printf("*** Grid may not be moved off of board.  Please retry.\n");
        outOfBounds = 1;
    }
    else if (gridIndex[0] - 6  == gridCameFrom) {
        printf("*** Grid cannot be immediately moved back to original position.  Please retry.\n");
        outOfBounds = 1;
    }
    else {
        gridCameFrom = gridIndex[0];
        gridIndex[0] = gridIndex[0] - 6;
        updateIndex(gridIndex);
    }
} // end moveGridUpLeft


/* ------------------------------------------------
 * Moves the grid up and right by updating the first
 * index and checking where it is moving
 *
 * Takes 1 2D char arrays, an int array and 2 ints
 *
 * Does not return a value
 * ------------------------------------------------
*/
void moveGridUpRight (char theBoard[][5], int gridIndex[9], int &outOfBounds, int &gridCameFrom) {

    if (theBoard[gridIndex[5]][CENTER] != ' ' || theBoard[gridIndex[1]][ABOVE] != ' ') {
        printf("*** Grid may not be moved off of board.  Please retry.\n");
        outOfBounds = 1;
    }
    else if (gridIndex[0] - 4  == gridCameFrom) {
        printf("*** Grid cannot be immediately moved back to original position.  Please retry.\n");
        outOfBounds = 1;
    }
    else {
        gridCameFrom = gridIndex[0];
        gridIndex[0] = gridIndex[0] - 4;
        updateIndex(gridIndex);
    }
} // end moveGridUpRight


/* ------------------------------------------------
 * Moves the grid down and left by updating the first
 * index and checking where it is moving
 *
 * Takes 1 2D char arrays, an int array and 2 ints
 *
 * Does not return a value
 * ------------------------------------------------
*/
void moveGridDownLeft (char theBoard[][5], int gridIndex[9], int &outOfBounds, int &gridCameFrom) {

    if (theBoard[gridIndex[3] - 1][CENTER] != ' ' || theBoard[gridIndex[7]][BELOW] != ' ') {
        printf("*** Grid may not be moved off of board.  Please retry.\n");
        outOfBounds = 1;
    }
    else if (gridIndex[0] + 4  == gridCameFrom) {
        printf("*** Grid cannot be immediately moved back to original position.  Please retry.\n");
        outOfBounds = 1;
    }
    else {
        gridCameFrom = gridIndex[0];
        gridIndex[0] = gridIndex[0] + 4;
        updateIndex(gridIndex);
    }
} // end moveGridDownLeft


/* ------------------------------------------------
 * Moves the grid down and right by updating the first
 * index and checking where it is moving
 *
 * Takes 1 2D char arrays, an int array and 2 ints
 *
 * Does not return a value
 * ------------------------------------------------
*/
void moveGridDownRight (char theBoard[][5], int gridIndex[9], int &outOfBounds, int &gridCameFrom) {

    if (theBoard[gridIndex[5]][CENTER] != ' ' || theBoard[gridIndex[7]][BELOW] != ' ') {
        printf("*** Grid may not be moved off of board.  Please retry.\n");
        outOfBounds = 1;
    }
    else if (gridIndex[0] + 6  == gridCameFrom) {
        printf("*** Grid cannot be immediately moved back to original position.  Please retry.\n");
        outOfBounds = 1;
    }
    else {
        gridCameFrom = gridIndex[0];
        gridIndex[0] = gridIndex[0] + 6;
        updateIndex(gridIndex);
    }
} // end moveGridDownRight

void moveGrid(int destination, int gridIndex[9]){
    // Moving the grid back to the previous position, only works with perfect input
    if(destination > 0 && destination < 4)
        destination -= 7;
    else if(destination > 6 && destination < 10)
        destination -= 3;
    else if(destination == 4 || destination == 6)
        destination -= 5;
    gridIndex[0] = gridIndex[0] + destination;
    updateIndex(gridIndex);
}

/* ------------------------------------------------
 * Decides on which move to make based on the user input
 *
 * Takes 3 int variables, 1 int array and 1 char 2D array
 *
 * Does not return a value
 * ------------------------------------------------
*/
void makeMove(int userGrid, int &outOfBounds, char theBoard[][5], int gridIndex[], int &gridCameFrom) {

    switch (userGrid) {
    case 1:
        //move up left diagonal
        moveGridUpLeft(theBoard, gridIndex, outOfBounds, gridCameFrom);
        break;
    case 2:
        //move up
        moveGridUp(theBoard, gridIndex, outOfBounds, gridCameFrom);
        break;
    case 3:
        //move up right diagonal
        moveGridUpRight(theBoard, gridIndex, outOfBounds, gridCameFrom);
        break;
    case 4:
        //move left
        moveGridLeft(theBoard, gridIndex, outOfBounds, gridCameFrom);
        break;
    case 6:
        //move right
        moveGridRight(theBoard, gridIndex, outOfBounds, gridCameFrom);
        break;
    case 7:
        //move down left diagonal
        moveGridDownLeft(theBoard, gridIndex, outOfBounds, gridCameFrom);
        break;
    case 8:
        //move down
        moveGridDown(theBoard, gridIndex, outOfBounds, gridCameFrom);
        break;
    case 9:
        //move down right diagonal
        moveGridDownRight(theBoard, gridIndex, outOfBounds, gridCameFrom);
        break;
    default:
        printf("*** 5 is not a valid move for the grid.  Please retry.\n");
        outOfBounds = 1;
        break;
    }

} // end makeMove()
void dropFromList(Node* &pHead){
    pHead = pHead->next; // Sets the linked list back 1 step
}

void addToList(Node* &pHead, char userPiece, int userGrid, int turn){// Adds to the list
    Node* pTemp = new Node;
    pTemp->next = pHead;
    pTemp->piece = userPiece;
    pTemp->destination = userGrid;
    pTemp->turn = turn;
    pHead = pTemp;              // Sets pHead to the newest move; pTemp.
    free(&pTemp);               // Deletes pTemp as pHead replaces it.
}

/* ------------------------------------------------
 * Function that handles the majority of the program functions
 *
 * Takes 3 int parameters, 4 char 2D arrays, and one int array
 *
 * Does not return a value
 * ------------------------------------------------
*/
void playGame (char &userPiece, int &userGrid, int &turn, int gridIndex[], int &gridCameFrom,
               char theBoard[][5], char thePieces[][5], char gameInfo[][50],  char gamePieces[2][4]) {

    int finished = 0;
    int outOfBounds = 0;
    int inputError = 0;
    int pieceCheck = -1;
    int pieceFound = 0;
    int gridPiece = -1;
    Node* pHead = NULL;     // Linked List of the moves
    int winner = 0;

    //displaying board stuff
    clearGrid(theBoard, thePieces, gridIndex);      // clears grid before display
    positionBoard(theBoard, thePieces, gridIndex);  // set up the position of the grid after moves
    printBoard(thePieces, theBoard, gameInfo);      // display board

    while (!finished) {

        // resets tracking varaibles for the next run thorugh of th program
        outOfBounds = 0;
        inputError = 0;
        pieceCheck = -1;
        pieceFound = 0;
        gridPiece = -1;

        clearGrid(theBoard, thePieces, gridIndex);      // clears grid before display

        // determies which instruction set to display and displays appropriate information
        if (turn + 1 > 4) {
            printf("\n%d. Player %d: Enter piece to move and destination number, 'm' or 'M'\n", turn + 1, turn % 2 + 1);
            printf("             to move the grid and move direction (1-9 except 5), or \n             'u' or 'U' to undo last move: \n");
        }
        else {

            printf("\n%d. Player %d: Enter piece to move and destination number, or 'u' or 'U' to undo: ", turn + 1, turn % 2 + 1);
        }

        // user input and exit conditions
        scanf(" %c", &userPiece);
        if (userPiece == 'u' || userPiece == 'U'){
            if(pHead == NULL)// pHead is null when the game is at the first turn, so can't go past the start
                printf("****Error cannot undo past beginning of the game!\n");
            else{
                if(pHead->piece == 'm' || pHead->piece == 'M')
                    moveGrid((10 - pHead->destination), gridIndex);// Moves the grid back if it was moves last turn
                else{
                    if((turn + 1) % 2 == 0){
                        gamePieces[0][pHead->piece - 'A'] = pHead->piece;// Sets the piece back in the list to reuse
                    }
                    if((turn + 1) % 2 == 1){
                        gamePieces[1][pHead->piece - 'a'] = pHead->piece;// Sets the piece back in the list to reuse
                    }
                    thePieces[gridIndex[pHead->destination - 1]][CENTER] = '.';// Reset the destination to default '.'
                    updateGameInfo(gameInfo, gamePieces);// Update information
                }
                dropFromList(pHead); // Sets the linked list back 1 step
                turn--;     // Decrement turn to go back to the previous player's turn
                //displaying board stuff
                clearGrid(theBoard, thePieces, gridIndex);      // clears grid before display
                positionBoard(theBoard, thePieces, gridIndex);  // set up the position of the grid after moves
                printBoard(thePieces, theBoard, gameInfo);      // display board
            }
        }
        else{
            if (userPiece == 'X' || userPiece == 'x') {

                printf("\nExiting program...\n\n");
                break;

            }
            scanf(" %d", &userGrid);
            if (userGrid == 'X' || userGrid == 'x') {

                printf("\nExiting program...\n\n");
                break;

            }

            // checks if the input number was within the grid
            if (userGrid > 9 || userGrid < 1) {

                printf("\n*** Please enter a number on the grid (1 - 9).  Please retry.\n");
                continue;

            }

            printf("\n");

            // handles moving the board potentially
            if (userPiece == 'm' || userPiece == 'M') {

                // determins if the player can move the grid
                if (turn + 1 < 5) {

                    printf("*** Both players must place 2 pieces before grid can be moved.  Please retry.\n");
                    continue;

                }

                // determines the move to make
                makeMove(userGrid, outOfBounds, theBoard, gridIndex, gridCameFrom);

                // checks to see if the attempted move was out of bounds
                if (outOfBounds == 1) {

                    continue;

                }


            }
            else { // determins if the players have input the right piece for their turn
                if (turn % 2 + 1 == 1) {
                    switch (userPiece) {
                    case 'A':
                        pieceCheck = 0;
                        break;
                    case 'B':
                        pieceCheck = 1;
                        break;
                    case 'C':
                        pieceCheck = 2;
                        break;
                    case 'D':
                        pieceCheck = 3;
                        break;

                    default:
                        printf("*** Player 1 can only select from upper-case pieces. Please retry.\n");
                        inputError = 1;
                        break;
                    }
                    if (inputError == 1) {
                        continue;
                    }
                }
                else {
                    switch (userPiece) {
                    case 'a':
                        pieceCheck = 0;
                        break;
                    case 'b':
                        pieceCheck = 1;
                        break;
                    case 'c':
                        pieceCheck = 2;
                        break;
                    case 'd':
                        pieceCheck = 3;
                        break;

                    default:
                        printf("*** Player 2 can only select from lower-case pieces. Please retry.\n");
                        inputError = 1;
                        break;
                    }
                    if (inputError == 1) {
                        continue;
                    }
                }

                // searches the grid for the piece that is to be moved
                for (int i = 0; i < 9; i++) {

                    if (thePieces[gridIndex[i]][CENTER] == userPiece) {

                        gridPiece = gridIndex[i];
                        pieceFound = 1;
                        break;

                    }

                }

                // determines when the player can move pieces on the grid
                if (gamePieces[turn % 2][pieceCheck] == ' ' && turn < 5 ) {

                    printf("*** Both players must place 2 pieces before grid pieces can be moved. Please retry.\n");
                    continue;

                }

                // determeins if the pieces is in the grid before moving it to a new position
                if (gamePieces[turn % 2][pieceCheck] == ' ' && pieceFound == 0 ) {

                    printf("*** Pieces outside of the grid cannot be moved. Please retry.\n");
                    continue;

                }

                // determins if the position is available for placement
                if (thePieces[gridIndex[userGrid - 1]][CENTER] != '.') {

                    printf("*** Destination square %d is already occupied Please retry.\n", userGrid);
                    continue;

                }


                // places the piece
                gamePieces[turn % 2][pieceCheck] = ' ';
                if (gridPiece != -1) {
                    thePieces[gridPiece][CENTER] = '.';
                }
                thePieces[gridIndex[userGrid - 1]][CENTER] = userPiece;
                updateGameInfo(gameInfo, gamePieces);

            }

            // Insert win check function that will check if the win spots are capital or lower case
            // and use the turn nubmer to determine the winner in case of grid move makes both players win



            //displaying board stuff
            clearGrid(theBoard, thePieces, gridIndex);      // clears grid before display
            positionBoard(theBoard, thePieces, gridIndex);  // set up the position of the grid after moves
            printBoard(thePieces, theBoard, gameInfo);      // display board

            // check for winner
            winCheck(thePieces, gridIndex, turn, winner, finished);

            if (winner != 0) {

                printf("CONGRATULATIONS! Player %d wins!\n\n", winner);

            }

            // only increase the turn only if going to loop again
            if (!finished) {
                turn++;
            }
            addToList(pHead, userPiece, userGrid, turn);
            // Sets pTemp to a new Node with the new move being recorded and pointing to pHead
        }
    }

} // end playGame();


/* ------------------------------------------------
 * Sets up the starting pieces for the users in gameInfo
 *
 * Takes one 2D char array
 *
 * Does not return a value
 * ------------------------------------------------
*/
void initializePieces(char gamePieces[][4]) {

    gamePieces[0][0] = 'A';
    gamePieces[0][1] = 'B';
    gamePieces[0][2] = 'C';
    gamePieces[0][3] = 'D';

    gamePieces[1][0] = 'a';
    gamePieces[1][1] = 'b';
    gamePieces[1][2] = 'c';
    gamePieces[1][3] = 'd';


} //end initializePieces


int main()
{
    char thePieces[25][5];
    char theBoard[25][5];
    char gameInfo[10][50];
    char gamePieces[2][4];
    char userPiece;
    int userGrid;
    int turn = 0;

    int gridCameFrom;


    //int i = 0; // was used for debugging

    // sets up the grid information and position
    int gridIndex[9];
    gridIndex[0] = START;
    gridCameFrom = START;
    updateIndex(gridIndex);

    // display program and author information
    displayIdInformation();

    // setting up the board and pieces
    initializeBoard(thePieces, theBoard);
    initializePieces(gamePieces);
    updateGameInfo(gameInfo, gamePieces);

    // set up the board and grid information and then display the board
    positionBoard(theBoard, thePieces, gridIndex);
    //printBoard(thePieces, theBoard, gameInfo);

    // clear grid on board to reprint later
    clearGrid(theBoard, thePieces, gridIndex);

    // main game function
    playGame(userPiece, userGrid, turn, gridIndex, gridCameFrom, theBoard, thePieces, gameInfo, gamePieces);

    return 0;
} // end main()
