#include "../../include/piece.h"

Pawn::Pawn(int y, int x, Color c) : Piece(y, x, c, PieceType::PAWN) {}

Piece *Pawn::clone() const {
    return new Pawn(*this);
}
bool Pawn::isValidMove(int targetY, int targetX, Piece **grid) {
    int currentY = getY();
    int currentX = getX();
    Color color = getColor();

    int direction = 1;
    int startingRow = 1;
    if (std::fabs(currentY - targetY) > 2) {
        return false;
    }
    if (color == Color::WHITE) {
        direction = -1;
        startingRow = 6;
        // pawn can not go backwards
        if (targetY >= currentY) return false;

    } else {
        if (targetY <= currentY) return false;
    }
    // can only be at most one column away
    if (std::fabs(currentX - targetX) > 1) {
        return false;
    }
    // two squares is only allowed if this is the starting square and it is
    // moving forward
    if (std::fabs(currentY - targetY) == 2) {
        if (currentY != startingRow || targetX != currentX) return false;
    }

    // if it is the same column
    if (targetX == currentX) {
        int start = currentY + direction;
        do {
            int index = convertCors(start, currentX);
            if (grid[index] != nullptr) return false;

            start += direction;
        } while (start != targetY + direction);

        if (std::fabs(currentY - targetY) == 2) {
            setJustMovedTwo(true);
        }
        return true;
    }

    // different column -- already checked above that it is only moving one
    // square in the y direction
    int targetIndex = convertCors(targetY, targetX);
    // check that there is a piece and it is a different color
    if (grid[targetIndex] != nullptr &&
        grid[targetIndex]->getColor() != color) {
        return true;
    }

    if (currentY == startingRow + direction * 3) {
        int pawnSquare = convertCors(currentY, targetX);
        if (grid[pawnSquare] != nullptr &&
            grid[pawnSquare]->getType() == PieceType::PAWN) {
            Pawn *pawn = dynamic_cast<Pawn *>(grid[pawnSquare]);
            if (pawn == nullptr) {
                std::cerr << "cast failed" << std::endl;
            } else {
                if (pawn->getJustMovedTwo()) {
                    // valid en passant
                    setJustEnPassant(true);
                    return true;
                }
            }
        }
    }

    return false;
}

void Pawn::makeMove(int y2, int x2, Piece **grid) {
    if (std::fabs(y2 - getY()) == 1) {
        setJustMovedTwo(false);
    }

    Piece::makeMove(y2, x2, grid);

    if (getJustEnPassant()) {
        const int direction = getColor() == Color::WHITE ? 1 : -1;
        grid[convertCors(y2 + direction, x2)] = nullptr;
        setJustEnPassant(false);
    }

    // TODO: pawn promotion
}

void Pawn::setJustMovedTwo(bool x) {
    justMovedTwo = x;
}

bool Pawn::getJustMovedTwo() {
    return justMovedTwo;
}

void Pawn::setJustEnPassant(bool x) {
    justEnPassant = x;
}

bool Pawn::getJustEnPassant() {
    return justEnPassant;
}
