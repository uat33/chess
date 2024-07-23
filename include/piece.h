// piece.h

#ifndef PIECE_H
#define PIECE_H

#include <iostream>

#include "colors.h"
#include "definitions.h"
class Piece {
   public:
    Piece(int y = 0, int x = 0, Color c = Color::WHITE,
          PieceType t = PieceType::PAWN);
        
    virtual ~Piece();
    int getX() const;
    int getY() const;
    PieceType getType() const;
    Color getColor() const;
    virtual void display(Color c) const;

   protected:
    PieceType type;
    Color color;
    int y;
    int x;
    void movePiece(int y, int x);
    virtual std::vector<string> listValidMoves(Piece **grid) const = 0;
};

class Pawn : public Piece {
   public:
    Pawn(int y, int x, Color c);

   protected:
    std::vector<string> listValidMoves(Piece **grid) const override;
};

class Knight : public Piece {
   public:
    Knight(int y, int x, Color c);

   protected:
    std::vector<string> listValidMoves(Piece **grid) const override;
};

class Bishop : public Piece {
   public:
    Bishop(int y, int x, Color c);

   protected:
    std::vector<string> listValidMoves(Piece **grid) const override;
};

class Queen : public Piece {
   public:
    Queen(int y, int x, Color c);

   protected:
    std::vector<string> listValidMoves(Piece **grid) const override;
};

class Rook : public Piece {
   public:
    Rook(int y, int x, Color c);

   protected:
    std::vector<string> listValidMoves(Piece **grid) const override;
};

class King : public Piece {
   public:
    King(int y, int x, Color c);
    void setCheck(bool check);
    void display(Color c) const override;

   protected:
    std::vector<string> listValidMoves(Piece **grid) const override;

   private:
    bool underCheck = false;
};

string pieceString(PieceType t);
#endif  // PIECE_H