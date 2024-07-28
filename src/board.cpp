#include "../include/board.h"

Board::Board() : black(nullptr), white(nullptr), lastMoved(nullptr) {
    for (int i = 0; i < DIMENSION * DIMENSION; i++) {
        grid[i] = nullptr;
    }
}

Board::Board(bool init) {
    white = new Player(Color::WHITE, true);
    black = new Player(Color::BLACK, true);

    Piece **whitePieces = white->getPieces();
    Piece **blackPieces = black->getPieces();

    int y, x, index;
    for (int i = 0; i < NUMPIECES; i++) {
        y = whitePieces[i]->getY();
        x = whitePieces[i]->getX();
        index = convertCors(y, x);
        grid[index] = whitePieces[i];

        y = blackPieces[i]->getY();
        x = blackPieces[i]->getX();
        index = convertCors(y, x);
        grid[index] = blackPieces[i];
    }

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            int index = convertCors(i, j);
            grid[index] = nullptr;
        }
    }
}

Board::~Board() {
    delete white;
    delete black;
}

static void printHorizontalLine() {
    int length = 32;
    std::cout << "   ";
    for (int i = 0; i < length; i++) {
        std::cout << "\u2500";  // Unicode character for horizontal line (─)
    }
    std::cout << std::endl;
}

void Board::display(Color playerturn) const {
    // fill with row nums based off of whether this is being seen from one
    // player's side or the other
    int arr[DIMENSION];
    string fileLetters;
    for (int i = 0; i < DIMENSION; i++) {
        if (playerturn == Color::WHITE) {
            arr[i] = i;
            fileLetters = "    a   b   c   d   e   f   g   h";
        } else {
            arr[i] = DIMENSION - 1 - i;
            fileLetters = "    h   g   f   e   d   c   b   a";
        }
    }

    printHorizontalLine();
    for (int i : arr) {
        std::cout << 8 - i << " |";
        for (int j : arr) {
            int index = convertCors(i, j);
            if (grid[index] == nullptr) {
                std::cout << "   |";
            } else {
                grid[index]->display(grid[index]->getColor());
            }
        }
        std::cout << std::endl;
        printHorizontalLine();
    }
    std::cout << fileLetters << std::endl;
}

static bool validateInput(const string &s) {
    if (s.length() != 5) return false;
    if (s[2] != '-') return false;
    char file1 = std::tolower(s[0]);
    char file2 = std::tolower(s[3]);
    char row1 = s[1];
    char row2 = s[4];
    if (file1 < 'a' || file1 > 'h') return false;
    if (file2 < 'a' || file2 > 'h') return false;
    if (row1 < '1' || row1 > '8') return false;
    if (row2 < '1' || row2 > '8') return false;
    return true;
}

int Board::processMove(const string &s, Color playerturn) {
    // invalid notation
    if (!validateInput(s)) return -5;
    char file1 = std::tolower(s[0]);
    char file2 = std::tolower(s[3]);
    char row1 = s[1];
    char row2 = s[4];
    int y1 = 8 - (row1 - '0');
    int x1 = file1 - 'a';
    int y2 = 8 - (row2 - '0');
    int x2 = file2 - 'a';

    // Check that this player has a piece on that square.
    if (grid[convertCors(y1, x1)] == nullptr ||
        grid[convertCors(y1, x1)]->getColor() != playerturn) {
        return -4;
    }

    // make the move
    Player *current;
    Player *opposition;
    if (playerturn == Color::WHITE) {
        current = white;
        opposition = black;

    } else {
        current = black;
        opposition = white;
    }

    bool canMove = current->makeMove(y1, x1, y2, x2, grid);
    // if false, this was not valid move due to the piece not being able to move
    // to that location
    if (!canMove) return -1;

       // if this move causes the player to be under check it is invalid.
    // reset the board
    if (current->isUnderCheck(grid, opposition)) {
        return current->getUnderCheck() ? -3 : -2;
    }

    current->setUnderCheck(false);

    if (lastMoved != nullptr) {
        lastMoved->setJustMoved(false);
    } else {
        // it's possible this is the first move, in which case this will do
        // nothing. but if this was a castle, check the back row and remove the
        // last moved flag from all the pieces there
        for (int i = 0; i < DIMENSION; i++) {
            int r1 = convertCors(0, i);
            int r2 = convertCors(7, i);
            if (grid[r1] != nullptr) {
                grid[r1]->setJustMoved(false);
            }
            if (grid[r2] != nullptr) {
                grid[r2]->setJustMoved(false);
            }
        }
    }
    lastMoved = grid[convertCors(y2, x2)];

    // if it was a castle, the target square will be empty
    if (lastMoved != nullptr) {
        lastMoved->setJustMoved(true);
    }

    // check if it was a capture
    opposition->removePiece(y2, x2);
    if (opposition->isUnderCheck(grid, current)) {
        opposition->setUnderCheck(true);
    }
    return 0;
}

Board *Board::clone() {
    Board *newBoard = new Board();

    newBoard->white = this->white->clone();
    newBoard->black = this->black->clone();

    Piece **whitePieces = newBoard->white->getPieces();
    Piece **blackPieces = newBoard->black->getPieces();

    for (int i = 0; i < 16; i++) {
        if (whitePieces[i] != nullptr) {
            int x = whitePieces[i]->getX();
            int y = whitePieces[i]->getY();
            newBoard->grid[convertCors(y, x)] = whitePieces[i];
        }
        if (blackPieces[i] != nullptr) {
            int x = blackPieces[i]->getX();
            int y = blackPieces[i]->getY();
            newBoard->grid[convertCors(y, x)] = blackPieces[i];
        }
    }

    if (this->lastMoved != nullptr) {
        int x = this->lastMoved->getX();
        int y = this->lastMoved->getY();
        newBoard->lastMoved = newBoard->grid[convertCors(y, x)];
    } else {
        newBoard->lastMoved = nullptr;
    }

    return newBoard;
}
