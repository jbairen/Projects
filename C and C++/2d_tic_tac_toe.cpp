#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
//#include <windows.h>
#include <unistd.h>

/*This is a interactive code using C language coded on 03/29/2024 for the Intro to C and C++
course by Dr. Roman V. Yampolskiy by Bethanie Bairen
*/
using std::string;
using std::cout;
using std::cin;


//Storing board values
struct TTTBoard{
    string pos[9] = {" "," "," "," "," "," "," "," "," "};
} board;

bool activeGame=true;
bool draw=false;
bool gameOver;

//Base class for both player and computer users
class user{
    public:
        string avatar;
        bool valid=false;
        int selection;
        bool win=false;

        //Check if either player or computer have won the game
        int checkWin (){

            if (board.pos[0] == avatar && board.pos[1] == avatar && board.pos[2] == avatar){
                win = true;
            } else if (board.pos[0] == avatar && board.pos[3] == avatar && board.pos[6] == avatar){
                win = true;
            } else if (board.pos[0] == avatar && board.pos[4] == avatar && board.pos[8] == avatar){
                win = true;
            } else if (board.pos[1] == avatar && board.pos[4] == avatar && board.pos[7] == avatar){
                win = true;
            } else if (board.pos[2] == avatar && board.pos[5] == avatar && board.pos[8] == avatar){
                win = true;
            } else if (board.pos[3] == avatar && board.pos[4] == avatar && board.pos[5] == avatar){
                win = true;
            } else if (board.pos[6] == avatar && board.pos[7] == avatar && board.pos[8] == avatar){
                win = true;
            } else if (board.pos[6] == avatar && board.pos[4] == avatar && board.pos[2] == avatar){
                win = true;
            }
    
            return win;
        }
         
};

//Sub-class for player-specific functions
class player : public user{
    public:

    //Ask user for avatar choice and assign either X or O to user and vice-versa for computer
    void playerChoice(){
            bool validPlayer=false;

            while (!validPlayer){
        
                cout << "\nMake your selection: X or O\n";
                cin >> avatar;

                if (avatar == "X"){
                    validPlayer=true;
                    avatar="O";
                } else if (avatar == "x") {
                    validPlayer=true;
                    avatar = "X";
                } else if (avatar == "O") {
                    validPlayer=true;
                    avatar="X";
                } else if (avatar == "o") {
                    validPlayer=true;
                    avatar = "O";
                } else {
                    cout << "\nPlease enter a valid selection.\n";
                    continue;
                }
            }
        }

        //Ask user for input and validate that the selected field has not been filled already
        int checkPlayerValid(){
            if (board.pos[selection-1] != " "){
            cout << "Position has already been filled! Make another selection.\n";
            valid = 0;
            } else {
                valid = 1;
            }
            return valid;
}
};

//Sub-class for computer-specific functions
class computer : public user{
    public:

        //Random position selection for computer, 
        //validating that it is not trying to override a filled position
        int compSelection(){
        srand(time(NULL));
        valid=0;

            while (valid == 0){
                selection = (1+(rand()%9));
        
                if (board.pos[selection-1] != " "){
                    valid = 0;
                    continue;
                } else {
                    board.pos[selection-1] = avatar;
                    valid=1;
                }
            }
        return 1;
        }
};

computer Computer;
player Player;

//Print current tic-tac-toe board with values
void printBoard(){
    cout << "\n   |   |   \n";
    cout << " " <<board.pos[0]<<" | "<<board.pos[1]<<" | "<<board.pos[2]<<" \n";
    cout << "___|___|___\n";
    cout << "   |   |   \n";
    cout << " " <<board.pos[3]<<" | "<<board.pos[4]<<" | "<<board.pos[5]<<" \n";
    cout << "___|___|___\n";
    cout << "   |   |   \n";
    cout << " " <<board.pos[6]<<" | "<<board.pos[7]<<" | "<<board.pos[8]<<" \n";
    cout << "   |   |   \n";
}

//Check if the game has ended in a tie
int checkTie(){
    int i = 0;
    int x = 0;
   
    for (i=0; i<9; i++){
        if (board.pos[i] != " "){
            x++;
        }
    }

    if (x==9){
        cout << "\nMatch has ended in a draw! Please play again.\n";
        draw = true;
        activeGame = false;
    }
    return draw;
}

//Function to run through different win checks and determine final result of game
void checkRes(){
    gameOver=false;
    Player.checkWin();
    if(!Player.win){
        Computer.checkWin();
    } else if (Player.win){
        printBoard();
        gameOver=true;
    }
    if(!Player.win && !Computer.win){
        checkTie();
    } else if (Computer.win){
        printBoard();
        gameOver=true;
    }
    if (draw){
        printBoard();
        gameOver=true;
    }
}

//Function to output win results and end game
void endWin(){
    if (Player.win){
        cout << "\nCongratulations, you win! Good game.\n";
        activeGame = false;
    } else if (Computer.win){
        cout << "\nComputer wins. Good game, please play again!\n";
        activeGame=false;
    } else if (draw){
        cout << "\nGame has ended in a draw! Good game, please play again!\n";
        activeGame=false;
    }
}

int main (){
    //Randomly select whether the player moves first or the computer
    srand(time(NULL));
    int playerStart = (rand()&1);

    cout << "Welcome to Tic-Tac-Toe\n";

    Player.playerChoice();

    if (Player.avatar=="X"){
        Computer.avatar="O";
    } else {
        Computer.avatar="X";
    }

    while (activeGame){
        int selOver = 1;
        //Process runs if computer starts game
        if (playerStart==0){
            cout << "\nComputer's turn.\n";
            sleep(2);
            Computer.compSelection();

            //Check if computer wins
            checkRes();
            endWin();
            if (gameOver){
                break;
            }
        }
           
        printBoard();

        //Player position selection
        while (selOver){
            cout << "\nMake your selection (1-9)\n";
            cin >> Player.selection;

            //Check for non-numeric values or values out of range
            if (cin.fail()){
                cin.clear();
                cin.ignore();
                cout << "Not a valid selection, please select another option.\n";
                continue;
            } else if (Player.selection > 9){
                cout << "Not a valid selection, please select another option.\n";
                continue;
            } else if (Player.selection < 1){
                cout << "Not a valid selection, please select another option.\n";
                continue;
            }
        
            //Add player selection to board
            Player.checkPlayerValid();
            if (Player.valid == 1){
                board.pos[Player.selection-1] = Player.avatar;
                selOver=0;
            } else {
                continue;
            } 
        }

        //Check if player wins
        checkRes();
        endWin();
        if (gameOver){
            break;
        }
        
        printBoard();

        //Process runs if player started first
        if (playerStart==1){
            cout << "\nComputer's turn.\n";
            sleep(2);
            Computer.compSelection();

            //Check if computer wins
            checkRes();
            endWin();
            if (gameOver){
                break;
            }
        }
    }
    system("pause");
    return 0;
}
