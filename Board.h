#pragma once
#include <vector>

class Board
{
    private:
        int size;
        std::vector<std::vector<int>> cells;   // cells[row][col]，0 空 / 1 黑 / 2 白
        bool inBoard(int row, int col) const;
        int countDirection(int row, int col, int drow, int dcol) const;

    public:
        Board(int size = 15);
        bool place(int row, int col, int player);
        bool isEmpty(int row, int col) const;
        bool checkWin(int row, int col) const;
        bool isFull() const;
        void print() const;
};
