#ifndef _GAME_6_H
#define _GAME_6_H
#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;
//Player<char> *temp[2];

template <typename T>
class X_O_6_Board : public Board<T>
{
public:
    X_O_6_Board()
    {
        this->rows = this->columns = 3;
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
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || symbol == 0))
        {
            if (symbol == 0)
            {
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else
            {
                this->n_moves++;
                this->board[x][y] = toupper(symbol);
            }

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
    bool is_win()
    {
        for (int i = 0; i < this->rows; i++)
        {
            if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
                (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0))

            { 
                if(this->board[i][0] == 'O'  || this->board[0][i] == 'O'){
                    cout << temp[1]->getname() << " loses\n";
                    exit(0);
                }
                 else if(this->board[i][0] == 'X'  || this->board[0][i] == 'X'){
                    cout << temp[0]->getname() << " loses\n";
                     exit(0);
                }
                return true;
            }
        }

        // Check diagonals
        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0))
        {   
            if(this->board[0][0] == 'O'  || this->board[0][2] == 'O'){
                    cout << temp[1]->getname() << " loses\n";
                    exit(0);
                }
                 else if(this->board[0][2] == 'X'  || this->board[0][0] == 'X'){
                    cout << temp[0]->getname() << " loses\n";
                     exit(0);
                }
            return true;
        }

        return false;
    }
    bool is_draw()
    {
        return (this->n_moves == 9 && !is_win());
    }
    bool game_is_over()
    {
        return is_win() || is_draw();
    }
};

template <typename T>
class X_O_6_Player : public Player<T>
{
public:
    X_O_6_Player(string name, T symbol) : Player<T>(name, symbol) {}
    void getmove(int &x, int &y)
    {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;
    }
};

template <typename T>
class X_O_6_Random_Player : public RandomPlayer<T>
{
public:
    X_O_6_Random_Player(T symbol) : RandomPlayer<T>(symbol)
    {
        this->dimension = 3;
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