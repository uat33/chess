#include "util.h"
int convertCors(int y, int x) {
    return y * 8 + x;
}

bool isUnderCheck(int kingY, int kingX, Player *opponent, Piece **grid) {
    Piece **opponentPieces = opponent->getPieces();
    for (int i = 0; i < 16; i++) {
        if (opponentPieces[i] != nullptr &&
            opponentPieces[i]->isValidMove(kingY, kingX, grid)) {
            return true;
        }
    }

    return false;
}