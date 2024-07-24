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


bool validLateralMove(int currentY, int currentX, int targetY, int targetX, Piece **grid){

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

bool validDiagonalMove(int currentY, int currentX, int targetY, int targetX, Piece **grid){
 

  int diffY = std::fabs(currentY - targetY);
  int diffX = std::fabs(currentX - targetX);

  if (diffY != diffX) return false;

  int directionX = currentX > targetX ? -1 : 1;
  
  int directionY = currentY > targetY ? -1 : 1;
  
  int startX = currentX;
  int startY = currentY;
  
  // check that the path from current to target is clear
  while (startY != targetY){
    
    int index = convertCors(startY, startX);

    if (grid[index] != nullptr) return false;

    startY += directionY;
    startX += directionX;
  }
  // check that the targer does not have one of the player's pieces
  int targetIndex = convertCors(targetY, targetX);

  int currentIndex = convertCors(currentY, currentX);
  Color pieceColor = grid[currentIndex]->getColor();
  if (grid[targetIndex] != nullptr && grid[targetIndex]->getColor() == pieceColor){
    return false;
  }


  return true;

}
