#include "../../include/piece.h"

Bishop::Bishop(int y, int x, Color c) : Piece(y, x, c, PieceType::BISHOP) {}

bool Bishop::isValidMove(int y, int x, Piece** grid) {
    return false;
}