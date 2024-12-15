#ifndef UNTITLED8_GAME_4_H
#define UNTITLED8_GAME_4_H
#include "BoardGame_Classes.h"

template <typename T>
class Board_4 : public Board<T> {
public:
    Board_4() {
        this->rows = this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    bool update_board(int x, int y, T mark) override {
        // Only update if move is valid
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
            if (mark == 0){
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(mark);
            }

            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout <<  this->board[i][j] << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
    }

    bool is_win() override {
        ifstream in("dic.txt");
        if (!in) {
            cerr << "Error: Could not open dic.txt" << endl;
            return false;
        }

        set<string> dic;
        string word;
        while (in >> word) {
            dic.insert(word);
        }
        in.close();
        string line;

        // Check rows
        for (int i = 0; i < this->rows; i++) {
            line.clear();
            for (int j = 0; j < this->columns; j++) {
                line += this->board[i][j];
            }
            if (dic.count(line))
                return true;
        }

        // Check columns
        for (int j = 0; j < this->columns; j++) {
            line.clear();
            for (int i = 0; i < this->rows; i++) {
                line += this->board[i][j];
            }
            if (dic.count(line))
                return true;
        }

        // Check diagonals
        line.clear();
        for (int i = 0; i < this->rows; i++) {
            line += this->board[i][i];
        }
        if (dic.count(line))
            return true;

        line.clear();
        for (int i = 0; i < this->rows; i++) {
            line += this->board[i][this->columns - 1 - i];
        }
        if (dic.count(line))
            return true;

        return false;
    }

    bool is_draw(){
        return (this->n_moves == 9 && !is_win());
    }
    bool game_is_over(){
        return is_win() || is_draw();
    }

};

template <typename T>
class Player_4 : public Player<T> {
public:
    Player_4(string name, T symbol) : Player<T>(name, symbol) {
        this->name = name;
        this->symbol = symbol;
    }
    void getSymbol(){
        cout << "\nEnter the character you want to use: ";
        char s;
        cin >> s;
        this->symbol = s;
    }


    void getmove(int& x, int& y) {
        cout << "\nPlease enter your move coordinates (x y) between 0 and 2 separated by spaces: ";
        cin >> x >> y;
        getSymbol();
    }
};

template <typename T>
class Random_Player_4 : public RandomPlayer<T>{
public:
    Random_Player_4(T symbol) : RandomPlayer<T>(symbol){
        this->dimension=3;
        this->symbol=symbol;
        this->name = "Random Computer Player";
        srand(time(0));  // Seed the random number generator
    }
    void getmove(int& x, int& y) {
        cout<<this->dimension<<' ';
        x = rand() %this->dimension;
        y = rand() % this->dimension;
    }

};



#endif