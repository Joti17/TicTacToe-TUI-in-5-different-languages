#include <stdio.h>
#include <ctype.h> // toupper()
#include <stdlib.h> // rand() + srand()
#include <time.h>

int is_full(char board[3][3]);

void print_board(char board[3][3]){
        char end[] = " | ";
        char line_2[] = "\n--+----+--\n";
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                printf("d", board[i][j]);
                if (j < 2) printf("%s", end);
            }
            if (i < 2) printf(line_2);
        }
        printf("\n");
    }

// 1 = true 0 = false
int set(char symbol, int x, int y, char board[3][3]){
    int success = 1;
    y--;
    x--;
    if (board[x][y] != " ") success = 0;
    else{
        board[x][y] = symbol;
        success = 1;
    }
    return success;
}

char check_win(char board[3][3]){
    char winner = ' ';    // T = Tie, X = X won; O = O won


    for (int col = 0; col < 3; col++){
        if(board[0][col] == board[1][col] &&
           board[1][col] == board[2][col] &&
           board[0][col] != ' '){
            winner = board[0][col];
           }
    }

    for (int row = 0; row < 3; row++){
        if(board[row][0] == board[row][1] &&
           board[row][1] == board[row][2] &&
           board[row][0] != ' '){
            winner = board[0][row];
           }
    }

    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != ' '){
            winner = board[1][1];
        }
    else if(board[0][2] == board[1][1] &&
            board[1][1] == board[2][0] &&
            board[0][2] != ' '){
                winner = board[1][1];
            }
    
    if (winner = ' '){
        if (is_full(board)){
            winner = 'T';
        }
    }

    return winner;
}

int is_full(char board[3][3]){
    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

int main(){
    srand(time(NULL));
    // int r = rand() % 3 + 1;
    char gameBoard[3][3] = { 
                         {' ', ' ', ' '},
                         {' ', ' ', ' '},
                         {' ', ' ', ' '} 
                        };
    int ai = 1;
    char ai_string;
    printf("Do you want to player with AI? (y)es or (n)o ");
    scanf(" %c", &ai_string);
    if (toupper(ai_string) == 'Y') ai = 1;
    else if (toupper(ai_string) == 'N') ai = 0;
    else {
        printf("Failed returning to terminal...\n");
    }
    int column;
    int row;
    while(1){
        print_board(gameBoard);
        printf("X's turn\n");
        printf("Enter column ");
        scanf(" %d", &column);
        printf("Enter row ");
        scanf(" %d", &row);
        
        if(row >= 4 || row <= 0){
            printf("Failed returning to terminal...\n");
            return -1;
        }
        if(column >= 4 || column <= 0){
            printf("Failed returning to terminal...\n");
            return -1;
        }
        if(!set('X', row, column, gameBoard)){
            printf("Failed returning to terminal...\n");
            return -2;
        }

        if(check_win(gameBoard) == ' '){
            if (ai){
                int ai_row, ai_column;
                ai_row = rand() % 3 + 1;
                ai_column = rand() % 3 + 1;
                int sett = set('O', ai_row, ai_column, gameBoard);
                while (!sett){
                    if (set('O', rand() % 3 + 1, rand() % 3 + 1, gameBoard)){
                        sett = 1;
                    }
                }
            }
            else{
                print_board(gameBoard);
                printf("O's turn\n");
                printf("Enter column ");
                scanf(" %d", &column);
                printf("Enter row ");
                scanf(" %d", &row);
                
                if(row >= 4 || row <= 0){
                    printf("Failed returning to terminal...\n");
                    return -1;
                }
                if(column >= 4 || column <= 0){
                    printf("Failed returning to terminal...\n");
                    return -1;
                }
                if(!set('O', row, column, gameBoard)){
                    printf("Failed returning to terminal...\n");
                    return -2;
                }
            }
        }
        char winner = check_win(gameBoard);
        if (winner != ' '){
            print_board(gameBoard);
            if (winner == 'T'){
                printf("The game ended in a Tie.\n"); 
            }
            else{
                printf("%c won! \n", winner);
            }
            return 1;
        }


    }
    return -1;
}