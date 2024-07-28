#include "piece.h"

Queen::Queen(int y, int x, Color c) : Piece(y, x, c, PieceType::QUEEN) {}
Piece* Queen::clone() const {
    return new Queen(*this);
}
bool Queen::isValidMove(int y, int x, Piece** grid) {
    std::vector<std::vector<int>> validMoves = listValidMoves(grid);

    for (const auto& cor : validMoves) {
        if (cor[0] == y && cor[1] == x) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<int>> Queen::listValidMoves(Piece** grid) const {
    std::vector<std::vector<int>> validMoves = getDiagonalMoves(y, x, grid);
    std::vector<std::vector<int>> lateral = getLateralMoves(y, x, grid);
    for (const auto& inner_vec : lateral) {
        validMoves.push_back(inner_vec);
    }
    return validMoves;
}