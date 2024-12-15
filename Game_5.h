#ifndef NumTicTacToe_H
#define NumTicTacToe_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class NumTicTacToe_Board : public Board<T> {
public:
    vector <char> odd_symbols = {'1', '3', '5', '7', '9'};
    vector <char> even_symbols = {'2', '4', '6', '8'};
    NumTicTacToe_Board() {
        this->rows = 3;
        this->columns = 3;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }
    void display_board(){
        for (int i = 0; i < this->rows; i++){
            cout << "| ";
            for (int j = 0; j < this->columns; j++){
                cout << this->board[i][j] << " | ";
            }
            cout << endl;
        }
    }
    bool update_board(int x, int y, T symbol) {
        int player_move;
        if (symbol % 2 == 1){
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if ((this->board[i][j] != 0) && (this->board[i][j] % 2 == 1)){
                        for (int w = 0; w < odd_symbols.size(); w++){
                            if (this->board[i][j] == odd_symbols[w]){
                                odd_symbols.erase(odd_symbols.begin() + w);
                            }
                        }
                    }
                }
            }
        }
        if (symbol % 2 == 0){
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if ((this->board[i][j] != 0) && (this->board[i][j] % 2 == 0)){
                        for (int w = 0; w < even_symbols.size(); w++){
                            if (this->board[i][j] == even_symbols[w]){
                                even_symbols.erase(even_symbols.begin() + w);
                            }
                        }
                    }
                }
            }
        }
        
        if (symbol == 1){
            cout << "\nPlease choose a number form these numbers (";
            for (int i = 0; i < odd_symbols.size(); i++){
                cout << " " << odd_symbols[i];
            }
            cout << " ): ";
            cin >> player_move;
            for (int i = 0; i < odd_symbols.size(); i++){
                if ((player_move == odd_symbols[i]) && (this->board[x][y] == 0)){
                    this->board[x][y] = odd_symbols[i];
                    return true;
                }
            }
        }
        else if (symbol == 2){
            cout << "\nPlease choose a number form these numbers (";
            for (int i = 0; i < even_symbols.size(); i++){
                cout << " " << even_symbols[i];
            }
            cout << " ): ";
            cin >> player_move;
            for (int i = 0; i < even_symbols.size(); i++){
                if ((player_move == even_symbols[i]) && (this->board[x][y] == 0)){
                    this->board[x][y] = even_symbols[i];
                    return true;
                }
            }
        }
        else if (symbol == 5){
            player_move = (rand() % 9) + 1;
            for (int i = 0; i < odd_symbols.size(); i++){
                if ((player_move == odd_symbols[i]) && (this->board[x][y] == 0)){
                    this->board[x][y] = odd_symbols[i];
                    return true;
                }
            }
        }
        else if (symbol == 6){
            player_move = (rand() % 9) + 1;
            for (int i = 0; i < even_symbols.size(); i++){
                if ((player_move == even_symbols[i]) && (this->board[x][y] == 0)){
                    this->board[x][y] = even_symbols[i];
                    return true;
                }
            }
        }
        
        return false;
    
    }
    bool is_win() {
        int row_sum = 0;
        int col_sum = 0;
        int diag_sum = 0;
        // Check for horizontal wins
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++){
                if (this->board[i][j] == 0){
                    break;
                }
                else {
                    row_sum += this->board[i][j];
                }
            }
            if (row_sum == 15){return true;}
            row_sum = 0;
        }

        // Check for vertical wins
        for (int j = 0; j < 3; j++){
            for (int i = 0; i < 3; i++){
                if (this->board[i][j] == 0){
                    break;
                }
                else {
                    col_sum += this->board[i][j];
                }
            }
            if (col_sum == 15){return true;}
            col_sum = 0;
        }

        // Check for diagonal wins (top-left to bottom-right)
        for (int i = 0; i < 3; i++){
            if (this->board[i][i] == 0){
                continue;
            }
            else {
                diag_sum += this->board[i][i];
            }
        }
        if (diag_sum == 15){return true;}
        diag_sum = 0;
        // Check for diagonal wins (bottom-left to top-right)
        for (int i = 2; i >= 0; i--){
            if (this->board[i][i] == 0){
                continue;
            }
            else {
                diag_sum += this->board[i][i];
            }
        }
        if (diag_sum == 15){return true;}

        return false;
    }
    bool is_draw(){
        bool done = true;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (this->board[i][j] == 0){
                    done = false;
                }
            }
        }
        if (done && !is_win()){
            return true;
        }
        else {
            return false;
        }
    }
    bool game_is_over() {
        return is_win() || is_draw();
    }
};

template <typename T>
class NumTicTacToe_Player : public Player<T> {
public:
    NumTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol){}
    NumTicTacToe_Player(T symbol) : Player<T>(symbol){}
    void getmove(int& x, int& y) {
        cout << "\nPlease enter your move x (row) and y (column) separated by spaces: ";
        cin >> x >> y;
    }
};

// random_player class
template <typename T>
class NumTicTacToe_Random_Player : public RandomPlayer<T>{
public:
    NumTicTacToe_Random_Player (T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    }
    void getmove(int &x, int &y){
        x = rand() % this->dimension; // Random number between 0 and 2
        y = rand() % this->dimension; // Random number between 0 and 2
    }
};

/*
int main() {
    int choice;
    Player<int>* players[2];
    NumTicTacToe_Board<int>* B = new NumTicTacToe_Board<int>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new NumTicTacToe_Player<int>(playerXName, 1);
            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[1] = new NumTicTacToe_Player<int>(player2Name, 2);
                    break;
                case 2:
                    players[1] = new NumTicTacToe_Random_Player<int>(6);
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }
            break;
        case 2:
            players[0] = new NumTicTacToe_Random_Player<int>(5);
            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[1] = new NumTicTacToe_Player<int>(player2Name, 2);
                    break;
                case 2:
                    players[1] = new NumTicTacToe_Random_Player<int>(6);
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<int> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
*/

#endif
