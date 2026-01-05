#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>

using std::string;
#pragma region game
class Game{
    public:
    string m_gameBoard[3][3] = {
        {" ", " ", " "},
        {" ", " ", " "},
        {" ", " ", " "}};

    
    void print_board(){
        string end = " | ";
        string line_2 = "\n--+----+--\n";
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                std::cout << m_gameBoard[i][j];
                if (j < 2) std::cout << end;
            }
            if (i < 2) std::cout << line_2;
        }
        std::cout << std::endl;
    }

    bool set(string symbol, int x, int y){
        bool success = true;
        y--;
        x--;
        if (m_gameBoard[x][y] != " ") success = false;
        else {
            m_gameBoard[x][y] = symbol;
            success = true;
        }
        return success;
    }

    string check_win() {
        string winner = "";

        for (int col = 0; col < 3; col++) {
            if (m_gameBoard[0][col] == m_gameBoard[1][col] && 
                m_gameBoard[1][col] == m_gameBoard[2][col] && 
                m_gameBoard[0][col] != " ") {
                winner = m_gameBoard[0][col];
            }
        }

        for (int row = 0; row < 3; row++) {
            if (m_gameBoard[row][0] == m_gameBoard[row][1] && 
                m_gameBoard[row][1] == m_gameBoard[row][2] && 
                m_gameBoard[row][0] != " ") {
                winner = m_gameBoard[row][0]; 
            }
        }

        if (m_gameBoard[0][0] == m_gameBoard[1][1] && 
            m_gameBoard[1][1] == m_gameBoard[2][2] && 
            m_gameBoard[0][0] != " ") {
            winner = m_gameBoard[1][1]; 
        }
        else if (m_gameBoard[0][2] == m_gameBoard[1][1] && 
                 m_gameBoard[1][1] == m_gameBoard[2][0] && 
                 m_gameBoard[0][2] != " ") {
            winner = m_gameBoard[1][1]; 
        }

        if (winner == "") {
            if (is_full()) {
                winner = "Tie";
            }
        }

        return winner;
    }

    bool is_full(){
        for (int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(m_gameBoard[i][j] == " ")
                    return false;
            }
        }
        return true;
    }
};
#pragma endregion

// AI function
void toUpper(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
}
// End AI function

int main(){
    srand(time(0));
    bool ai = true;
    string ai_string;
    std::cout << "Do you want to play with AI? (y)es or (n)o ";
    std::cin >> ai_string;
    string *ai_s = &ai_string;
    toUpper(*ai_s);
    ai_string = *ai_s;
    if (ai_string == "Y") ai = true;
    else if (ai_string == "N") ai = false;
    else {
        std::cout << "Failed returning to terminal..." << std::endl;
        return -1;
    }
    Game game;
    int column;
    int row;
    while(true){
        game.print_board();
        std::cout << "X's turn\n";
        std::cout << "Enter column ";
        std::cin >> column;
        std::cout << "Enter row ";
        std::cin >> row;
        int choice[2] = {row, column};







        if(choice[0] >= 4 || choice[0] <= 0){
            std::cout << "Failed returning to terminal..." << std::endl;
            return -1;
        } 
        if (choice[1] >= 4 || choice[1] <= 0){
            std::cout << "Failed returning to terminal..." << std::endl;
            return -1;
        }
        if (!game.set("X", choice[0], choice[1])){
            std::cout << "Failed returning to terminal..." << std::endl;
            return -2;
        }   
        if (game.check_win() == ""){
            if (ai){
                int ai_choice[2] = {1, 1};
                bool sett = game.set("O", ai_choice[0], ai_choice[1]);
                while(!sett){
                    if (game.set("O", rand() % 3 + 1, rand() % 3 + 1)) {
                        sett = true;
                    }
                }
            }
            else{
                game.print_board();
                std::cout << "O's turn\n";
                std::cout << "Enter column ";
                std::cin >> column;
                std::cout << std::endl << "Enter row ";
                std::cin >> row;
                int choice[2] = {row, column};
                if(choice[0] >= 4 || choice[0] <= 0){
                    std::cout << "Failed returning to terminal..." << std::endl;
                return -1;
            } 
                if (choice[1] >= 4 || choice[1] <= 0){
                    std::cout << "Failed returning to terminal..." << std::endl;
                    return -1;
                }
                if (!game.set("O", choice[0], choice[1])){
                    std::cout << "Failed returning to terminal..." << std::endl;
                    return -2;
                }   
            }
        }

        string winner = game.check_win();
        if (winner != ""){
            game.print_board();
            if (winner == "Tie"){
                std::cout << "The game ended in a Tie." << std::endl;
            }
            else{
                std::cout << winner << " won! " << std::endl;
            }
            return 1;
        }
    }
    return -3;
}