#include "piece.h"

string pieceString(PieceType t, Color c) {
    const string whitePieces[] = {
        "\u2659",  // PAWN
        "\u2656",  // ROOK
        "\u2658",  // KNIGHT
        "\u2657",  // BISHOP
        "\u2655",  // QUEEN
        "\u2654"   // KING
    };

    const string blackPieces[] = {
        "\u265F",  // PAWN
        "\u265C",  // ROOK
        "\u265E",  // KNIGHT
        "\u265D",  // BISHOP
        "\u265B",  // QUEEN
        "\u265A"   // KING
    };

    // Determine which array of pieces to use based on color
    const string *pieces = (c == Color::WHITE) ? whitePieces : blackPieces;

    // Return the appropriate piece string based on PieceType
    switch (t) {
        case PieceType::PAWN:
            return pieces[0];
        case PieceType::ROOK:
            return pieces[1];
        case PieceType::KNIGHT:
            return pieces[2];
        case PieceType::BISHOP:
            return pieces[3];
        case PieceType::QUEEN:
            return pieces[4];
        case PieceType::KING:
            return pieces[5];
        default:
            return "Unknown";
    }
}

Piece::Piece(int y, int x, Color c, PieceType t) {
    this->y = y;
    this->x = x;
    color = c;
    type = t;
}

Piece::~Piece() {}

int Piece::getX() const {
    return x;
}

int Piece::getY() const {
    return y;
}

void Piece::setX(int x) {
    if (x < 0 || x > 7) return;
    this->x = x;
}

void Piece::setY(int y) {
    if (y < 0 || y > 7) return;
    this->y = y;
}
PieceType Piece::getType() const {
    return type;
}

Color Piece::getColor() const {
    return color;
}

void Piece::display(Color c) const {
    std::cout << " ";
    if (getJustMoved()) {
        std::cout << GREEN << pieceString(type, c) << RESET;
    } else {
        std::cout << pieceString(type, c);
    }
    std::cout << " |";
}

bool Piece::getJustMoved() const {
    return justMoved;
}

void Piece::setJustMoved(bool x) {
    justMoved = x;
}

void Piece::makeMove(int y2, int x2, Piece **grid) {
    int source = convertCors(getY(), getX());
    int target = convertCors(y2, x2);
    grid[target] = grid[source];
    grid[source] = nullptr;
    grid[target]->setX(x2);
    grid[target]->setY(y2);
}

bool validLateralMove(int currentY, int currentX, int targetY, int targetX,
                      Piece **grid) {
    // must be the same x or the same y but not both
    if (!((currentY == targetY) ^ (currentX == targetX))) return false;
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
    start += direction;
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
    int currentIndex = convertCors(currentY, currentX);
    Color pieceColor = grid[currentIndex]->getColor();

    if (grid[targetIndex] != nullptr &&
        grid[targetIndex]->getColor() == pieceColor) {
        return false;
    }

    return true;
}

bool validDiagonalMove(int currentY, int currentX, int targetY, int targetX,
                       Piece **grid) {
    int diffY = std::fabs(currentY - targetY);
    int diffX = std::fabs(currentX - targetX);

    if (diffY != diffX || diffX == 0) return false;

    int directionX = currentX > targetX ? -1 : 1;
    int directionY = currentY > targetY ? -1 : 1;
    int startX = currentX + directionX;
    int startY = currentY + directionY;

    // check that the path from current to target is clear
    while (startY != targetY) {
        int index = convertCors(startY, startX);

        if (grid[index] != nullptr) return false;

        startY += directionY;
        startX += directionX;
    }
    // check that the targer does not have one of the player's pieces
    int targetIndex = convertCors(targetY, targetX);
    int currentIndex = convertCors(currentY, currentX);
    Color pieceColor = grid[currentIndex]->getColor();

    if (grid[targetIndex] != nullptr &&
        grid[targetIndex]->getColor() == pieceColor) {
        return false;
    }

    return true;
}
