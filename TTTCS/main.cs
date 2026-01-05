
namespace Game
{
    public class main {
        public static void Main(string[] args) {
            // random(3) gibt 0-49
            Random rand = new Random(System.DateTime.Now.Millisecond);
            bool ai = false;
            Console.Write("Do you want to play with AI? (y)es or (n)o ");
            string ai_string = Console.ReadLine();
            if (ai_string.ToUpper().Equals("Y")) ai = true;
            else if (ai_string.ToUpper().Equals("N")) ai = false;
            else{
                Console.WriteLine("Failed returning to terminal...");
                Environment.Exit(-1);
            }
            Game game = new Game();
            while(true){
                game.print_board();
                Console.WriteLine("X's turn");
                Console.Write("Enter column ");
                int column = Convert.ToInt32(Console.ReadLine());
                Console.Write("Enter row ");
                int row = Convert.ToInt32(Console.ReadLine());
                int[] choice = {row, column};
                if (choice[0] >= 4 || choice[0] <= 0){
                    Console.WriteLine("Failed returning to terminal...");
                    Environment.Exit(-1);
                }
                if (choice[1] >= 4 || choice[1] <= 0){
                    Console.WriteLine("Failed returning to terminal...");
                    Environment.Exit(-1);
                }
                if (!game.set("X", choice[0], choice[1])){
                    Console.WriteLine("Failed returning to terminal...");
                    Environment.Exit(-2);
                }


                if (game.check_win().Equals("")){
                    if (ai){
                        bool sett = false;
                        while(!sett){
                            if(game.set("O", rand.Next(3) + 1, rand.Next(3) + 1)){
                                sett = true;
                            }
                        }
                    }
                    else{
                        game.print_board();
                        Console.WriteLine("O's turn");
                        Console.Write("Enter column ");
                        column = Convert.ToInt32(Console.ReadLine());
                        Console.Write("Enter row ");
                        row = Convert.ToInt32(Console.ReadLine());
                        choice[0] = row;
                        choice[1] = column;
                        if (choice[0] >= 4 || choice[0] <= 0){
                            Console.WriteLine("Failed returning to terminal...");
                            Environment.Exit(-1);
                        }
                        if (choice[1] >= 4 || choice[1] <= 0){
                            Console.WriteLine("Failed returning to terminal...");
                            Environment.Exit(-1);
                        }
                        if (!game.set("O", choice[0], choice[1])){
                            Console.WriteLine("Failed returning to terminal...");
                            Environment.Exit(-2);
                        }
                    }
                }

                String winner = game.check_win();
                if (!winner.Equals("")){
                    game.print_board();
                    if (winner.Equals("Tie")){
                        Console.WriteLine("The game ended in a Tie.");
                    }
                    else{
                        Console.WriteLine("\n {0} won! \n", winner);
                    }
                    Environment.Exit(1);
                }
            }
        }
    }
}