#include "../../include/piece.h"

Queen::Queen(int y, int x, Color c) : Piece(y, x, c, PieceType::QUEEN) {}

bool Queen::isValidMove(int y, int x, Piece** grid) {
    return false;
}