#include "../../include/piece.h"

Pawn::Pawn(int y, int x, Color c) : Piece(y, x, c, PieceType::PAWN) {}

// 0
// 1
// 2
// 3
// 4
// 5
// 6
// 7
bool Pawn::movePiece(int y, int x, Piece **grid) {
    int currentY = getY();
    int currentX = getX();
    Color color = getColor();

    int modifier = 1;
    if (color == Color::WHITE) {
        modifier = -1;
    }

    return false;
}

// if (y > currentY || y < currentY - 2) return false;
// if (x < currentX - 1 || x > currentX + 1) return false;
// if (currentX == x) {
//     if (currentY - 2 == y) {
//         if (currentY != 6) return false;
//     }

//     // piece in between
//     for (int i = currentY - 1; i <= y; i--) {
//         if (grid[convertCors(i, x)] != nullptr) return false;
//     }

//     setX(x);
//     setY(y);
//     return true;
// } else {  // different file
//     if (currentY - 1 != y) return false;

//     int index = convertCors(y, x);

//     if (grid[index] != nullptr &&
//         grid[index]->getColor() != getColor()) {
//         // TODO: capture that piece
//         setX(x);
//         setY(y);
//         return true;
//     }
//     // TODO: en passant
//     return false;
// }