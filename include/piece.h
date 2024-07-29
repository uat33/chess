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
    Color getColor() const;
    PieceType getType() const;
    bool getJustMoved() const;
    void setJustMoved(bool x);
    virtual Piece *clone() const = 0;
    virtual void display(Color c) const;
    virtual void makeMove(int y2, int x2, Piece **grid);
    virtual bool isValidMove(int y, int x, Piece **grid) = 0;
    virtual std::vector<std::vector<int>> listValidMoves(
        Piece **grid) const = 0;

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
    Piece *clone() const override;
    virtual void makeMove(int y2, int x2, Piece **grid) override;
    bool isValidMove(int y, int x, Piece **grid) override;
    bool getJustMovedTwo();
    void setJustMovedTwo(bool x);
    bool getJustEnPassant();
    void setJustEnPassant(bool x);
    std::vector<std::vector<int>> listValidMoves(Piece **grid) const override;

   private:
    bool justMovedTwo = false;
    bool justEnPassant = false;
};

class Knight : public Piece {
   public:
    Knight(int y, int x, Color c);
    Piece *clone() const override;

    bool isValidMove(int y, int x, Piece **grid) override;
    std::vector<std::vector<int>> listValidMoves(Piece **grid) const override;
};

class Bishop : public Piece {
   public:
    Bishop(int y, int x, Color c);
    Piece *clone() const override;
    bool isValidMove(int y, int x, Piece **grid) override;
    std::vector<std::vector<int>> listValidMoves(Piece **grid) const override;
};

class Queen : public Piece {
   public:
    Queen(int y, int x, Color c);
    Piece *clone() const override;
    std::vector<std::vector<int>> listValidMoves(Piece **grid) const override;
    bool isValidMove(int y, int x, Piece **grid) override;
};

class Rook : public Piece {
   public:
    Rook(int y, int x, Color c);
    Piece *clone() const override;
    virtual void makeMove(int y2, int x2, Piece **grid) override;
    std::vector<std::vector<int>> listValidMoves(Piece **grid) const override;
    bool isValidMove(int y, int x, Piece **grid) override;
    bool getHasMoved();
    void setHasMoved(bool x);

   private:
    bool hasMoved = false;
};

class King : public Piece {
   public:
    King(int y, int x, Color c);
    Piece *clone() const override;
    virtual void makeMove(int y2, int x2, Piece **grid) override;
    void setCheck(bool check);
    void display(Color c) const override;
    bool isValidMove(int y, int x, Piece **grid) override;
    std::vector<std::vector<int>> listValidMoves(Piece **grid) const override;

   private:
    bool underCheck = false;
    bool hasMoved = false;
};

string pieceString(PieceType t, Color c);
std::vector<std::vector<int>> getDiagonalMoves(int currentY, int currentX,
                                               Piece **grid);
std::vector<std::vector<int>> getLateralMoves(int currentY, int currentX,
                                              Piece **grid);
#endif  // PIECE_H
