// board.h

#ifndef BOARD_H
#define BOARD_H

#include "player.h"

class Board {
   public:
    Board();
    ~Board();
    void display() const;

   private:
    Player *white;
    Player *black;
    Piece *grid[DIMENSION * DIMENSION];
};

#endif  // BOARD_H