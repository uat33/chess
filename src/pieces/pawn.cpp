#include "piece.h"

Pawn::Pawn(int y, int x, Color c) : Piece(y, x, c, PieceType::PAWN) {}

Piece *Pawn::clone() const {
    return new Pawn(*this);
}
bool Pawn::isValidMove(int targetY, int targetX, Piece **grid) {
    std::vector<std::vector<int>> moves = listValidMoves(grid);
    for (const auto &cor : moves) {
        if (cor[0] == targetY && cor[1] == targetX) {
            return true;
        }
    }
    return false;
}

void Pawn::makeMove(int y2, int x2, Piece **grid) {
    if (std::fabs(y2 - getY()) == 1) {
        setJustMovedTwo(false);
    }
    if (std::fabs(y2 - getY()) == 2) {
        setJustMovedTwo(true);
    }
    if (grid[convertCors(y2, x2)] == nullptr && y2 != getY()) {
        setJustEnPassant(true);
    }

    Piece::makeMove(y2, x2, grid);

    if (getJustEnPassant()) {
        const int direction = getColor() == Color::WHITE ? 1 : -1;
        grid[convertCors(y2 + direction, x2)] = nullptr;
        setJustEnPassant(false);
    }
}

std::vector<std::vector<int>> Pawn::listValidMoves(Piece **grid) const {
    std::vector<std::vector<int>> validMoves;
    int currentY = getY();
    int currentX = getX();
    Color color = getColor();

    int direction = 1;
    int startingRow = 1;
    if (color == Color::WHITE) {
        direction = -1;
        startingRow = 6;
    }
    int inFront = convertCors(currentY + direction, currentX);
    if (grid[inFront] == nullptr) {
        validMoves.push_back({currentY + direction, currentX});
        // check if two moves in front works -- only if 1 in front is empty
        if (currentY == startingRow &&
            grid[convertCors(currentY + direction * 2, currentX)] == nullptr) {
            validMoves.push_back({currentY + direction * 2, currentX});
        }
    }

    std::vector<std::vector<int>> diagonals;
    std::vector<std::vector<int>> enPassantSquares;

    if (currentX > 0) {
        diagonals.push_back({currentY + direction, currentX - 1});
        if (currentY == startingRow + direction * 3) {
            enPassantSquares.push_back({currentY, currentX - 1});
        }
    }
    if (currentX < DIMENSION - 1) {
        diagonals.push_back({currentY + direction, currentX + 1});
        if (currentY == startingRow + direction * 3) {
            enPassantSquares.push_back({currentY, currentX + 1});
        }
    }

    for (const auto &cor : diagonals) {
        int diagonal = convertCors(cor[0], cor[1]);
        if (grid[diagonal] != nullptr && grid[diagonal]->getColor() != color) {
            validMoves.push_back({cor[0], cor[1]});
        }
    }

    for (const auto &cor : enPassantSquares) {
        int square = convertCors(cor[0], cor[1]);
        if (grid[square] != nullptr && grid[square]->getColor() != color &&
            grid[square]->getType() == PieceType::PAWN) {
            Pawn *pawn = dynamic_cast<Pawn *>(grid[square]);
            if (pawn->getJustMovedTwo()) {
                validMoves.push_back({cor[0] + direction, cor[1]});
            }
        }
    }

    return validMoves;
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
