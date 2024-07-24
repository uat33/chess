#include "../../include/piece.h"

Rook::Rook(int y, int x, Color c) : Piece(y, x, c, PieceType::ROOK) {}

bool Rook::movePiece(int y, int x, Piece** grid) {
    return false;
}