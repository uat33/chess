#include "piece.h"

Bishop::Bishop(int y, int x, Color c) : Piece(y, x, c, PieceType::BISHOP) {}

Piece* Bishop::clone() const {
    return new Bishop(*this);
}
bool Bishop::isValidMove(int targetY, int targetX, Piece** grid) {
    return validDiagonalMove(getY(), getX(), targetY, targetX, grid);
}

std::vector<std::vector<int>> Bishop::listValidMoves(Piece** grid) const {
    std::vector<std::vector<int>> validMoves;

    return validMoves;
}