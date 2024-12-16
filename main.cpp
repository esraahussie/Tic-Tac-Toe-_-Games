#include "BoardGame_Classes.h"
#include "Game_1.h"
#include "Game_2.h"
#include "Game_3.h"
#include "Game_4.h"
#include "Game_5.h"
#include "Game_6.h"
#include "Game_7.h"
#include "Game_8.h"

// Esraa Hussein Mohamed          id : 20230052
// Samaa Alaa Abdelmaksod         id : 20231077
// Matthew Ashraf                 id : 20230596

int main() {
    cout<<"*** Welcome in our Games ***\n";
    cout << "Please Enter your name to begin: ";
    string name;
    cin >> name;

    cout << "Welcome " << name << " to FCAI X O variations Game\n";
    while(true) {
        cout << "Choose your favorite variation from the menu\n"
             << "1) Pyramid Tic-Tac-Toe\n2) Four-in-a-row\n3) 5 x 5 Tic Tac Toe\n"
             << "4) Word Tic-tac-toe \n5) Numerical Tic-Tac-Toe\n6) Misere Tic Tac Toe"
             << "\n7) 4 x 4 Tic-Tac-Toe\n8) Ultimate Tic Tac Toe\n9) Exit\n" << "Enter your choice : ";

        int variation = 0;
        while (variation < 1 || variation > 9) {
            cin >> variation;
        }
        if (variation == 9) {
            cout << "Exiting the game. Goodbye!" << endl;
            return 0;
        }
        int mode = 0;
        while (mode < 1 || mode > 2) {
            cout << "1) Two players\n2) Random Computer \n Enter your choice : ";
            cin >> mode;
        }
        Player<char> *players[8][2] = {nullptr};
        Board<char> *board[8] = {nullptr};
        GameManager<char> *game[8] = {nullptr};

        if (mode == 1) {
            cout << "Enter Second Player Name: ";
            string secondName;
            cin >> secondName;

            switch (variation) {
                case 1:
                    players[0][1] = new Player_1<char>(secondName, 'O');
                    break;

                case 2:
                    players[1][1] = new FourInARow_Player<char>(secondName, 'O');
                    break;

                case 3:
                    players[2][1] = new _5x5_Player<char>(secondName, 'O');
                    break;

                case 4:
                   players[3][1] = new Player_4<char>(secondName, 'O');
                    break;

                case 5:
                    players[4][1] = new NumTicTacToe_Player<char>(secondName, 2);
                    break;

                case 6:
                   players[5][1] = new X_O_6_Player<char>(secondName, 'O');
                    break;

                case 7:
                    players[6][1] = new Player_7 <char>(secondName, 'O');
                    break;

                case 8:
                    players[7][1] = new UltimateTicTacToe_Player<char>(secondName, 'X');
                    break;
            }
        }
        else if (mode == 2) {
            switch (variation) {
                case 1:
                    players[0][1] = new Random_Player_1<char>('O');
                    break;

                case 2:
                   players[1][1] = new FourInARow_Random_Player<char>('O');
                    break;

                case 3:
                    players[2][1] = new _5x5_Random_Player<char>('O');
                    break;

                case 4:
                    players[3][1] = new Random_Player_4<char>('O');
                    break;

                case 5:
                   players[4][1] = new NumTicTacToe_Random_Player<char>(6);
                    break;

                case 6:
                   players[5][1] = new X_O_6_Random_Player<char>('O');
                    break;

                case 7:
                    players[6][1] = new Random_Player_7 <char>('O');
                    break;
                case 8:
                    players[7][1] = new UltimateTicTacToe_Random_Player<char>('Z');
                    break;
            }
        }

        switch (variation) {
            case 1:
                players[0][0] = new Player_1<char>(name, 'X');
                board[0] = new Board_1<char>();
                game[0] = new GameManager<char>(board[0], players[0]);
                break;

            case 2:
                players[1][0] = new FourInARow_Player<char>(name, 'X');
                board[1] = new FourInARow<char>();
                game[1] = new GameManager<char>(board[1], players[1]);
                break;

            case 3:
                players[2][0] = new _5x5_Player<char>(name, 'X');
                board[2] = new _5x5_Board<char>();
                game[2] = new GameManager<char>(board[2], players[2]);
                break;

            case 4:
                players[3][0] = new Player_4<char>(name, 'X');
                board[3] = new Board_4<char>();
                game[3] = new GameManager<char>(board[3], players[3]);
                break;

            case 5:
                players[4][0] = new NumTicTacToe_Player<char>(name, 'X');
                board[4] = new  NumTicTacToe_Board <char>();
                game[4] = new GameManager<char>(board[4], players[4]);
                break;

            case 6:
                players[5][0] = new X_O_6_Player<char>(name, 'X');
                board[5] = new X_O_6_Board<char>();
                game[5] = new GameManager<char>(board[5], players[5]);
                break;

            case 7:
                players[6][0] = new Player_7<char>(name, 'X');
                board[6] = new Board_7<char>();
                game[6] = new GameManager<char>(board[6], players[6]);
                break;

            case 8:
                players[7][0] = new UltimateTicTacToe_Player <char>(name, 'X');
                board[7] = new UltimateTicTacToeBoard <char>();
                game[7] = new GameManager<char>(board[7], players[7]);
                break;

            default:
                cout << "Selected variation is not yet implemented." << endl;
                return 0;
        }
        
        // Run the selected game
        if (game[variation - 1] != nullptr) {
            game[variation - 1]->run();
        } else {
            cout << "Error: Game Manager not initialized properly." << endl;
        }

        // Clean up resources
        delete board[variation - 1];
        delete players[variation - 1][0];
        delete players[variation - 1][1];
        delete game[variation - 1];

        cout << "Thank you for playing!" << endl;
    }
}