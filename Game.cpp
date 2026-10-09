#include "Game.h"
#include "Board.h"
#include <iostream>
#include <limits>

Game::Game():
    currentPlayer(1)
{}

// 读到合法坐标返回 true，并换算成内部的 0-based；
// 读到非数字就重问；输入断了（Ctrl+Z 或管道喂完）返回 false
bool Game::getPosition(int& row, int& col)
{
    while (true)
    {
        if (std::cin >> row >> col)
        {
            --row;
            --col;
            return true;
        }
        if (std::cin.eof())
            return false;

        std::cin.clear();   // 不清掉失败状态，后面每次 >> 都会直接失败
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   // 丢掉这行剩下的垃圾
        std::cout << "Not a number. Enter row col:\n";
    }
}

void Game::switchPlayer()
{currentPlayer = 3 - currentPlayer;}

void Game::run()
{
    while (true)
    {
        board.print();
        std::cout << "Current player is " << currentPlayer << ". Enter row col:\n";

        int row, col;
        if (!getPosition(row, col))
        {
            std::cout << "\nInput ended. Bye.\n";
            break;
        }

        if (!board.place(row, col, currentPlayer))
        {
            std::cout << "Invalid position. Try again:\n";
            continue;
        }
        if (board.checkWin(row, col))
        {
            board.print();
            std::cout << "Player " << currentPlayer << " Wins!\n";
            break;
        }
        if (board.isFull())
        {
            board.print();
            std::cout << "The board is full. It's a draw!\n";
            break;
        }
        switchPlayer();
    }
}
