#include "../../include/piece.h"

Rook::Rook(int y, int x, Color c) : Piece(y, x, c, PieceType::ROOK) {}

bool Rook::isValidMove(int y, int x, Piece** grid) {
    return false;
}