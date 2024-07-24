#include "../../include/piece.h"

Rook::Rook(int y, int x, Color c) : Piece(y, x, c, PieceType::ROOK) {}

bool Rook::isValidMove(int targetY, int targetX, Piece** grid) {
    int currentY = getY();
    int currentX = getX();

    // must be the same x or the same y but not both
    if (!(currentY == targetY ^ currentX == targetX)) return false;

    int start, end;
    bool movingVertically;
    if (currentY == targetY) {
        start = currentX;
        end = targetX;
        movingVertically = false;
    } else {
        start = currentY;
        end = targetY;
        movingVertically = true;
    }

    const int direction = end - start > 0 ? 1 : -1;

    // all squares in between must be empty
    while (start != end) {
        int index;
        if (movingVertically) {
            index = convertCors(start, currentX);
        } else {
            index = convertCors(currentY, start);
        }
        if (grid[index] != nullptr) return false;
        start += direction;
    }

    // make sure the target square doesn't have piece of the same color
    int targetIndex = convertCors(targetY, targetX);
    if (grid[targetIndex] != nullptr &&
        grid[targetIndex]->getColor() == getColor()) {
        return false;
    }
    // store this for castling
    setHasMoved(true);
    return true;
}

bool Rook::getHasMoved() {
    return justMoved;
}
void Rook::setHasMoved(bool x) {
    justMoved = x;
}
