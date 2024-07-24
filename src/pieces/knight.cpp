#include "../../include/piece.h"
#include "piece.h"

Knight::Knight(int y, int x, Color c) : Piece(y, x, c, PieceType::KNIGHT) {}

bool Knight::movePiece(int y, int x, Piece** grid) {
    return false;
}