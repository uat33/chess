#include "../../include/piece.h"

King::King(int y, int x, Color c) : Piece(y, x, c, PieceType::KING) {}

bool King::movePiece(int y, int x, Piece** grid) {
    return false;
}

void King::setCheck(bool check) {
    underCheck = check;
}

void King::display(Color c) const {
    std::cout << " ";

    if (underCheck) {
        std::cout << RED << pieceString(type) << RESET;
    } else if (c == Color::BLACK) {
        std::cout << BLACK_TEXT << pieceString(type) << RESET;
    } else {
        std::cout << pieceString(type);
    }
    std::cout << " |";
}
