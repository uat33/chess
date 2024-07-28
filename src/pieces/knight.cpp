#include "piece.h"

Knight::Knight(int y, int x, Color c) : Piece(y, x, c, PieceType::KNIGHT) {}
Piece* Knight::clone() const {
    return new Knight(*this);
}

bool Knight::isValidMove(int targetY, int targetX, Piece** grid) {

    std::vector<std::vector<int>> valid = listValidMoves(grid);
    for (const auto& inner_vec : valid) {
        if (inner_vec[0] == targetY && inner_vec[1] == targetX) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<int>> Knight::listValidMoves(Piece** grid) const {
    std::vector<std::vector<int>> validMoves;

    int currentX = getX();
    int currentY = getY();

    std::vector<std::vector<int>> all;

    all.push_back({currentX + 2, currentY - 1});
    all.push_back({currentX + 2, currentY + 1});
    all.push_back({currentX - 2, currentY - 1});
    all.push_back({currentX - 2, currentY + 1});

    all.push_back({currentX - 1, currentY + 2});
    all.push_back({currentX + 1, currentY + 2});
    all.push_back({currentX - 1, currentY - 2});
    all.push_back({currentX + 1, currentY - 2});

    for (const auto& cor : all) {
        if (cor[0] < 0 || cor[0] > DIMENSION - 1 || cor[1] < 0 ||
            cor[0] > DIMENSION - 1) {
            continue;
        }
        int square = convertCors(cor[0], cor[1]);
        if (grid[square] != nullptr && grid[square]->getColor() == color) {
            continue;
        }
        validMoves.push_back({cor[0], cor[1]});
    }

    return validMoves;
}