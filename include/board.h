// board.h

#ifndef BOARD_H
#define BOARD_H

#include "player.h"
#include "util.h"

class Board {
   public:
    Board();
    ~Board();
    void display(Color c) const;
    void setBoardCopy();
    Board *revertBoard();
    int processMove(const string &s, Color playerturn);
    Board *clone();
    Player *white;

   private:
    Player *black;
    Piece *grid[DIMENSION * DIMENSION];
    Piece *lastMoved = nullptr;
    Board *boardCopy;
};

#endif  // BOARD_H
