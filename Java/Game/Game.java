package Game;

public class Game{
    public String[][] gameBoard = {
        {" ", " ", " "},
        {" ", " ", " "},
        {" ", " ", " "}
    };
    
    public void print_board(){
        String end = " | ";
        String line_2 = "\n--+----+--\n";
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                System.out.printf("%s", gameBoard[i][j]); // For no new line
                if (j < 2) System.out.printf("%s", end);
            }
            if (i < 2) System.out.printf("%s", line_2);
        }
        System.out.println("");
    }
    // bool
    public boolean set(String symbol, int x, int y){
        boolean success = true;
        x--;
        y--;
        if (!gameBoard[x][y].equals(" ")) success = false;
        else{
            gameBoard[x][y] = symbol;
            success = true;
        }
        return success;
    }

    public String check_win(){
        String winner = "";
                for (int col = 0; col < 3; col++) {
            if (gameBoard[0][col].equals(gameBoard[1][col]) && 
                gameBoard[1][col].equals(gameBoard[2][col]) && 
                !gameBoard[0][col].equals(" ")) {
                winner = gameBoard[0][col];
            }
        }

        for (int row = 0; row < 3; row++) {
            if (gameBoard[row][0].equals(gameBoard[row][1]) && 
                gameBoard[row][1].equals(gameBoard[row][2]) && 
                !gameBoard[row][0].equals(" ")) {
                winner = gameBoard[row][0]; 
            }
        }

        if (gameBoard[0][0].equals(gameBoard[1][1]) && 
            gameBoard[1][1].equals(gameBoard[2][2]) && 
            !gameBoard[0][0].equals(" ")) {
            winner = gameBoard[1][1]; 
        }
        else if (gameBoard[0][2].equals(gameBoard[1][1]) && 
                 gameBoard[1][1].equals(gameBoard[2][0]) && 
                 !gameBoard[0][2].equals(" ")) {
            winner = gameBoard[1][1]; 
        }

        if (winner.equals("")){
            if(is_full()){
                winner = "Tie";
            }
        }

        return winner;
    }

    public boolean is_full(){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (gameBoard[i][j].equals(" "))
                    return false;
            }
        }
        return true;
    }
}