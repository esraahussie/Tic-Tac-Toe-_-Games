#ifndef _5x5_TIC_TAC_TOE_H
#define _5x5_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;
Player<char> *temp[2];


template <typename T>
class _5x5_Board : public Board<T>
{
public:
    _5x5_Board()
    {
        this->rows = this->columns = 5;
        this->board = new char *[this->rows];
        for (int i = 0; i < this->rows; i++)
        {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++)
            {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    bool update_board(int x, int y, T symbol)
    {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0)
        {
            this->board[x][y] = toupper(symbol);
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board()
    {
        for (int i = 0; i < this->rows; i++)
        {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++)
            {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
    }


bool is_win() {
    if(this->n_moves == 24){
    int player1_count = 0; // To count Player 1's three-in-a-rows
    int player2_count = 0; // To count Player 2's three-in-a-rows

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2]) {
                if (this->board[i][j] == 'X') {
                    player1_count++;
                } else if (this->board[i][j] == 'O') {
                    player2_count++;
                }
            }
        }
    }

    // Check columns
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i <= this->rows - 3; i++) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j] && this->board[i][j] == this->board[i + 2][j]) {
                if (this->board[i][j] == 'X') {
                    player1_count++;
                } else if (this->board[i][j] == 'O') {
                    player2_count++;
                }
            }
        }
    }

    // Check diagonals
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            // Main diagonal
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i][j] == this->board[i + 2][j + 2]) {
                if (this->board[i][j] == 'X') {
                    player1_count++;
                } else if (this->board[i][j] == 'O') {
                    player2_count++;
                }
            }
            // Anti-diagonal
            if (this->board[i][j + 2] != 0 && this->board[i][j + 2] == this->board[i + 1][j + 1] && this->board[i][j + 2] == this->board[i + 2][j]) {
                if (this->board[i][j + 2] == 'X') {
                    player1_count++;
                } else if (this->board[i][j + 2] == 'O') {
                    player2_count++;
                }
            }
        }
    }
   if(player2_count > player1_count ){
      return true;
   } 
   else if(player2_count < player1_count){
    cout << temp[1] << " wins\n";
    exit(0);
   }
   else return false;
    } 
    else return false;
}


    bool is_draw()
    {
        return (this->n_moves == 24 && !is_win());
    }

    bool game_is_over()
    {
        return is_win() || is_draw();
    }
};

template <typename T>
class _5x5_Player : public Player<T>
{
public:
    _5x5_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int &x, int &y)
    {
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
        cin >> x >> y;
    }
};

template <typename T>
class _5x5_Random_Player : public RandomPlayer<T>
{
public:
    _5x5_Random_Player(T symbol) : RandomPlayer<T>(symbol)
    {
        this->dimension = 5;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0))); 
    }

    void getmove(int &x, int &y)
    {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }
};

#endif
