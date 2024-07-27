#include "../include/player.h"

#include "player.h"

Player::Player(Color c) {
    for (int i = 0; i < NUMPIECES; i++) {
        pieces[i] = nullptr;
    }
    pieceColor = c;
}

Player::Player(Color c, bool init) {
    int row1 = c == Color::BLACK ? 0 : 7;
    int row2 = c == Color::BLACK ? 1 : 6;
    for (int i = 8; i < NUMPIECES; i++) {
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
    for (int i = 0; i < NUMPIECES; i++) {
        delete pieces[i];
        pieces[i] = nullptr;
    }
}

Piece **Player::getPieces() {
    return pieces;
}

void Player::setUnderCheck(bool x) {
    underCheck = x;
    King *k = dynamic_cast<King *>(getPieces()[4]);
    k->setCheck(x);
}

bool Player::getUnderCheck() const {
    return underCheck;
}

bool Player::isUnderCheck(Piece **grid, Player *opponent) const {
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

bool Player::makeMove(int y1, int x1, int y2, int x2, Piece **grid) {
    int index = convertCors(y1, x1);

    bool validMove = grid[index]->isValidMove(y2, x2, grid);

    if (validMove) {
        grid[index]->makeMove(y2, x2, grid);
    }
    return validMove;
    // int targetIndex = convertCors(y2, x2);
    // grid[targetIndex]->setX(x2);
    // grid[targetIndex]->setY(y2);
    // Piece **pieces = getPieces();
    // for (int i = 0; i < 16; i++) {
    //     if (pieces[i]->getY() == y1 && pieces[i]->getX() == x1) {
    //         pieces[i]->setX(x2);
    //         pieces[i]->setY(y2);
    //     }
    // }
}

Player *Player::clone() {
    Player *newPlayer = new Player(pieceColor);

    for (int i = 0; i < NUMPIECES; i++) {
        if (pieces[i] != nullptr) {
            newPlayer->pieces[i] = pieces[i]->clone();
        } else {
            newPlayer->pieces[i] = nullptr;
        }
    }

    newPlayer->material = material;
    newPlayer->underCheck = underCheck;

    return newPlayer;
}

Color Player::getColor() const {
    return pieceColor;
}

int Player::getMaterial() const {
    return material;
}

void Player::setMaterial(int x) {
    material = x;
}

void Player::removePiece(int y, int x) {
    for (int i = 0; i < NUMPIECES; i++) {
        if (pieces[i] != nullptr && pieces[i]->getY() == y &&
            pieces[i]->getX() == x) {
            pieces[i] = nullptr;
        }
    }
}