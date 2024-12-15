#ifndef UNTITLED8_GAME_1_H
#define UNTITLED8_GAME_1_H
#include "BoardGame_Classes.h"

template <typename T>
class Board_1 : public Board<T> {
public:
    Board_1() {
        this->rows = 3;
        this->columns = 5;
        this->board = new char*[this->rows];

        // Initialize rows with increasing number of cells
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[2 * i + 1];
            for (int j = 0; j < 2 * i + 1; j++) {
                this->board[i][j] = 0;  // Empty cell
            }
        }
        this->n_moves = 0;
    }

    ~Board_1() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (x >= 0 && x < this->rows && y >= 0 && y < (2 * x + 1) && this->board[x][y] == 0) {
            this->board[x][y] = symbol;
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < this->rows; i++) {
            cout << string((this->columns - (2 * i + 1)) / 2, ' ');
            for (int j = 0; j < (2 * i + 1); j++) {
                cout << (this->board[i][j] == 0 ? '-' : this->board[i][j]) << " ";
            }
            cout << endl;
        }
    }

    bool is_win() {
        // Check rows
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < (2 * i + 1) - 2; j++) {
                if (this->board[i][j] == this->board[i][j + 1] && this->board[i][j + 1] == this->board[i][j + 2] && this->board[i][j] != 0) {
                    return true;
                }
            }
        }

        // Check vertical columns (aligned visually)
        for (int col = 0; col < this->columns; col++) {
            for (int row = 0; row < this->rows - 2; row++) {
                if (col < (2 * row + 1) && col < (2 * (row + 1) + 1) && col < (2 * (row + 2) + 1) &&
                    this->board[row][col] == this->board[row + 1][col] &&
                    this->board[row + 1][col] == this->board[row + 2][col] &&
                    this->board[row][col] != 0) {
                    return true;
                }
            }
        }

        // Check diagonals (left-to-right)
        for (int i = 0; i < this->rows - 2; i++) {
            for (int j = 0; j < (2 * i + 1); j++) {
                if (j < (2 * (i + 1) + 1) && j + 1 < (2 * (i + 2) + 1) && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i + 1][j + 1] == this->board[i + 2][j + 2] && this->board[i][j] != 0) {
                    return true;
                }
                if (j + 2 < (2 * (i + 1) + 1) && j + 2 < (2 * (i + 2) + 1) && this->board[i][j + 2] == this->board[i + 1][j + 1] && this->board[i + 1][j + 1] == this->board[i + 2][j] && this->board[i][j + 2] != 0) {
                    return true;
                }
            }
        }

        return false;
    }


    bool is_draw() {
        return (this->n_moves == 9 && !is_win());
    }

    bool game_is_over() {
        return is_win() || is_draw();
    }
};

template <typename T>
class Player_1 : public Player<T> {
public:
    Player_1(string name, T symbol) : Player<T> (name,symbol) {
        this->name = name;
        this->symbol = symbol;
    }

    void getmove(int &x, int &y) override {
        while (true) {
            cout << "Enter your move (row column): ";
            cin >> x >> y;
            if (x >= 0 && x < 3 && y >= 0 && y < (2 * x + 1)) {
                break;
            }
            cout << "Invalid move. Try again.\n";
        }
    }
};

template <typename T>
class Random_Player_1 : public RandomPlayer<T> {
private:
    char randomLetter;
public:
    Random_Player_1(T symbol): RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->symbol = symbol;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned>(time(0)));
    }

    void getmove(int &x, int &y) override {
        while (true) {
            x = rand() % this->dimension;  // Row
            y = rand() % (2 * x + 1);  // Column within that row
            if (x >= 0 && x <this->dimension && y >= 0 && y < (2 * x + 1)) {
                randomLetter = 'A' + (rand() % 26);
                cout << "Random Letter: " << randomLetter << std::endl;
                break;
            }
        }
    }

};


#endif