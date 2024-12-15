#ifndef FourInARow_H
#define FourInARow_H

#include "BoardGame_Classes.h"

#include <iostream>
using namespace std;

/*
   0 1 2 3 4 5 6
   _ _ _ _ _ _ _
0| 0 0 0 0 0 0 0 
1| 0 0 0 0 0 0 0
2| 0 0 0 0 0 0 0
3| 0 0 0 0 0 0 0
4| 0 0 0 0 0 0 0
5| 0 0 0 0 0 0 0
*/


//board class
template <typename T>
class FourInARow : public Board<T> {
public:
    FourInARow() {
        this->rows = 6;
        this->columns = 7;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
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
        if (this->board[x][y] != 0) {
            return false; // Cell is already occupied
        }
        for (int i = this->rows - 1; i >= 0; --i) {
            if (this->board[i][y] == 0) {
                this->board[i][y] = symbol; // Place the symbol in the first empty space
                return true;
            }
        }
        return false; // Column is full
    }
    bool is_win() {
        // Check for horizontal wins
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 3; j++) {
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i][j+1] &&
                    this->board[i][j] == this->board[i][j+2] &&
                    this->board[i][j] == this->board[i][j+3]) {
                    return true;
                }
            }
        }

        // Check for vertical wins
        for (int i = 0; i < this->rows - 3; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i+1][j] &&
                    this->board[i][j] == this->board[i+2][j] &&
                    this->board[i][j] == this->board[i+3][j]) {
                    return true;
                }
            }
        }

        // Check for diagonal wins (top-left to bottom-right)
        for (int i = 0; i < this->rows - 3; i++) {
            for (int j = 0; j < this->columns - 3; j++) {
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i+1][j+1] &&
                    this->board[i][j] == this->board[i+2][j+2] &&
                    this->board[i][j] == this->board[i+3][j+3]) {
                    return true;
                }
            }
        }

        // Check for diagonal wins (bottom-left to top-right)
        for (int i = 3; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 3; j++) {
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i-1][j+1] &&
                    this->board[i][j] == this->board[i-2][j+2] &&
                    this->board[i][j] == this->board[i-3][j+3]) {
                    return true;
                }
            }
        }

        return false;
    }
    bool is_draw(){
        bool done = true;
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 7; j++){
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

//player class
template <typename T>
class FourInARow_Player : public Player<T> {
public:
    FourInARow_Player(string name, T symbol) : Player<T>(name, symbol){}
    FourInARow_Player(T symbol) : Player<T>(symbol){}
    void getmove(int& x, int& y) {
        cout << "\nPlease enter your move x (row) and y (column) separated by spaces: ";
        cin >> x >> y;
    }

};

// random_player class
template <typename T>
class FourInARow_Random_Player : public RandomPlayer<T>{
public:
    FourInARow_Random_Player (T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 7;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    }
    void getmove(int &x, int &y){
        x = rand() % (this->dimension - 1);  // Random number between 0 and 5
        y = rand() % this->dimension; // Random number between 0 and 6
    }
};

#endif