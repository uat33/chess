#include "../../include/piece.h"

Bishop::Bishop(int y, int x, Color c) : Piece(y, x, c, PieceType::BISHOP) {}

std::vector<string> Bishop::listValidMoves(Piece **grid) const {
    std::vector<string> result;
    return result;
}