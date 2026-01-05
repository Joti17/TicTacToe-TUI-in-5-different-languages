package Game;
import java.util.Random;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // random(3) gibt 0-49
        Random rand = new Random();
        rand.setSeed(System.currentTimeMillis());
        Scanner in = new Scanner(System.in);
        boolean ai = false;
        System.out.print("Do you want to play with AI? (y)es or (n)o ");
        String ai_string = in.nextLine();
        if (ai_string.toUpperCase().equals("Y")) ai = true;
        else if (ai_string.toUpperCase().equals("N")) ai = false;
        else{
            System.out.println("Failed returning to terminal...");
            System.exit(-1);
        }
        Game game = new Game();
        while(true){
            game.print_board();
            System.out.println("X's turn");
            System.out.print("Enter column ");
            int column = in.nextInt();
            System.out.print("Enter row ");
            int row = in.nextInt();
            int choice[] = {row, column};
            if (choice[0] >= 4 || choice[0] <= 0){
                System.out.println("Failed returning to terminal...");
                System.exit(-1);
            }
            if (choice[1] >= 4 || choice[1] <= 0){
                System.out.println("Failed returning to terminal...");
                System.exit(-1);
            }
            if (!game.set("X", choice[0], choice[1])){
                System.out.println("Failed returning to terminal...");
                System.exit(-2);
            }


            if (game.check_win().equals("")){
                if (ai){
                    boolean sett = false;
                    while(!sett){
                        if(game.set("O", rand.nextInt(3) + 1, rand.nextInt(3) + 1)){
                            sett = true;
                        }
                    }
                }
                else{
                    game.print_board();
                    System.out.println("X's turn");
                    System.out.print("Enter column ");
                    column = in.nextInt();
                    System.out.print("Enter row ");
                    row = in.nextInt();
                    choice[0] = row;
                    choice[1] = column;
                    if (choice[0] >= 4 || choice[0] <= 0){
                        System.out.println("Failed returning to terminal...");
                        System.exit(-1);
                    }
                    if (choice[1] >= 4 || choice[1] <= 0){
                        System.out.println("Failed returning to terminal...");
                        System.exit(-1);
                    }
                    if (!game.set("O", choice[0], choice[1])){
                        System.out.println("Failed returning to terminal...");
                        System.exit(-2);
                    }
                }
            }

            String winner = game.check_win();
            if (!winner.equals("")){
                game.print_board();
                if (winner.equals("Tie")){
                    System.out.println("The game ended in a Tie.");
                }
                else{
                    System.out.printf("\n %s won! \n", winner);
                }
                System.exit(1);
            }
        }
    }
}