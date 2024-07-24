#include "../../include/piece.h"

Rook::Rook(int y, int x, Color c) : Piece(y, x, c, PieceType::ROOK) {}

bool Rook::isValidMove(int targetY, int targetX, Piece** grid) {
    bool res = validLateralMove(getY(), getX(), targetY, targetX, grid);
    if (res) {
        setHasMoved(true);
    }
    return res;
}

bool Rook::getHasMoved() {
    return justMoved;
}
void Rook::setHasMoved(bool x) {
    justMoved = x;
}
