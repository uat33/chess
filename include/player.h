// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"

class Player {
   public:
    Player(Color c);
    ~Player();
    Piece **getPieces();
    bool getUnderCheck();
    void setUnderCheck(bool x);
    bool makeMove(int y1, int x1, int y2, int x2, Piece **grid,
                  Player *opponent);
    Color getColor();
    bool isUnderCheck(Piece **grid, Player *opponent);

   private:
    Piece *pieces[NUMPIECES];
    Color pieceColor;
    int numpieces = NUMPIECES;
    int material = 0;
    void removePiece(int y, int x);
    bool underCheck = false;
};

#endif
