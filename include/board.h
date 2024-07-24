// board.h

#ifndef BOARD_H
#define BOARD_H

#include "player.h"
#include "util.h"

class Board {
   public:
    Board();
    ~Board();
    void display() const;
    int processMove(const string &s, Color playerturn);

   private:
    Player *white;
    Player *black;
    Piece *grid[DIMENSION * DIMENSION];
};

#endif  // BOARD_H