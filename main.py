# Python RPS
import random

class Game():
    def __init__(self) -> None:
        self.gameBoard = [
            [" ", " ", " "],
            [" ", " ", " "],
            [" ", " ", " "],
            ]


    def print_board(self) -> None:
        for i in range(3):
            for j in range(3):
                #if j == 0:
                #    print("", end="")
                print(self.gameBoard[i][j], end=" | " if j < 2 else "")
            print("\n--+----+--" if i < 2 else "")    


    def set(self, symbol: str, x: int, y: int) -> bool:
        success: bool = True
        x -= 1
        y -= 1
        if self.gameBoard[x][y] != " ":
            success = False
        else:
            self.gameBoard[x][y] = symbol
            success = True

        return success


    def check_win(self) -> str:
        #columns
        winner: str = ""
        gb = self.gameBoard
        for col in range(3):
            if self.gameBoard[0][col] == self.gameBoard[1][col] == self.gameBoard[2][col] != " ":
                winner = self.gameBoard[0][col]

        #rows
        for row in range(3):
            if gb[row][0] == gb[row][1] == gb[row][2] != " ":
                winner = gb[row][0]
        
        #diagonals
        if gb[0][0] == gb[1][1] == gb[2][2] != " ":
            winner = gb[1][1]
        elif gb[0][2] == gb[1][1] == gb[2][0] != " ":
            winner = gb[1][1]
        
        if winner == "":
            if self.is_full():
               winner = "Tie"

        return winner
                      




    def is_full(self) -> bool:
        for i in range(3):
            for j in range(3):
               if self.gameBoard[i][j] == " ":
                   return False
        return True           




running: bool = True

game: Game = Game()

ai: bool = False

ai_string: str = input("Do you want to player with AI or without (y)es or (n)o")
if (ai_string.lower() =="y"):
    ai = True;
elif (ai_string.lower() == "n"):
    ai = False;
else:
    running = False
    print("Failed returning to terminal...")

while running:
    game.print_board()
    column = int(input("Enter column "))
    row = int(input("Enter row "))
    
    choice: tuple[int, int] = (row, column)
    if choice[1] not in range(1, 4):
        print("Failed returning to terminal...")
        running = False
        break
    elif choice[0] not in range(1, 4):
        print("Failed returning to terminal...")
        running = False
        break

    if game.set("X", *choice) == False:
        print("Failed returning to terminal...")
        running = False
        break

    
    if game.check_win() == "":
        if ai:
            ai_choice = (1, 1)
            sett: bool = game.set("O", *ai_choice) # set
            while sett == False:
                if game.set("O", random.randint(1, 3), random.randint(1, 3)):
                    sett = True
        else:
                game.print_board()
                column = int(input("Enter column "))
                row = int(input("Enter row "))
                
                choice: tuple[int, int] = (row, column)
                if choice[1] not in range(1, 4):
                    print("Failed returning to terminal...")
                    running = False
                    break
                elif choice[0] not in range(1, 4):
                    print("Failed returning to terminal...")
                    running = False
                    break

                if game.set("O", *choice) == False:
                    print("Failed returning to terminal...")
                    running = False
                    break

    if game.check_win() != "":
        game.print_board()
        if game.check_win() == "Tie":
            print("The game ended in a Tie. ")
        else:
            print(game.check_win() + " won! ")
        running = False


