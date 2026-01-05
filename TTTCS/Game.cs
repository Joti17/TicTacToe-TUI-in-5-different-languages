namespace Game
{

public class Game{
    public string[][] gameBoard = {
        new string[] {" ", " ", " "},
        new string[] {" ", " ", " "},
        new string[] {" ", " ", " "}
    };
    
    public void print_board(){
        string end = " | ";
        string line_2 = "\n--+----+--\n";
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                Console.WriteLine(gameBoard[i][j]);
                if (j < 2) Console.Write(end);
            }
            if (i < 2) Console.WriteLine(line_2);
        }
        Console.WriteLine("");
    }
    // bool
    public bool set(string symbol, int x, int y){
        bool success = true;
        x--;
        y--;
        if (!gameBoard[x][y].Equals(" ")) success = false;
        else{
            gameBoard[x][y] = symbol;
            success = true;
        }
        return success;
    }

    public string check_win(){
        string winner = "";
                for (int col = 0; col < 3; col++) {
            if (gameBoard[0][col].Equals(gameBoard[1][col]) && 
                gameBoard[1][col].Equals(gameBoard[2][col]) && 
                !gameBoard[0][col].Equals(" ")) {
                winner = gameBoard[0][col];
            }
        }

        for (int row = 0; row < 3; row++) {
            if (gameBoard[row][0].Equals(gameBoard[row][1]) && 
                gameBoard[row][1].Equals(gameBoard[row][2]) && 
                !gameBoard[row][0].Equals(" ")) {
                winner = gameBoard[row][0]; 
            }
        }

        if (gameBoard[0][0].Equals(gameBoard[1][1]) && 
            gameBoard[1][1].Equals(gameBoard[2][2]) && 
            !gameBoard[0][0].Equals(" ")) {
            winner = gameBoard[1][1]; 
        }
        else if (gameBoard[0][2].Equals(gameBoard[1][1]) && 
                 gameBoard[1][1].Equals(gameBoard[2][0]) && 
                 !gameBoard[0][2].Equals(" ")) {
            winner = gameBoard[1][1]; 
        }

        if (winner.Equals("")){
            if(is_full()){
                winner = "Tie";
            }
        }

        return winner;
    }

    public bool is_full(){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (gameBoard[i][j].Equals(" "))
                    return false;
            }
        }
        return true;
    }
}
}