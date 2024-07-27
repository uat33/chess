// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"

class Player {
   public:
    Player(Color c);
    Player(Color c, bool init);
    ~Player();
    Piece **getPieces();
    Color getColor() const;
    bool getUnderCheck() const;
    void setUnderCheck(bool x);
    bool isUnderCheck(Piece **grid, Player *opponent) const;
    bool makeMove(int y1, int x1, int y2, int x2, Piece **grid);
    int getMaterial() const;
    void setMaterial(int x);
    void removePiece(int y, int x);
    Player *clone();

   private:
    Piece *pieces[NUMPIECES];
    Color pieceColor;
    int material = 0;
    bool underCheck = false;
};

#endif
