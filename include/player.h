// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"

class Player {
   public:
    Player(Color c);
    Player(Color c, bool init);
    ~Player();
    Player *clone();
    Piece **getPieces();
    Color getColor() const;
    int getMaterial() const;
    void setMaterial(int x);
    bool getUnderCheck() const;
    void setUnderCheck(bool x);
    bool removePiece(int y, int x, Piece **grid);
    bool isUnderCheck(Piece **grid, Player *opponent) const;
    bool makeMove(int y1, int x1, int y2, int x2, Piece **grid);

   private:
    Piece *pieces[NUMPIECES];
    Color pieceColor;
    int material = 0;  // material this player has lost
    bool underCheck = false;
    void promote(Piece **grid, int y, int x, char piece);
    void updatePiece(Piece *p, int y, int x);
};

#endif
