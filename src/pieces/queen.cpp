#include "../../include/piece.h"

Queen::Queen(int y, int x, Color c) : Piece(y, x, c, PieceType::QUEEN) {}

bool Queen::isValidMove(int y, int x, Piece** grid) {
  
  int currentX = getX();
  int currentY = getY();

  bool diagonal = validDiagonalMove(currentY, currentX, y, x, grid);
  
  bool lateral = validLateralMove(currentY, currentX, y, x, grid);
  
  return diagonal || lateral;
}
