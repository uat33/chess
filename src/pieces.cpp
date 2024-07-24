#include "../include/piece.h"
#include "piece.h"

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
        std::cout << YELLOW << pieceString(type) << RESET << " |";
        return;
    }
    if (c == Color::BLACK) {
        std::cout << BLACK_TEXT << pieceString(type) << RESET;
    } else {
        std::cout << pieceString(type);
    }
    std::cout << " |";
}

bool Piece::getJustMoved() const {
    return justMoved;
}

void Piece::setJustMoved(bool x) {
    justMoved = x;
}
