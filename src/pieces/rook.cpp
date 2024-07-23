#include "../../include/piece.h"

Rook::Rook(int y, int x, Color c) : Piece(y, x, c, PieceType::ROOK) {}

std::vector<string> Rook::listValidMoves(Piece **grid) const {
    std::vector<string> result;
    return result;
}