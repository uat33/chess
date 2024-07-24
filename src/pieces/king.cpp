#include "../../include/piece.h"

King::King(int y, int x, Color c) : Piece(y, x, c, PieceType::KING) {}

bool King::isValidMove(int y, int x, Piece** grid) {
    
    int currentX = getX();
    int currentY = getY();
    
    if (x == currentX && y == currentY) return false;

    if (std::fabs(x - currentX) > 1) return false;
    if (std::fabs(y - currentY) > 1) return false;
    
    int index = convertCors(y, x);
    if (grid[index] != nullptr && grid[index]->getColor() == getColor()){
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
        std::cout << YELLOW << pieceString(type) << RESET << " |";
        return;
    }
    if (underCheck) {
        std::cout << RED << pieceString(type) << RESET;
    } else if (c == Color::BLACK) {
        std::cout << BLACK_TEXT << pieceString(type) << RESET;
    } else {
        std::cout << pieceString(type);
    }
    std::cout << " |";
}
