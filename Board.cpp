#include <iostream>
#include <iomanip>
#include "Board.h"

bool Board::inBoard(int row, int col) const
{return 0 <= row && row < size && 0 <= col && col < size;}

Board::Board(int size):
    size(size)
{cells.resize(size, std::vector<int>(size, 0));}

bool Board::place(int row, int col, int player)
{
    if (!inBoard(row, col) || !isEmpty(row, col))
        return false;

    cells[row][col] = player;
    return true;
}

bool Board::isEmpty(int row, int col) const
{
    if (!inBoard(row, col))
        return false;

    return cells[row][col] == 0;
}

int Board::countDirection(int row, int col, int drow, int dcol) const
{
    int count = 0;
    int step = 1;

    while (inBoard(row + step * drow, col + step * dcol)
        && cells[row + step * drow][col + step * dcol] == cells[row][col])
    {count++; step++;}
    step = -1;
    while (inBoard(row + step * drow, col + step * dcol)
        && cells[row + step * drow][col + step * dcol] == cells[row][col])
    {count++; step--;}
    count++;

    return count;
}

bool Board::checkWin(int row, int col) const
{
    return (countDirection(row, col, 0, 1) > 4
         || countDirection(row, col, 1, 1) > 4
         || countDirection(row, col, 1, 0) > 4
         || countDirection(row, col, 1, -1) > 4);
}

bool Board::isFull() const
{
    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
            if (isEmpty(row, col))
                return false;
    return true;
}

void Board::print() const
{
    // 顶部列号：每列占 3 个字符（"01 "），跟下面每格的宽度对齐
    std::cout << "   ";
    for (int col = 1; col <= size; ++col)
        std::cout << std::setw(2) << std::setfill('0') << col << ' ';
    std::cout << '\n';

    for (int row = 0; row < size; ++row)
    {
        // 左侧行号
        std::cout << std::setw(2) << std::setfill('0') << row + 1 << ' ';
        for (int col = 0; col < size; ++col)
        {
            if (cells[row][col] == 0)
                std::cout << "   ";
            else
                std::cout << (cells[row][col] == 1 ? "## " : "[] ");
        }
        std::cout << '\n';
    }

    std::cout << std::setfill(' ');   // setfill 是粘的，用完还原成默认
}
