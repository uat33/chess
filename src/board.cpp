#include "../include/board.h"

Board::Board() {
    white = new Player(Color::WHITE);
    black = new Player(Color::BLACK);

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
    for (int i = 0; i < length; ++i) {
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

int Board::processMove(const string &s, Color playerturn) {
    if (s.length() != 5) return -2;
    if (s[2] != '-') return -2;
    char file1 = std::tolower(s[0]);
    char file2 = std::tolower(s[3]);
    char row1 = s[1];
    char row2 = s[4];
    if (file1 < 'a' || file1 > 'h') return -2;
    if (file2 < 'a' || file2 > 'h') return -2;
    if (row1 < '1' || row1 > '8') return -2;
    if (row2 < '1' || row2 > '8') return -2;

    int y1 = 8 - (row1 - '0');
    int x1 = file1 - 'a';
    int y2 = 8 - (row2 - '0');
    int x2 = file2 - 'a';

    int index = convertCors(y1, x1);
    // one of the player's pieces must be on the chosen tile
    if (grid[index] == nullptr || grid[index]->getColor() != playerturn)
        return -1;
    bool res = grid[index]->isValidMove(y2, x2, grid);
    if (!res) return -1;
    grid[index]->setX(x2);
    grid[index]->setY(y2);
    int targetIndex = convertCors(y2, x2);

    if (grid[targetIndex] != nullptr) {
        // capture
        delete grid[targetIndex];
    }

    grid[targetIndex] = grid[index];
    grid[targetIndex]->setJustMoved(true);
    if (lastMoved != nullptr) {
        lastMoved->setJustMoved(false);
    }
    lastMoved = grid[targetIndex];
    grid[index] = nullptr;
    return 0;
}
