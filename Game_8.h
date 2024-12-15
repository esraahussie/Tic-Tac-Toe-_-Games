#ifndef UltimateTicTacToe_H
#define UltimateTicTacToe_H
#include "BoardGame_Classes.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// note: when implementing in the main.cpp the random player's symbol is 'Z'

template <typename T>
class TicTacToeBoard : public Board<T> {
public:
    TicTacToeBoard() {
        this->rows = this->columns = 3;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = ' '; // empty space
            }
        }
    }

    bool update_board(int x, int y, T symbol) override {
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && this->board[x][y] == ' ') {
            this->board[x][y] = symbol;
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < 3; ++i) {
            cout << "|";
            for (int j = 0; j < 3; ++j) {
                cout << this->board[i][j] << " |";
            }
            cout << endl;
        }
    }

    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ') {
                return true;
            }
            if (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' ') {
                return true;
            }
        }
        if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ') {
            return true;
        }
        if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ') {
            return true;
        }
        return false;
    }

    bool is_draw() override {
        return this->n_moves == 9;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class UltimateTicTacToeBoard : public Board<T> {
private:
    TicTacToeBoard<T> smallBoards[3][3];
    vector<vector<T>> mainBoard;  // 3x3 array of 'X'/'O' marks for the main board

public:
    UltimateTicTacToeBoard() {
        this->rows = this->columns = 3;
        mainBoard.resize(3, vector<T>(3, ' '));  // Initialize the main board with empty spaces
    }

    bool update_board(int x, int y, T symbol) override {
        int subX, subY;
        if (symbol == 'Z'){
            subX = rand() % 3;
            subY = rand() % 3;
        }
        else{
            cout << "\nPlease enter your move for sub-board (" << x << "," << y << "): ";
            cin >> subX >> subY;
        }
        if (mainBoard[x][y] == ' ' && smallBoards[x][y].update_board(subX, subY, symbol)) {
            if (smallBoards[x][y].is_win()) {
                mainBoard[x][y] = symbol;
            }
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "main board: " << endl;
        for (int i = 0; i < 3; ++i) {
            cout << "|";
            for (int j = 0; j < 3; ++j) {
                cout << mainBoard[i][j] << " |";
            }
            cout << endl;
        }
        cout << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << "board (" << i << ", " << j << ")" << endl;
                smallBoards[i][j].display_board();
                cout << "------\n";
            }
        }
    }

    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            if (mainBoard[i][0] == mainBoard[i][1] && mainBoard[i][1] == mainBoard[i][2] && mainBoard[i][0] != ' ') {
                return true;
            }
            if (mainBoard[0][i] == mainBoard[1][i] && mainBoard[1][i] == mainBoard[2][i] && mainBoard[0][i] != ' ') {
                return true;
            }
        }
        if (mainBoard[0][0] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][2] && mainBoard[0][0] != ' ') {
            return true;
        }
        if (mainBoard[0][2] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][0] && mainBoard[0][2] != ' ') {
            return true;
        }
        return false;
    }

    bool is_draw() override {
        return !is_win() && all_of(mainBoard.begin(), mainBoard.end(), [](const vector<T>& row) {
            return all_of(row.begin(), row.end(), [](T cell) { return cell != ' '; });
        });
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class UltimateTicTacToe_Player : public Player<T> {
public:
    UltimateTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol){}
    UltimateTicTacToe_Player(T symbol) : Player<T>(symbol){}
    void getmove(int& x, int& y) {
        cout << "\nchoose which small board you want to choose";
        cout << "\nPlease enter your move x (row) and y (column) separated by spaces: ";
        cin >> x >> y;
    }
};

// random_player class
template <typename T>
class UltimateTicTacToe_Random_Player : public RandomPlayer<T>{
public:
    UltimateTicTacToe_Random_Player (T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    }
    void getmove(int &x, int &y){
        x = rand() % this->dimension;  // Random number between 0 and 2
        y = rand() % this->dimension; // Random number between 0 and 2
    }
};


#endif