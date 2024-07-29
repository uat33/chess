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

static std::vector<std::vector<int>> getMovesInDirection(int directions[4][2],
                                                         Piece **grid,
                                                         int currentY,
                                                         int currentX) {
    std::vector<std::vector<int>> validMoves;
    Color c = grid[convertCors(currentY, currentX)]->getColor();
    int startX;
    int startY;
    for (int i = 0; i < 4; i++) {
        int yChange = directions[i][0];
        int xChange = directions[i][1];
        startX = currentX + xChange;
        startY = currentY + yChange;
        while (startX < DIMENSION && startY < DIMENSION && startX >= 0 &&
               startY >= 0) {
            int index = convertCors(startY, startX);
            if (grid[index] == nullptr) {
                validMoves.push_back({startY, startX});
            } else if (grid[index]->getColor() != c) {
                validMoves.push_back({startY, startX});
                break;
            } else {
                break;
            }
            startX += xChange;
            startY += yChange;
        }
    }

    return validMoves;
}

std::vector<std::vector<int>> getDiagonalMoves(int currentY, int currentX,
                                               Piece **grid) {
    int arr[4][2] = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};

    return getMovesInDirection(arr, grid, currentY, currentX);
}

std::vector<std::vector<int>> getLateralMoves(int currentY, int currentX,
                                              Piece **grid) {
    int arr[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    return getMovesInDirection(arr, grid, currentY, currentX);
}
