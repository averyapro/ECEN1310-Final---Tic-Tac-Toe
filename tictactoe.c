#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void boardGuide(){ //function for the user that describes how the program works and required user input
    printf("Welcome to Tic-Tac-Toe! You will be playing against the computer and you will be 'X'.\n"); 
    printf("Type a number 1-9 to pick your board space. Below is the board guide with corresponding numbers. Have fun!\n");
    printf(" 1 | 2 | 3 \n");
    printf("---|---|---\n");
    printf(" 4 | 5 | 6 \n");
    printf("---|---|---\n");
    printf(" 7 | 8 | 9 \n");
    printf("\n");
}

void printBoard(char board[3][3]){
    for (int i = 0; i < 3; i++) { //loop that runs through all indices of the board
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]); //prints the current board state after computer and user move
        if (i < 2) {
            printf("---|---|---\n"); 
        }
    }
    printf("\n"); 
}

void userMove(char board[3][3]){
    int row, col, input;
    int c; 
    printf("Enter where you'd like to place your X (1-9):\n");
    while (true){
        if (scanf("%d", &input) != 1){ //expects one int input so scanf shoudl be equal to 1; if it's not, input is malformed
            printf("Invalid input, try again\n");
            while((c = getchar() != '\n' && c != EOF)); //removes newline buffer in scanf if input is invalid
            continue;
            }
         if (input < 1 || input > 9){ //expect input to be 1-9
            printf("Oops, invalid input, try again!\n");
            continue;
         }
        row = (input - 1) / 3; //sets row index based on user input
        col = (input - 1) % 3; //sets col index based on user input
        if (board[row][col] != ' '){ //if the specific array index is not equal to a space, then that spot is already taken
            printf("Already taken, try again!\n");
            continue;
        }
        if (board[row][col] == ' '){ //if specific array index is equal to a space we set that space equal to X for user input
            board[row][col] = 'X';
            break;
        }
    }
}

void computerMove(char board[3][3]){
    int row, col, cMove;
    while (true){
        cMove = rand() % 9 + 1; //take the number from srand, % 9 and plus 1 to get it within the index of 1-9
        row = (cMove - 1) / 3; //same as user input; set row index based on rand generation
        col = (cMove - 1) % 3; //same as user input; set col index based on rand generation
        if (board[row][col] != ' '){ //if specific index is not a space, that spot is already taken
            continue;
        }
        if (board[row][col] == ' '){
            board[row][col] = 'O'; //if specific index is a space, set that index equal to O
            break;
        }
    }
}

int checkWin(char board[3][3]){
    char players[] = {'X', 'O'};
    int i, j, p;
    for (p = 0; p < 2; p++){ //runs through players array with X and O
        char player = players[p];
        for (i = 0; i < 3; i++){
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player){ //run through all columns to check for win
                if (player == 'X'){ //if players array is equal to X, the player wins
                    printf("Congrats! The player wins!\n");
                    return 0;
                } else {
                    printf("The computer wins! Better luck next time!\n"); //if players array is not X it must be O, computer wins
                    return 0;
                }
            }
        }
        for (j = 0; j < 3; j++){
            if (board[j][0] == player && board[j][1] == player && board[j][2] == player){ //run through all rows to check for win
                if (player == 'X'){ //if players array is equal to X, player wins
                    printf("Congrats! The player wins!\n");
                    return 0;
                } else {
                    printf("The computer wins! Better luck next time!\n"); //players array is equal to O, computer wins
                    return 0;
                }
            }
        }
    if (board[0][0] == player && board[1][1] == player && board [2][2] == player){ //brute force to check for diagonal wins
        if (player == 'X'){
            printf("Congrats! The player wins!\n");
            return 0;
        } else {
            printf("The computer wins! Better luck next time!\n");
            return 0;
        }
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player){ //brute force to check for diagonal wins
        if (player == 'X'){
            printf("Congrats! The player wins!\n");
            return 0;
        } else {
            printf("The computer wins! Better luck next time!\n");
            return 0;
        }
    }
    }
    return 1;
}

int checkDraw(char board[3][3]){
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (board[i][j] == ' '){ //run through all indices on the board to check if any are still open
                return 0;
            }
        }
    }
    printf("It's a draw!\n"); //if no spaces are still open and checkWin fails to find a winner, the game ends in a draw
    return -1;
}
    
             
int main(){
    boardGuide(); //print boardGuide to show the user how the program works
    srand(time(NULL)); //creates random number
    char board[3][3] = { //initialize 2D array
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
};
    while (true){
        printBoard(board); 
        userMove(board);
         if (checkWin(board) == 0){ //indicates checkWin found a winner; show the winning board and break
            printBoard(board);
            break;
        }
        if (checkDraw(board) == -1){ //indicated checkDraw found a draw; show final board state and break
            printBoard(board);
            break;
        }
        computerMove(board);
        if (checkWin(board) == 0){
            printBoard(board);
            break;
        }
        if (checkDraw(board) == -1){
            printBoard(board);
            break;
        }
    }
    return 0;
}