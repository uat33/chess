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

static void pawnPromotionText() {
    std::cout << "Pawn promoted." << std::endl;
    std::cout << "Choose which piece to promote to." << std::endl;
    std::cout << "Q for Queen" << std::endl;
    std::cout << "R for Rook" << std::endl;
    std::cout << "B for Bishop" << std::endl;
    std::cout << "N for Knight" << std::endl;
}

static char validatePromotion(const string &promotion) {
    if (promotion.length() > 1) return '.';
    char piece = std::tolower(promotion[0]);
    if (piece != 'q' && piece != 'b' && piece != 'r' && piece != 'n') {
        return '.';
    }

    return piece;
}

void Player::updatePiece(Piece *p, int y, int x) {
    Piece **pieces = getPieces();
    for (int i = 0; i < 16; i++) {
        if (pieces[i] != nullptr) {
            if (pieces[i]->getX() == x && pieces[i]->getY() == y) {
                delete pieces[i];
                pieces[i] = p;
            }
        }
    }
}

void Player::promote(Piece **grid, int y, int x, char piece) {
    Piece *p;
    Color c = getColor();
    int materialGain = 0;
    switch (piece) {
        case 'q':
            p = new Queen(y, x, c);
            materialGain = 9;
            break;
        case 'r':
            p = new Rook(y, x, c);
            materialGain = 5;
            break;
        case 'n':
            p = new Knight(y, x, c);
            materialGain = 3;
            break;
        case 'b':
            p = new Bishop(y, x, c);
            materialGain = 3;
            break;
        default:
            break;
    }
    // - as this is how much material this player has lost
    material -= materialGain;
    grid[convertCors(y, x)] = p;
    updatePiece(p, y, x);
}

static void removeJustMovedTwoFlag(Piece **pieces, Piece **grid, int y2,
                                   int x2) {
    for (int i = 0; i < NUMPIECES; i++) {
        if (grid[convertCors(y2, x2)] != pieces[i] && pieces[i] != nullptr) {
            if (pieces[i]->getType() == PieceType::PAWN) {
                Pawn *pawn = dynamic_cast<Pawn *>(pieces[i]);
                pawn->setJustMovedTwo(false);
            }
        }
    }
}

bool Player::makeMove(int y1, int x1, int y2, int x2, Piece **grid) {
    int index = convertCors(y1, x1);
    bool validMove = grid[index]->isValidMove(y2, x2, grid);

    if (validMove) {
        grid[index]->makeMove(y2, x2, grid);

        // remove the just moved two flag, for all the pawns that aren't this
        // piece
        // because none of those moving by two can be the most recent move
        // anymore
        removeJustMovedTwoFlag(getPieces(), grid, y2, x2);

        int targetIndex = convertCors(y2, x2);
        // check if it is a pawn promotion
        if (grid[targetIndex] != nullptr &&
            grid[targetIndex]->getType() == PieceType::PAWN &&
            (y2 == 0 || y2 == 7)) {
            pawnPromotionText();
            string promotion;
            char piece = '.';
            while (piece == '.') {
                std::getline(std::cin, promotion);
                piece = validatePromotion(promotion);
            }
            promote(grid, y2, x2, piece);
        }
    }
    return validMove;
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

static int getMaterialPiece(PieceType t) {
    switch (t) {
        case PieceType::PAWN:
            return 1;
        case PieceType::KNIGHT:
            return 3;
        case PieceType::BISHOP:
            return 3;
        case PieceType::ROOK:
            return 5;
        case PieceType::QUEEN:
            return 9;
        case PieceType::KING:
            return 0;
        default:
            return 0;
    }
}

void Player::removePiece(int y, int x) {
    for (int i = 0; i < NUMPIECES; i++) {
        if (pieces[i] != nullptr && pieces[i]->getY() == y &&
            pieces[i]->getX() == x) {
            int materialChange = getMaterialPiece(pieces[i]->getType());
            setMaterial(getMaterial() + materialChange);
            delete pieces[i];
            pieces[i] = nullptr;
        }
    }
}