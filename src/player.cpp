#include "../include/player.h"

#include "player.h"

Player::Player(Color c) {
    int row1 = c == Color::BLACK ? 0 : 7;
    int row2 = c == Color::BLACK ? 1 : 6;
    for (int i = 8; i < 16; i++) {
        pieces[i] = new Pawn(row2, i - 8, c);
    }

    pieces[0] = new Rook(row1, 0, c);
    pieces[1] = new Knight(row1, 1, c);
    pieces[2] = new Bishop(row1, 2, c);
    pieces[3] = new Queen(row1, 3, c);
    pieces[4] = new King(row1, 4, c);
    pieces[5] = new Bishop(row1, 5, c);
    pieces[6] = new Knight(row1, 6, c);
    pieces[7] = new Rook(row1, 7, c);
    pieceColor = c;
}

Player::~Player() {
    for (int i = 0; i < 16; ++i) {
        delete pieces[i];
    }
}

Piece **Player::getPieces() {
    return pieces;
}

void Player::removePiece(int y, int x) {}

void Player::setUnderCheck(bool x) {
    underCheck = x;
    King *k = dynamic_cast<King *>(getPieces()[4]);
    k->setCheck(x);
}

bool Player::getUnderCheck() {
    return underCheck;
}

bool Player::isUnderCheck(Piece **grid, Player *opponent) {
    Piece **opponentPieces = opponent->getPieces();
    int kingY = pieces[4]->getY();
    int kingX = pieces[4]->getX();
    for (int i = 0; i < 16; i++) {
        if (opponentPieces[i] != nullptr &&
            opponentPieces[i]->isValidMove(kingY, kingX, grid)) {
            return true;
        }
    }

    return false;
}

bool Player::makeMove(int y1, int x1, int y2, int x2, Piece **grid,
                      Player *opponent) {
    int index = convertCors(y1, x1);
    int targetIndex = convertCors(y2, x2);

    // check that the chosen tile has a piece belonging to the user
    if (grid[index] == nullptr || grid[index]->getColor() != getColor()) {
        return false;
    }
    if (!grid[index]->isValidMove(y2, x2, grid)) return false;
    Piece *targetPiece = grid[targetIndex];
    Piece *oldPiece = grid[index];
    grid[targetIndex] = grid[index];
    grid[index] = nullptr;

    // TODO: the resulting board must not have the opponent under check
    if (isUnderCheck(grid, opponent)) {
        grid[targetIndex] = targetPiece;
        grid[index] = oldPiece;
        setUnderCheck(true);
        return false;
    }
    setUnderCheck(false);

    grid[targetIndex]->setX(x2);
    grid[targetIndex]->setY(y2);
    if (targetPiece != nullptr) {
        // capture
        delete targetPiece;
    }
    grid[targetIndex]->setJustMoved(true);

    if (opponent->isUnderCheck(grid, this)) {
        opponent->setUnderCheck(true);
    }

    return true;
}

Color Player::getColor() {
    return pieceColor;
}
