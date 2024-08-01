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


//Storing values for every configuration of boards
struct TTTBoards{
    string boardPos[11][9] = {
        {" "," "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "," "}
    };
} boards;

//Translating simple user input into associated position in each board layout
void equivBoards(){
    boards.boardPos[3][0] = boards.boardPos[6][2] = boards.boardPos[10][0] = boards.boardPos[0][6];
    boards.boardPos[3][1] = boards.boardPos[7][2] = boards.boardPos[0][7];
    boards.boardPos[3][2] = boards.boardPos[8][2] = boards.boardPos[9][2] = boards.boardPos[0][8];
    boards.boardPos[3][3] = boards.boardPos[6][5] = boards.boardPos[10][3] = boards.boardPos[1][6];
    boards.boardPos[3][4] = boards.boardPos[7][5] = boards.boardPos[1][7];
    boards.boardPos[3][5] = boards.boardPos[8][5] = boards.boardPos[9][5] = boards.boardPos[1][8];
    boards.boardPos[3][6] = boards.boardPos[6][8] = boards.boardPos[10][6] = boards.boardPos[2][6];
    boards.boardPos[3][7] = boards.boardPos[7][8] = boards.boardPos[2][7];
    boards.boardPos[3][8] = boards.boardPos[8][8] = boards.boardPos[9][8] = boards.boardPos[2][8];
    boards.boardPos[4][0] = boards.boardPos[6][1] = boards.boardPos[0][3];
    boards.boardPos[4][1] = boards.boardPos[7][1] = boards.boardPos[9][1] = boards.boardPos[10][1] = boards.boardPos[0][4];
    boards.boardPos[4][2] = boards.boardPos[8][1] = boards.boardPos[0][5];
    boards.boardPos[4][3] = boards.boardPos[6][4] = boards.boardPos[1][3];
    boards.boardPos[4][4] = boards.boardPos[7][4] = boards.boardPos[9][4] = boards.boardPos[10][4] = boards.boardPos[1][4];
    boards.boardPos[4][5] = boards.boardPos[8][4] = boards.boardPos[1][5];
    boards.boardPos[4][6] = boards.boardPos[6][7] = boards.boardPos[2][3];
    boards.boardPos[4][7] = boards.boardPos[7][7] = boards.boardPos[9][7] = boards.boardPos[10][7] = boards.boardPos[2][4];
    boards.boardPos[4][8] = boards.boardPos[8][7] = boards.boardPos[2][5];
    boards.boardPos[5][0] = boards.boardPos[6][0] = boards.boardPos[9][0] = boards.boardPos[0][0];
    boards.boardPos[5][1] = boards.boardPos[7][0] = boards.boardPos[0][1];
    boards.boardPos[5][2] = boards.boardPos[8][0] = boards.boardPos[10][2] = boards.boardPos[0][2];
    boards.boardPos[5][3] = boards.boardPos[6][3] = boards.boardPos[9][3] = boards.boardPos[1][0];
    boards.boardPos[5][4] = boards.boardPos[7][3] = boards.boardPos[1][1];
    boards.boardPos[5][5] = boards.boardPos[8][3] = boards.boardPos[10][5] = boards.boardPos[1][2];
    boards.boardPos[5][6] = boards.boardPos[6][6] = boards.boardPos[9][6] = boards.boardPos[2][0];
    boards.boardPos[5][7] = boards.boardPos[7][6] = boards.boardPos[2][1];
    boards.boardPos[5][8] = boards.boardPos[8][6] = boards.boardPos[10][8] = boards.boardPos[2][2];    
}

bool activeGame=true;
bool draw=false;
bool gameOver;
int boardOver;
int selOver;
void fullSelect();

//Base class for both player and computer users
class user{
    public:
        string avatar;
        bool valid=false;
        int posSelection;
        int boardSelection;
        bool win=false;

        //Check if either player or computer have won the game
        int checkWin (){
            int x=0;

            for (x=0; x<11; x++){
                if (boards.boardPos[x][0] == avatar && boards.boardPos[x][1] == avatar && boards.boardPos[x][2] == avatar){
                    win = true;
                } else if (boards.boardPos[x][0] == avatar && boards.boardPos[x][3] == avatar && boards.boardPos[x][6] == avatar){
                    win = true;
                } else if (boards.boardPos[x][0] == avatar && boards.boardPos[x][4] == avatar && boards.boardPos[x][8] == avatar){
                    win = true;
                } else if (boards.boardPos[x][1] == avatar && boards.boardPos[x][4] == avatar && boards.boardPos[x][7] == avatar){
                    win = true;
                } else if (boards.boardPos[x][2] == avatar && boards.boardPos[x][5] == avatar && boards.boardPos[x][8] == avatar){
                    win = true;
                } else if (boards.boardPos[x][3] == avatar && boards.boardPos[x][4] == avatar && boards.boardPos[x][5] == avatar){
                    win = true;
                } else if (boards.boardPos[x][6] == avatar && boards.boardPos[x][7] == avatar && boards.boardPos[x][8] == avatar){
                    win = true;
                } else if (boards.boardPos[x][6] == avatar && boards.boardPos[x][4] == avatar && boards.boardPos[x][2] == avatar){
                    win = true;
                }    
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
        bool checkPlayerValid(){
            if (boards.boardPos[boardSelection-1][posSelection-1] != " "){
            cout << "Position has already been filled! Make another selection.\n";
            valid = false;
            } else {
                valid = true;
            }
            return valid;
        }

        //Player board selection
        void boardSelect(){ 
            int boardOver = 1;
            do{        
                cout << "\nSelect the board to play on (1-3)\n";
                cin >> boardSelection;

                //Check for non-numeric values or values out of range
                if (cin.fail()){
                    cin.clear();
                    cin.ignore();
                    cout << "Not a valid selection, please select another option.\n";
                    continue;
                } else if (boardSelection > 3){
                    cout << "Not a valid selection, please select another option.\n";
                    continue;
                } else if (boardSelection < 1){
                    cout << "Not a valid selection, please select another option.\n";
                    continue;
                } else {
                    boardOver = 0;
                }
            } while (boardOver);
        }    

        //Player postition selection
        void posSelect(){
            int selOver = 1;
            do{
            cout << "\nMake your selection (1-9)\n";
            cin >> posSelection;

            //Check for non-numeric values or values out of range
            if (cin.fail()){
                cin.clear();
                cin.ignore();
                cout << "Not a valid selection, please select another option.\n";
                continue;
            } else if (posSelection > 9){
                cout << "Not a valid selection, please select another option.\n";
                continue;
            } else if (posSelection < 1){
                cout << "Not a valid selection, please select another option.\n";
                continue;
            } else {
                selOver=0;
            }
        } while (selOver);
        }

        //Container function to run board selection and position selection, and then assign value once validated
        void fullSelect(){
            boardSelect();
            posSelect();

            //Add player selection to board after validation
            checkPlayerValid();
            if (valid == true){
                boards.boardPos[boardSelection-1][posSelection-1] = avatar;
                equivBoards();
            } else {
                fullSelect();
            }
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
                boardSelection = (1+(rand()%3));
                posSelection = (1+(rand()%9));
        
                if (boards.boardPos[boardSelection-1][posSelection-1] != " "){
                    valid = 0;
                    continue;
                } else {
                    boards.boardPos[boardSelection-1][posSelection-1] = avatar;
                    valid=1;
                }
            }
        return 1;
        }
};

computer Computer;
player Player;

//Print current tic-tac-toe boards with values
void printBoard(){
    //Top board
    cout << "\n   |   |   \n";
    cout << " " <<boards.boardPos[0][0]<<" | "<<boards.boardPos[0][1]<<" | "<<boards.boardPos[0][2]<<" \n";
    cout << "___|___|___\n";
    cout << "   |   |   \n";
    cout << " " <<boards.boardPos[0][3]<<" | "<<boards.boardPos[0][4]<<" | "<<boards.boardPos[0][5]<<" \n";
    cout << "___|___|___\n";
    cout << "   |   |   \n";
    cout << " " <<boards.boardPos[0][6]<<" | "<<boards.boardPos[0][7]<<" | "<<boards.boardPos[0][8]<<" \n";
    cout << "   |   |   \n";

    //Middle board
    cout << "\n              |   |   \n";
    cout << "            " <<boards.boardPos[1][0]<<" | "<<boards.boardPos[1][1]<<" | "<<boards.boardPos[1][2]<<" \n";
    cout << "           ___|___|___\n";
    cout << "              |   |   \n";
    cout << "            " <<boards.boardPos[1][3]<<" | "<<boards.boardPos[1][4]<<" | "<<boards.boardPos[1][5]<<" \n";
    cout << "           ___|___|___\n";
    cout << "              |   |   \n";
    cout << "            " <<boards.boardPos[1][6]<<" | "<<boards.boardPos[1][7]<<" | "<<boards.boardPos[1][8]<<" \n";
    cout << "              |   |   \n";

    //Bottom board
    cout << "\n                         |   |   \n";
    cout << "                       " <<boards.boardPos[2][0]<<" | "<<boards.boardPos[2][1]<<" | "<<boards.boardPos[2][2]<<" \n";
    cout << "                      ___|___|___\n";
    cout << "                         |   |   \n";
    cout << "                       " <<boards.boardPos[2][3]<<" | "<<boards.boardPos[2][4]<<" | "<<boards.boardPos[2][5]<<" \n";
    cout << "                      ___|___|___\n";
    cout << "                         |   |   \n";
    cout << "                       " <<boards.boardPos[2][6]<<" | "<<boards.boardPos[2][7]<<" | "<<boards.boardPos[2][8]<<" \n";
    cout << "                         |   |   \n";
}

//Check if the game has ended in a tie
int checkTie(){
    int i = 0;
    int a = 0;
    int m = 0;
    
    for (i=0; i<3; i++){
        for (m=0; m<9; m++){
            if (boards.boardPos[i][m] != " "){
                a++;
            }
        }    
    }

    if (a==27){
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

        //Player board and position selection
        Player.fullSelect();

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
