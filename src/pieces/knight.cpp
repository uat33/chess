#include "../../include/piece.h"

Knight::Knight(int y, int x, Color c) : Piece(y, x, c, PieceType::KNIGHT) {}

std::vector<string> Knight::listValidMoves(Piece **grid) const {
    std::vector<string> result;
    return result;
}