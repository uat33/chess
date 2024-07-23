#include "../../include/piece.h"

Pawn::Pawn(int y, int x, Color c) : Piece(y, x, c, PieceType::PAWN) {}

std::vector<string> Pawn::listValidMoves(Piece **grid) const {
    std::vector<string> result;
    return result;
}