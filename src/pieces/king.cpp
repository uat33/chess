#include "piece.h"

King::King(int y, int x, Color c) : Piece(y, x, c, PieceType::KING) {}

Piece* King::clone() const {
    return new King(*this);
}
bool King::isValidMove(int targetY, int targetX, Piece** grid) {
    std::vector<std::vector<int>> validMoves = listValidMoves(grid);

    for (const auto& cor : validMoves) {
        if (cor[0] == targetY && cor[1] == targetX) {
            return true;
        }
    }
    return false;
}

void King::setCheck(bool check) {
    underCheck = check;
}

void King::display(Color c) const {
    std::cout << " ";
    if (getJustMoved()) {
        std::cout << GREEN << pieceString(type, c) << RESET;
    } else if (underCheck) {
        std::cout << RED << pieceString(type, c) << RESET;
    } else {
        std::cout << pieceString(type, c);
    }
    std::cout << " |";
}

void King::makeMove(int y2, int x2, Piece** grid) {
    int target = convertCors(y2, x2);
    if (grid[target] == nullptr || grid[target]->getColor() != getColor()) {
        Piece::makeMove(y2, x2, grid);
        hasMoved = true;
        return;
    }
    int kingSquare = convertCors(getY(), getX());

    int newKingSquare, newRookSquare;
    // this is a short castle
    if (x2 > getX()) {
        newKingSquare = x2 - 1;
        newRookSquare = x2 - 2;
    } else {  // long castle
        newKingSquare = x2 + 2;
        newRookSquare = x2 + 3;
    }
    grid[kingSquare]->setJustMoved(true);
    grid[target]->setJustMoved(true);
    grid[kingSquare]->makeMove(getY(), newKingSquare, grid);
    grid[target]->makeMove(getY(), newRookSquare, grid);
}

static void addCastles(int y, int x, Piece** grid, Color color,
                       std::vector<std::vector<int>>& validMoves) {
    int r1 = convertCors(y, 0);
    int r2 = convertCors(y, DIMENSION - 1);

    for (auto c : {r1, r2}) {
        if (grid[c] != nullptr && grid[c]->getColor() == color &&
            grid[c]->getType() == PieceType::ROOK) {
            Rook* rook = dynamic_cast<Rook*>(grid[c]);
            // if rook has moved you can't castle
            if (!rook->getHasMoved()) {
                // check that there are no pieces in between
                int inBetweenSquares = std::fabs(x - grid[c]->getX()) - 1;
                int inBetweenCors[inBetweenSquares][2];
                int inBetweenCorsIndex = 0;
                int direction = x < grid[c]->getX() ? 1 : -1;
                bool inBetween = false;
                for (int i = x + direction; i != grid[c]->getX();
                     i += direction) {
                    int square = convertCors(y, i);
                    inBetweenCors[inBetweenCorsIndex][0] = y;
                    inBetweenCors[inBetweenCorsIndex++][1] = i;
                    if (grid[square] != nullptr) {
                        inBetween = true;
                        break;
                    }
                }
                if (inBetween) continue;
                bool inBetweenCheck = false;
                // check that none of the opposing pieces can move to those in
                // between squares
                for (int i = 0; i < inBetweenSquares; i++) {
                    int inBetweenY = inBetweenCors[i][0];
                    int inBetweenX = inBetweenCors[i][1];
                    for (int j = 0; j < DIMENSION * DIMENSION; j++) {
                        if (grid[j] != nullptr &&
                            grid[j]->getColor() != color) {
                            if (grid[j]->getType() != PieceType::KING &&
                                grid[j]->isValidMove(inBetweenY, inBetweenX,
                                                     grid)) {
                                inBetweenCheck = true;
                                break;
                            } else {
                                int kingY = grid[j]->getY();
                                int kingX = grid[j]->getX();

                                if (std::fabs(inBetweenY - kingY) <= 1 &&
                                    std::fabs(inBetweenX - kingX) <= 1) {
                                    inBetweenCheck = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (!inBetweenCheck) {
                    validMoves.push_back({grid[c]->getY(), grid[c]->getX()});
                }
            }
        }
    }
}

/**
 * Find all the valid moves for a king.
 * Create 3x3 grid surrounding the king
 * Omit the square the king is on, but if all the other squares do not have one
 * of this player's pieces, add that move
 *
 * If the king hasn't moved and is not under check if a castle if valid.
 *
 */
std::vector<std::vector<int>> King::listValidMoves(Piece** grid) const {
    std::vector<std::vector<int>> validMoves;
    int currentX = getX();
    int currentY = getY();
    int startY = currentY - 1;
    int startX = currentX - 1;

    for (int i = startY; i < startY + 3; i++) {
        for (int j = startX; j < startX + 3; j++) {
            if (i == currentY && j == currentX) continue;
            if (i >= 0 && i < DIMENSION && j >= 0 && j < DIMENSION) {
                if (grid[convertCors(i, j)] == nullptr ||
                    grid[convertCors(i, j)]->getColor() != getColor())
                    validMoves.push_back({i, j});
            }
        }
    }

    // check if a castle is valid
    if (!(underCheck || hasMoved)) {
        addCastles(currentY, currentX, grid, getColor(), validMoves);
    }

    return validMoves;
}