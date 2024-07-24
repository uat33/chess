// piece.h

#ifndef PIECE_H
#define PIECE_H

#include <cmath>
#include <iostream>

#include "colors.h"
#include "definitions.h"
#include "util.h"

class Piece {
   public:
    Piece(int y = 0, int x = 0, Color c = Color::WHITE,
          PieceType t = PieceType::PAWN);

    virtual ~Piece();
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    PieceType getType() const;
    Color getColor() const;
    virtual void display(Color c) const;
    virtual bool isValidMove(int y, int x, Piece **grid) = 0;
    bool getJustMoved() const;
    void setJustMoved(bool x);

   protected:
    PieceType type;
    Color color;
    int y;
    int x;
    bool justMoved = false;
};

class Pawn : public Piece {
   public:
    Pawn(int y, int x, Color c);
    bool isValidMove(int y, int x, Piece **grid) override;
    bool getJustMovedTwo();
    void setJustMovedTwo(bool x);

   private:
    bool justMovedTwo = false;
};

class Knight : public Piece {
   public:
    Knight(int y, int x, Color c);
    bool isValidMove(int y, int x, Piece **grid) override;
};

class Bishop : public Piece {
   public:
    Bishop(int y, int x, Color c);
    bool isValidMove(int y, int x, Piece **grid) override;
};

class Queen : public Piece {
   public:
    Queen(int y, int x, Color c);
    bool isValidMove(int y, int x, Piece **grid) override;
};

class Rook : public Piece {
   public:
    Rook(int y, int x, Color c);
    bool isValidMove(int y, int x, Piece **grid) override;
    bool getHasMoved();
    void setHasMoved(bool x);

   private:
    bool hasMoved = false;
};

class King : public Piece {
   public:
    King(int y, int x, Color c);
    void setCheck(bool check);
    void display(Color c) const override;
    bool isValidMove(int y, int x, Piece **grid) override;

   private:
    bool underCheck = false;
    bool hasMoved = false;
};

string pieceString(PieceType t);
#endif  // PIECE_H
