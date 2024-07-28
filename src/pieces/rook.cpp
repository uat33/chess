#include "piece.h"

Rook::Rook(int y, int x, Color c) : Piece(y, x, c, PieceType::ROOK) {}

Piece* Rook::clone() const {
    return new Rook(*this);
}

bool Rook::isValidMove(int targetY, int targetX, Piece** grid) {
    std::vector<std::vector<int>> validMoves = listValidMoves(grid);

    for (const auto& cor : validMoves) {
        if (cor[0] == y && cor[1] == x) {
            setHasMoved(true);
            return true;
        }
    }
    return false;
}

void Rook::makeMove(int y2, int x2, Piece** grid) {
    Piece::makeMove(y2, x2, grid);

    hasMoved = true;
}

bool Rook::getHasMoved() {
    return justMoved;
}
void Rook::setHasMoved(bool x) {
    justMoved = x;
}

std::vector<std::vector<int>> Rook::listValidMoves(Piece** grid) const {
    return getLateralMoves(getY(), getX(), grid);
}