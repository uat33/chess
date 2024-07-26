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
    void setGridCopy();
    void revertBoard();
    void revertPlayers();

   private:
    Player *white;
    Player *black;
    Piece *grid[DIMENSION * DIMENSION];
    Piece *lastMoved = nullptr;
    Piece *gridCopy[DIMENSION * DIMENSION];
};

#endif  // BOARD_H
