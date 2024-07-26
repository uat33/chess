#include "../../include/piece.h"
#include "piece.h"

Knight::Knight(int y, int x, Color c) : Piece(y, x, c, PieceType::KNIGHT) {}
Piece* Knight::clone() const {
    return new Knight(*this);
}

bool Knight::isValidMove(int targetY, int targetX, Piece** grid) {
    int currentX = getX();
    int currentY = getY();

    int index = convertCors(targetY, targetX);
    if (grid[index] != nullptr && grid[index]->getColor() == getColor())
        return false;
    if (std::fabs(targetX - currentX) == 2 &&
        std::fabs(targetY - currentY) == 1)
        return true;

    if (std::fabs(targetY - currentY) == 2 &&
        std::fabs(targetX - currentX) == 1)
        return true;

    return false;
}
