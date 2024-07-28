#include "piece.h"

Queen::Queen(int y, int x, Color c) : Piece(y, x, c, PieceType::QUEEN) {}
Piece* Queen::clone() const {
    return new Queen(*this);
}
bool Queen::isValidMove(int y, int x, Piece** grid) {
    int currentX = getX();
    int currentY = getY();

    bool diagonal = validDiagonalMove(currentY, currentX, y, x, grid);

    bool lateral = validLateralMove(currentY, currentX, y, x, grid);

    return diagonal || lateral;
}

std::vector<std::vector<int>> Queen::listValidMoves(Piece** grid) const {
    std::vector<std::vector<int>> validMoves;

    return validMoves;
}