#include "../../include/piece.h"

Queen::Queen(int y, int x, Color c) : Piece(y, x, c, PieceType::QUEEN) {}

std::vector<string> Queen::listValidMoves(Piece **grid) const {
    std::vector<string> result;
    return result;
}