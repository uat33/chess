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
}

Player::~Player() {
    for (int i = 0; i < 16; ++i) {
        delete pieces[i];
    }
}

Piece** Player::getPieces() {
    return pieces;
}

bool Player::processMove() const {
    return false;
}

void Player::removePiece(int y, int x) {}
