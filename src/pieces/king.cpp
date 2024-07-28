#include "../../include/piece.h"

King::King(int y, int x, Color c) : Piece(y, x, c, PieceType::KING) {}

Piece* King::clone() const {
    return new King(*this);
}
bool King::isValidMove(int y, int x, Piece** grid) {
    int currentX = getX();
    int currentY = getY();
    int index = convertCors(y, x);

    // check if this is a castle

    if (grid[index] != nullptr && grid[index]->getColor() == getColor()) {
        if (underCheck || hasMoved) return false;

        if (grid[index]->getType() == PieceType::ROOK) {
            Rook* rook = dynamic_cast<Rook*>(grid[index]);
            if (rook->getHasMoved()) return false;
        } else {
            return false;
        }

        int inBetweenSquares = std::fabs(currentX - x) - 1;
        int inBetweenCors[inBetweenSquares][2];
        int inBetweenCorsIndex = 0;
        // check that there are no pieces in between
        int direction = x < currentX ? -1 : 1;

        for (int i = currentX + direction; i != x; i += direction) {
            int square = convertCors(y, i);
            inBetweenCors[inBetweenCorsIndex][0] = y;
            inBetweenCors[inBetweenCorsIndex++][1] = i;
            if (grid[square] != nullptr) return false;
        }

        // check that there wouldn't be a check to the in between squares
        for (int i = 0; i < inBetweenSquares; i++) {
            int inBetweenY = inBetweenCors[i][0];
            int inBetweenX = inBetweenCors[i][1];
            for (int j = 0; j < DIMENSION * DIMENSION; j++) {
                if (grid[j] != nullptr && grid[j]->getColor() != getColor() &&
                    grid[j]->getType() != getType() &&
                    grid[j]->isValidMove(inBetweenY, inBetweenX, grid)) {
                    return false;
                }
            }
        }
        return true;
    }

    if (x == currentX && y == currentY) return false;

    if (std::fabs(x - currentX) > 1) return false;
    if (std::fabs(y - currentY) > 1) return false;
    if (grid[index] != nullptr && grid[index]->getColor() == getColor()) {
        return false;
    }

    return true;
}

void King::setCheck(bool check) {
    underCheck = check;
}

void King::display(Color c) const {
    std::cout << " ";
    if (getJustMoved()) {
        std::cout << GREEN << pieceString(type, c) << RESET;
    } else if (underCheck) {
        std::cout << RED << pieceString(type, c) << RESET;
    } else {
        std::cout << pieceString(type, c);
    }
    std::cout << " |";
}

void King::makeMove(int y2, int x2, Piece** grid) {
    int target = convertCors(y2, x2);
    if (grid[target] == nullptr || grid[target]->getColor() != getColor()) {
        Piece::makeMove(y2, x2, grid);
        hasMoved = true;
        return;
    }
    int kingSquare = convertCors(getY(), getX());

    int newKingSquare, newRookSquare;
    // this is a short castle
    if (x2 > getX()) {
        newKingSquare = x2 - 1;
        newRookSquare = x2 - 2;
    } else {  // long castle
        newKingSquare = x2 + 2;
        newRookSquare = x2 + 3;
    }
    grid[kingSquare]->setX(newKingSquare);
    grid[target]->setX(newRookSquare);
    Rook* rook = dynamic_cast<Rook*>(grid[target]);
    rook->setHasMoved(true);
    grid[convertCors(y2, newKingSquare)] = grid[kingSquare];
    grid[convertCors(y2, newRookSquare)] = grid[target];
    grid[convertCors(y2, newKingSquare)]->setJustMoved(true);
    grid[convertCors(y2, newRookSquare)]->setJustMoved(true);

    grid[target] = nullptr;
    grid[kingSquare] = nullptr;
    hasMoved = true;
}
