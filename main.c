#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
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
    for (int i = 0; i < 7; i+=3){
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
    // Check for diagonal win
    if ((a[0] == current_player) && (a[0] == a[4]) && (a[0] == a[8])){
        return true;
        
    }
    else if ((a[2] == current_player) && (a[0] == a[4]) && (a[0] == a[6])){
        return true;
        
    }
    else{
        
        return false;  
    }
    
}
int minimax(){
    return 1;
}
void AIMove(char current_player){

    int move = -1;
    int score = -2;

    // Check through every legal move and determine the max score possible         
    for (int i = 0; i < 9; i++){
        if (a[i] == ' '){
            a[i] = current_player;
            int tempScore = minimax();
            a[i] = ' ';
            if (tempScore > score){
                score = tempScore;
                move = i;
            }
        }
    }
    printf("%d", move);
    a[move] = current_player;
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
    AI_INPUT,
    GAME_OVER
} GAME;

// Programme Entry
int main(void) {
    char current_player = 'X';
    char new_game_bool;
    char ai_turn_bool;
    int player_input;
    int tempScore = -1000;
    
    uint8_t dim_3x3[2] = {3, 3};

    GAME GameState = START;

    

    while (1){
        switch (GameState){
            case START:
                printf("Would You Like To Play First? (Y/N)\n");
                scanf(" %c", &ai_turn_bool);
                if (ai_turn_bool == 'Y'){
                    GameState = PLAYER_INPUT;
                    
                }
                else if (ai_turn_bool == 'N'){
                    
                    GameState = AI_INPUT;
                }
                else{
                    printf("Invalid Input\n");
                }
                break;

            case PLAYER_INPUT:
                
                PrintBoard(a, dim_3x3);
                printf("Enter Position (1-9)\n");
                scanf(" %d", &player_input);
                if ((player_input >= 1) && (player_input <= 9) && (a[player_input-1] == ' ')){
                    a[player_input-1] = current_player;
                    GameState = GAME_OUTCOME;
                    
                }
                else{
                    printf("Invalid Input\n");
                }
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

            case PLAYER_CHANGE:
                if (ai_turn_bool == 'Y') {
                    current_player = (current_player == 'X') ? 'O' : 'X';
                    ai_turn_bool = 'N';
                    GameState = AI_INPUT;
                }
                else if (ai_turn_bool == 'N') {
                    current_player = (current_player == 'X') ? 'O' : 'X';
                    printf("%c", current_player);
                    ai_turn_bool = 'Y';
                    GameState = PLAYER_INPUT;
                }
                else {
                    printf("You shouldn't be here!\n");
                }
                break;

            case AI_INPUT:

                
                AIMove(current_player);
                GameState = GAME_OUTCOME;

                break;
            case GAME_OVER:
                exit(0);
                break;
            }
    }
    return 0;
}