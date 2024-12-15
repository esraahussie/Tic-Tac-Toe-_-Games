#ifndef UNTITLED8_GAME_7_H
#define UNTITLED8_GAME_7_H
#include "BoardGame_Classes.h"

template <typename T>
class Board_7 : public Board<T> {
public:
    Board_7() {
        this->rows = this->columns = 4;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        // Player X tokens
        this->board[0][1] = 'X';
        this->board[0][3] = 'X';
        this->board[3][0] = 'X';
        this->board[3][2] = 'X';

        // Player O tokens
        this->board[0][0] = 'O';
        this->board[0][2] = 'O';
        this->board[3][1] = 'O';
        this->board[3][3] = 'O';

        this->n_moves = 0;
    }

    bool update_board(int x, int y, T mark) override {
        int newX = x, newY = y;
        int choice;
        cout << "\nEnter the choice:\n1) Left\n2) Right\n3) Up\n4) Down\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: // Left
                newY--;
                break;
            case 2: // Right
                newY++;
                break;
            case 3: // Up
                newX--;
                break;
            case 4: // Down
                newX++;
                break;
            default:
                cout << "Invalid choice!";
                return false;
        }

        // Check if new coordinates are within bounds
        if (newX < 0 && newX >= 4 && newY < 0 && newY >= 4) {
            cout << "Move out of bounds. Try again." << endl;
            return false;
        }
        // Only update if move is valid
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == toupper(mark)) && this->board[newX][newY] == 0) {
            this->n_moves++;
            this->board[newX][newY] = toupper(mark);
            this->board[x][y] = 0;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << this->board[i][j] << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
    }

    bool is_win() override {
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
                (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
                return true;
            }
        }

        // Check diagonals
        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0) ||
            (this->board[0][3] == this->board[1][2] && this->board[1][2] == this->board[2][1] && this->board[0][3] != 0) ||
            (this->board[1][3] == this->board[2][2] && this->board[2][2] == this->board[3][1] && this->board[1][3] != 0) ||
            (this->board[2][3] == this->board[1][2] && this->board[1][2] == this->board[0][1] && this->board[2][3] != 0) ||
            (this->board[3][3] == this->board[2][2] && this->board[2][2] == this->board[1][1] && this->board[3][3] != 0) ||
            (this->board[3][0] == this->board[2][1] && this->board[2][1] == this->board[1][2] && this->board[3][0] != 0) ||
            (this->board[1][0] == this->board[2][1] && this->board[2][1] == this->board[3][2] && this->board[1][0] != 0)){

            return true;
        }

        return false;
    }

    bool is_draw(){
        return (this->n_moves == 16 && !is_win());
    }
    bool game_is_over(){
        return is_win() || is_draw();
    }

};

template <typename T>
class Player_7 : public Player<T> {
public:
    Player_7(string name, T symbol) : Player<T>(name,symbol){
        this->name = name;
        this->symbol = symbol;
    }

    void getmove(int& x, int& y) {
        cout << "\nPlease enter your move coordinates (x y) between 0 and 2 separated by spaces: ";
        cin >> x >> y;
    }

};

template <typename T>
class Random_Player_7: public RandomPlayer<T>{
public:
    Random_Player_7(T symbol) : RandomPlayer<T>(symbol){
        this->dimension=4;
        this->symbol = symbol;
        this->name = "Random Computer Player";
        srand(time(0));  // Seed the random number generator
    }
    void getmove(int& x, int& y) {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }

};


#endif