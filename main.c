#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.c"

void exit(int returning_value);

void PrintBoard(char* matrix, uint8_t* dim) {
    for (uint8_t row = 0; row < dim[0]; row++) {
        printf("\n");
        for (uint8_t col = 0; col < dim[1]; col++) {
            if (col < 2){
                printf("   %c   |", matrix[row*dim[1]+col]);
            }
            else{
                printf("   %c   ", matrix[row*dim[1]+col]);
            }
        }
        if (row < 2){
            printf("\n-------|-------|-------");
        }
    }
    printf("\n\n");
}

void ClearBoard(char* matrix){
    // Set all spaces to clear
    for (uint8_t row = 0; row < 3; row++) {
        for (uint8_t col = 0; col < 3; col++) {
            matrix[row*3+col] = ' ';
        }
    }
}

bool CheckForWin(char current_player){
    // Check for horizontal win
    for (int i = 0; i < 7; i++){
        if ((a[i] == current_player) && (a[i] == a[i+1]) && (a[i] == a[i+2])){
            return true;
        }
    }
    // Check for vertical win
    for (int i = 0; i < 3; i++){
        if ((a[i] == current_player) && (a[i] == a[i+3]) && (a[i] == a[i+6])){
            return true;
        }
    }
    // Check for horizontal win
    if ((a[0] == current_player) && (a[0] == a[4]) && (a[0] == a[8])){
        return true;
    }
    else if ((a[2] == current_player) && (a[0] == a[4]) && (a[0] == a[6])){
        return true;
    }
    return false;               
}

bool CheckForDraw(char current_player){
    // Check if no empty spaces remain
    for (int i = 0; i < 9; i++){
        if (a[i] == ' '){
            return false;
        }
    }
    return true;
}

typedef enum{
    START,
    PLAYER_INPUT,
    PLAYER_CHANGE,
    GAME_OUTCOME,
    GAME_OVER
} GAME;

// Programme Entry
int main(void) {
    char current_player;
    char new_game_bool;
    int player_input;

    uint8_t dim_3x3[2] = {3, 3};

    GAME GameState = START;

    while (1){
        switch (GameState){
            case START:
                printf("Enter Starting Player (X/O)\n");
                scanf(" %c", &current_player);
                if ((current_player == 'X') || (current_player == 'O')){
                    GameState = PLAYER_INPUT;
                }
                else{
                    printf("Invalid Input");
                }
                break;

            case PLAYER_INPUT:
                PrintBoard(a, dim_3x3);
                printf("Enter Position (0-8)\n");
                scanf(" %d", &player_input);
                if ((player_input >= 0) && (player_input <= 8) && (a[player_input] == ' ')){
                    a[player_input] = current_player;
                    GameState = GAME_OUTCOME;
                    
                }
                else{
                    printf("Invalid Input\n");
                }
                break;

            case PLAYER_CHANGE:
                if (current_player == 'X'){
                    current_player = 'O';
                }
                else if (current_player == 'O'){
                    current_player = 'X';
                }
                GameState = PLAYER_INPUT;
                break;

            case GAME_OUTCOME:
                if (CheckForWin(current_player)){
                    PrintBoard(a, dim_3x3);
                    printf("Game Over!\n");
                    printf("Player %c Won\n", current_player); 
                    printf("New Game? (Y/N)\n");
                    scanf(" %c", &new_game_bool);
                    if (new_game_bool == 'Y'){
                        ClearBoard(a);
                        GameState = START;
                    }
                    else if (new_game_bool == 'N'){
                        ClearBoard(a);
                        GameState = GAME_OVER;
                    }
                    else{
                        printf("Invalid Input");
                    }
                }
                else if (CheckForDraw(current_player)){
                    PrintBoard(a, dim_3x3);
                    printf("Game Draw!\n");
                    printf("New Game? (Y/N)\n");
                    scanf(" %c", &new_game_bool);
                    if (new_game_bool == 'Y'){
                        ClearBoard(a);
                        GameState = START;
                    }
                    else if (new_game_bool == 'N'){
                        ClearBoard(a);
                        GameState = GAME_OVER;
                    }
                    else{
                        printf("Invalid Input");
                    }
                }
                else{
                    GameState = PLAYER_CHANGE;
                }
                break;

            case GAME_OVER:
                exit(0);
                break;
            }
    }
    return 0;
}