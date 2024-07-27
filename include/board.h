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
    int processMove(const string &s, Color playerturn);
    Board *clone();

   private:
    Player *black;
    Player *white;
    Piece *grid[DIMENSION * DIMENSION];
    Piece *lastMoved = nullptr;
    Board *boardCopy;
};

#endif  // BOARD_H
