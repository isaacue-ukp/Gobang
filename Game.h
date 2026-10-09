#pragma once
#include "Board.h"

class Game
{
    private:
        Board board;
        int currentPlayer;
        bool getPosition(int& row, int& col);
        void switchPlayer();

    public:
        Game();
        void run();
};
