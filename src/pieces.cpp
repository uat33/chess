#include "../include/piece.h"

string pieceString(PieceType t) {
    switch (t) {
        case PieceType::PAWN:
            return "\u2659";
        case PieceType::ROOK:
            return "\u2656";
        case PieceType::KNIGHT:
            return "\u2658";
        case PieceType::BISHOP:
            return "\u2657";
        case PieceType::QUEEN:
            return "\u2655";
        case PieceType::KING:
            return "\u2654";
        default:
            return "Unknown";  // Handle unexpected values gracefully
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

PieceType Piece::getType() const {
    return type;
}

Color Piece::getColor() const {
    return color;
}

void Piece::display(Color c) const {
    std::cout << " ";
    if (c == Color::BLACK) {
        std::cout << BLACK_TEXT << pieceString(type) << RESET;
    } else {
        std::cout << pieceString(type);
    }
    std::cout << " |";
}

void Piece::movePiece(int y, int x) {
    if (y < 0 || y > DIMENSION - 1) return;
    if (x < 0 || x > DIMENSION - 1) return;
    this->y = y;
    this->x = x;
}
