#include "piece.h"

Bishop::Bishop(int y, int x, Color c) : Piece(y, x, c, PieceType::BISHOP) {}

Piece* Bishop::clone() const {
    return new Bishop(*this);
}
bool Bishop::isValidMove(int targetY, int targetX, Piece** grid) {
    std::vector<std::vector<int>> validMoves = listValidMoves(grid);

    for (const auto& cor : validMoves) {
        if (cor[0] == targetY && cor[1] == targetX) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<int>> Bishop::listValidMoves(Piece** grid) const {
    return getDiagonalMoves(getY(), getX(), grid);
}