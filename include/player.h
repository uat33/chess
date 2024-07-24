// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"

class Player {
   public:
    Player(Color c);
    ~Player();
    Piece **getPieces();

   private:
    Piece *pieces[NUMPIECES];
    Color pieceColor;
    int numpieces = NUMPIECES;
    int material = 0;
    void removePiece(int y, int x);
};

#endif
